#ifndef _H_PUNK_ALLOCATOR
#define _H_PUNK_ALLOCATOR

#ifdef _WIN32
#include "win32/allocator_win32.h"
#endif

#ifdef __linux__
#include "linux/allocator_linux.h"
#endif

#include <stdio.h>

static void* operator new (unsigned int num_bytes)
{	
	return System::Allocator::Alloc(num_bytes);
}

static void* operator new [] (unsigned int num_bytes)
{
	return System::Allocator::Alloc(num_bytes);
}

static void operator delete (void* object)
{
	System::Allocator::Free(object);
}

static void operator delete[] (void* object)
{
	System::Allocator::Free(object);
}

#endif