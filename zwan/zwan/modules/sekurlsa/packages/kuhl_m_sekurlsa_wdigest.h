/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include "../kuhl_m_sekurlsa.h"

KUHL_M_SEKURLSA_PACKAGE kuhl_m_sekurlsa_wdigest_package;

NTSTATUS kuhl_m_sekurlsa_wdigest(int argc, wchar_t * argv[]);
void CALLBACK kuhl_m_sekurlsa_enum_logon_callback_wdigest(IN PMANGO_BASIC_SECURITY_LOGON_SESSION_DATA pData);

typedef struct _MANGO_WDIGEST_LIST_ENTRY {
	struct _MANGO_WDIGEST_LIST_ENTRY *Flink;
	struct _MANGO_WDIGEST_LIST_ENTRY *Blink;
	ULONG	UsageCount;
	struct _MANGO_WDIGEST_LIST_ENTRY *This;
	LUID LocallyUniqueIdentifier;
} MANGO_WDIGEST_LIST_ENTRY, *PMANGO_WDIGEST_LIST_ENTRY;