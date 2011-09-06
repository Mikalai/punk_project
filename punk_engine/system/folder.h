#ifndef FOLDER_H
#define FOLDER_H

#ifdef _WIN32
#include "win32/folder_win32.h"
#endif
#ifdef __linux__
#include "linux/folder_linux.h"
#endif

#endif // FOLDER_H
