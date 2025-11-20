#include <windows.h>
#include "cpu.h"

static FILETIME prevIdleTime = {0};
static FILETIME prevKernelTime = {0};
static FILETIME prevUserTime = {0};

double getCPUUsage() {
    
}