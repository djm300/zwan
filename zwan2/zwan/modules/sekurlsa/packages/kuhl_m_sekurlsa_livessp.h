/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_livessp_package;

NTSTATUS kuhl_m_sekurlsa_livessp(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_livessp(IN PMANGO_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _MANGO_LIVESSP_PRIMARY_CREDENTIAL
{
	ULONG isSupp;
	ULONG unk0;
	MANGO_GENERIC_PRIMARY_CREDENTIAL credentials;
} MANGO_LIVESSP_PRIMARY_CREDENTIAL, *PMANGO_LIVESSP_PRIMARY_CREDENTIAL;

typedef struct _MANGO_LIVESSP_LIST_ENTRY
{
	struct _MANGO_LIVESSP_LIST_ENTRY *Flink;
	struct _MANGO_LIVESSP_LIST_ENTRY *Blink;
	PVOID	unk0;
	PVOID	unk1;
	PVOID	unk2;
	PVOID	unk3;
	DWORD	unk4;
	DWORD	unk5;
	PVOID	unk6;
	LUID	LocallyUniqueIdentifier;
	LSA_UNICODE_STRING UserName;
	PVOID	unk7;
	PMANGO_LIVESSP_PRIMARY_CREDENTIAL suppCreds;
} MANGO_LIVESSP_LIST_ENTRY, *PMANGO_LIVESSP_LIST_ENTRY;
