#include <windows.h>
#include "memory.h"

double getRAMUsage() {
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);

    return (double)mem.dwMemoryLoad;
}

unsigned long long getTotalRam() {
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    return mem.ullTotalPhys; 
}

unsigned long long getFreeRAM() {
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);
    return mem.ullAvailPhys; 
}