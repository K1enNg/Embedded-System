#include <windows.h>
#include "system.h"

unsigned long long getUpTimeSeconds() {
    return GetTickCount64() / 1000;
}