/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_ssp_package;

NTSTATUS kuhl_m_sekurlsa_ssp(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_ssp(IN PMANGO_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _MANGO_SSP_CREDENTIAL_LIST_ENTRY {
	struct _MANGO_SSP_CREDENTIAL_LIST_ENTRY *Flink;
	struct _MANGO_SSP_CREDENTIAL_LIST_ENTRY *Blink;
	ULONG References;
	ULONG CredentialReferences;
	LUID LogonId;
	ULONG unk0;
	ULONG unk1;
	ULONG unk2;
	MANGO_GENERIC_PRIMARY_CREDENTIAL credentials;
} MANGO_SSP_CREDENTIAL_LIST_ENTRY, *PMANGO_SSP_CREDENTIAL_LIST_ENTRY;