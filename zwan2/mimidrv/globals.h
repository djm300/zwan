/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include <ntifs.h>
#include <fltkernel.h>
#include <ntddk.h>
#include <aux_klib.h>
#include <ntstrsafe.h>
#include <string.h>
#include "ioctl.h"

#define POOL_TAG	'mango'
#define MIMIDRV		L"mimidrv"

#define kprintf(MangoBuffer, Format, ...) (RtlStringCbPrintfExW(*(MangoBuffer)->Buffer, *(MangoBuffer)->szBuffer, (MangoBuffer)->Buffer, (MangoBuffer)->szBuffer, STRSAFE_NO_TRUNCATION, Format, __VA_ARGS__))

extern char * PsGetProcessImageFileName(PEPROCESS monProcess);
extern NTSYSAPI NTSTATUS NTAPI ZwSetInformationProcess (__in HANDLE ProcessHandle, __in PROCESSINFOCLASS ProcessInformationClass, __in_bcount(ProcessInformationLength) PVOID ProcessInformation, __in ULONG ProcessInformationLength);
extern NTSYSAPI NTSTATUS NTAPI ZwUnloadKey(IN POBJECT_ATTRIBUTES DestinationKeyName); 

typedef struct _MANGO_BUFFER {
	size_t * szBuffer;
	PWSTR * Buffer;
} MANGO_BUFFER, *PMANGO_BUFFER;

typedef enum _MANGO_OS_INDEX {
	MangoOsIndex_UNK		= 0,
	MangoOsIndex_XP		= 1,
	MangoOsIndex_2K3		= 2,
	MangoOsIndex_VISTA	= 3,
	MangoOsIndex_7		= 4,
	MangoOsIndex_8		= 5,
	MangoOsIndex_BLUE	= 6,
	MangoOsIndex_10_1507	= 7,
	MangoOsIndex_10_1511	= 8,
	MangoOsIndex_10_1607	= 9,

	MangoOsIndex_MAX		= 10,
} MANGO_OS_INDEX, *PMANGO_OS_INDEX;

#ifdef _M_IX86
#define EX_FAST_REF_MASK	0x07
#else
#define EX_FAST_REF_MASK	0x0f
#endif

#define MANGO_mask3bits(addr)	 (((ULONG_PTR) (addr)) & ~7)

MANGO_OS_INDEX MangoOsIndex;