#include <cstdint>
#include <stdio.h>
#include "../MainInc/PRICoreMain.h"
#include <iostream>

int32_t GetSWVersion(char* pszSWVer, int32_t i32SWVerBufferLen)
{
    if (pszSWVer == NULL)
        return -1;
    snprintf(pszSWVer, i32SWVerBufferLen,
        "%02d.%02d.%02d.%02d",
        MWM_PRI_CORE_SW_MAJOR_VERSION, MWM_PRI_CORE_SW_MINOR_VERSION, MWM_PRI_CORE_SW_BUGFIX_VERSION, MWM_PRI_CORE_SW_BUILD_VERSION);
    return 0;
}

int32_t GetHWVersion(char* pszHWVer, int32_t i32SWVerBufferLen)
{
    if (pszHWVer == NULL)
        return -1;
    snprintf(pszHWVer, i32SWVerBufferLen,
        "%02d.%02d.%02d.%02d",
        MWM_PRI_CORE_HW_MAJOR_VERSION, MWM_PRI_CORE_HW_MINOR_VERSION, MWM_PRI_CORE_HW_BUGFIX_VERSION, MWM_PRI_CORE_HW_BUILD_VERSION);
    return 0;
}

void LogHeader(void)
{
    char     strTmpVal[33] = { 0 };
    GetSWVersion(strTmpVal, sizeof(strTmpVal));
    std::cout << "----------------------------------------------\n";
    std::cout << "  MWM PRI Core SW Version: " << strTmpVal << "\n";
    GetHWVersion(strTmpVal, sizeof(strTmpVal));
    std::cout << "  MWM PRI Core HW Version: " << strTmpVal << "\n";
    std::cout << "----------------------------------------------\n";
}