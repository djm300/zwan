/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#define SECURITY_WIN32
#include <windows.h>
#include <ntsecapi.h>
#include <sspi.h>
#include <sddl.h>
#include <wincred.h>
#include <ntsecapi.h>
#include <ntsecpkg.h>
#include <stdio.h>

#ifdef _M_X64
	#define zwan_ARCH_A "x64"
#else ifdef _M_IX86
	#define zwan_ARCH_A "x86"
#endif

#define zwan_A				"zwan"
#define zwan_VERSION_A		"2.1 alpha"
#define zwan_CODENAME_A		"A La Vie, A L\'Amour"
#define zwan_FULL_A			zwan_A " " zwan_VERSION_A " (" zwan_ARCH_A ") built on " __DATE__ " " __TIME__
#define zwan_SECOND_A		"\"" zwan_CODENAME_A "\""

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

#define LM_NTLM_HASH_LENGTH	16

void klog(FILE * logfile, PCWCHAR format, ...);
void klog_password(FILE * logfile, PUNICODE_STRING pPassword);
void klog_sid(FILE * logfile, PSID pSid);

typedef struct _REMOTE_LIB_FUNC {
	DWORD	outputSize;
	PVOID	outputData;
	DWORD	inputSize;
	BYTE	inputData[ANYSIZE_ARRAY];
} REMOTE_LIB_FUNC, *PREMOTE_LIB_FUNC;