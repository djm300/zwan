/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include "kkll_m_modules.h"

typedef enum _MANGO_MF_INDEX {
	CallbackOffset				= 0,
	CallbackPreOffset			= 1,
	CallbackPostOffset			= 2,
	CallbackVolumeNameOffset	= 3,

	MF_MAX						= 4,
} MANGO_MF_INDEX, *PMANGO_MF_INDEX;

NTSTATUS kkll_m_filters_list(PMANGO_BUFFER outBuffer);
NTSTATUS kkll_m_minifilters_list(PMANGO_BUFFER outBuffer);