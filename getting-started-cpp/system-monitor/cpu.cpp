#include <windows.h>
#include "cpu.h"

static FILETIME prevIdleTime = {0};
static FILETIME prevKernelTime = {0};
static FILETIME prevUserTime = {0};

static ULONGLONG fileNameToULL(const FILETIME& ft) {
    return ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
}

double getCPUUsage() {
    FILETIME idleTime, kernelTime, userTime;

    if(!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        return -1;
    }

    ULONGLONG idle = fileNameToULL(idleTime) - fileNameToULL(prevIdleTime);
    ULONGLONG kernel = fileNameToULL(kernelTime) - fileNameToULL(prevKernelTime);
    ULONGLONG user = fileNameToULL(userTime) - fileNameToULL(prevUserTime);

    prevIdleTime = idleTime;
    prevKernelTime = kernelTime;
    prevUserTime = userTime;

    ULONGLONG total = kernel + user;

    if (total == 0) return 0.0;

    return (double)(total - idle) * 100/total;

}