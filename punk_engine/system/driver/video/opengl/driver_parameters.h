#ifndef DRIVER_PARAMETERS_H
#define DRIVER_PARAMETERS_H

#ifdef _WIN32
#include "win32/driver_parameters_win32.h"
#endif

#ifdef __linux__
#include "linux/driver_parameters_linux.h"
#endif

#endif // DRIVER_PARAMETERS_H
