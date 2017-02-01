/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"

typedef enum _MANGO_PROCESS_INDEX {
	EprocessNext	= 0,
	EprocessFlags2	= 1,
	TokenPrivs		= 2,
	SignatureProtect= 3,

	Eprocess_MAX	= 4,
} MANGO_PROCESS_INDEX, *PMANGO_PROCESS_INDEX;

typedef struct _MANGO_NT6_PRIVILEGES
{
	UCHAR Present[8];
	UCHAR Enabled[8];
	UCHAR EnabledByDefault[8];
} MANGO_NT6_PRIVILEGES, *PMANGO_NT6_PRIVILEGES;

#define TOKEN_FROZEN_MASK		0x00008000
#define PROTECTED_PROCESS_MASK	0x00000800

typedef NTSTATUS (* PKKLL_M_PROCESS_CALLBACK) (SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer, PEPROCESS pProcess, PVOID pvArg);
NTSTATUS kkll_m_process_enum(SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer, PKKLL_M_PROCESS_CALLBACK callback, PVOID pvArg);

NTSTATUS kkll_m_process_token(SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer);
NTSTATUS kkll_m_process_protect(SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer);
NTSTATUS kkll_m_process_fullprivileges(SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer);

NTSTATUS kkll_m_process_token_toProcess(SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer, HANDLE hSrcToken, PEPROCESS pToProcess);

NTSTATUS kkll_m_process_list_callback(SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer, PEPROCESS pProcess, PVOID pvArg);
NTSTATUS kkll_m_process_systoken_callback(SIZE_T szBufferIn, PVOID bufferIn, PMANGO_BUFFER outBuffer, PEPROCESS pProcess, PVOID pvArg);