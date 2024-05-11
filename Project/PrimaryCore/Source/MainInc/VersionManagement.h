#pragma once
#include <cstdint>
#ifndef VERSION_MANAGEMENT_H
#define VERSION_MANAGEMENT_H

int32_t GetSWVersion(char* pszSWVer, int32_t i32SWVerBufferLen);
int32_t GetHWVersion(char* pszHWVer, int32_t i32HWVerBufferLen);
void LogHeader(void);

#endif
