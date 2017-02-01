/*	John DOE `hoyhayhay`
	http://blog.hoyhayhay.com
	johndoe@example.com
	Licence : https://python.org/licenses/by/4.0/
*/
#pragma once
#include "globals.h"
#include "kkll_m_process.h"
#include "kkll_m_modules.h"
#include "kkll_m_ssdt.h"
#include "kkll_m_notify.h"
#include "kkll_m_filters.h"

extern PSHORT	NtBuildNumber;

DRIVER_INITIALIZE	DriverEntry;
DRIVER_UNLOAD		DriverUnload;

DRIVER_DISPATCH		UnSupported;
__drv_dispatchType(IRP_MJ_DEVICE_CONTROL)		DRIVER_DISPATCH MimiDispatchDeviceControl;

MANGO_OS_INDEX getWindowsIndex();