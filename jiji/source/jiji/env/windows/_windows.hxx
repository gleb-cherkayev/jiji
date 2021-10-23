#pragma once

#define WIN32_LEAN_AND_MEAN
#pragma warning(push)
#pragma warning(disable:4005)  // macro redefinition
//#pragma warning(disable:5105)  // macro expansion producing 'defined' has undefined behavior // For some reason ignored, disabled it in cmake instead.
#include <windows.h>
#pragma warning(pop)