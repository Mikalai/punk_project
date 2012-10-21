#ifndef _FRAMEWORK_H_ // Win32 version
#define _FRAMEWORK_H_

// Get some classic includes
#include <iosfwd>
#include<Windows.h>
#include<stdio.h>
#include<io.h>
#include<fcntl.h>
#include<conio.h>
#include"al.h"
#include"alc.h"
#include"efx.h"
#include"efx-creative.h"
#include"xram.h"

// Initialization and shutdown
void ALFWInit();
void ALFWShutdown();

// OpenAL initialization and shutdown
ALboolean ALFWInitOpenAL();
ALboolean ALFWShutdownOpenAL();

// File loading functions
ALboolean ALFWLoadWaveToBuffer(const char *szWaveFile, ALuint uiBufferID, ALenum eXRAMBufferMode = 0);
ALboolean ALFWLoadWaveToBuffer(std::istream& stream, ALuint uiBufferID, ALenum eXRAMBufferMode = 0);

// Extension Queries 
ALboolean ALFWIsXRAMSupported();
ALboolean ALFWIsEFXSupported();


// Utilities
ALvoid ALFWprintf( const ALchar * x, ... );
ALchar *ALFWaddMediaPath(const ALchar *filename);
ALint ALFWKeyPress(void);

// EFX Extension function pointer variables

// Effect objects
extern LPALGENEFFECTS alGenEffects;
extern LPALDELETEEFFECTS alDeleteEffects;
extern LPALISEFFECT alIsEffect;
extern LPALEFFECTI alEffecti;
extern LPALEFFECTIV alEffectiv;
extern LPALEFFECTF alEffectf;
extern LPALEFFECTFV alEffectfv;
extern LPALGETEFFECTI alGetEffecti;
extern LPALGETEFFECTIV alGetEffectiv;
extern LPALGETEFFECTF alGetEffectf;
extern LPALGETEFFECTFV alGetEffectfv;

// Filter objects
extern LPALGENFILTERS alGenFilters;
extern LPALDELETEFILTERS alDeleteFilters;
extern LPALISFILTER alIsFilter;
extern LPALFILTERI alFilteri;
extern LPALFILTERIV alFilteriv;
extern LPALFILTERF alFilterf;
extern LPALFILTERFV alFilterfv;
extern LPALGETFILTERI alGetFilteri;
extern LPALGETFILTERIV alGetFilteriv;
extern LPALGETFILTERF alGetFilterf;
extern LPALGETFILTERFV alGetFilterfv;

// Auxiliary slot object
extern LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
extern LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
extern LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
extern LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
extern LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
extern LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
extern LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
extern LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
extern LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
extern LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
extern LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;

// XRAM Extension function pointer variables and enum values

typedef ALboolean (__cdecl *LPEAXSETBUFFERMODE)(ALsizei n, ALuint *buffers, ALint value);
typedef ALenum    (__cdecl *LPEAXGETBUFFERMODE)(ALuint buffer, ALint *value);

extern LPEAXSETBUFFERMODE eaxSetBufferMode;
extern LPEAXGETBUFFERMODE eaxGetBufferMode;

// X-RAM Enum values
extern ALenum eXRAMSize, eXRAMFree;
extern ALenum eXRAMAuto, eXRAMHardware, eXRAMAccessible;

#ifdef _DEBUG
inline void CHECK_ALERROR(const char* X)
{
	ALenum code = alGetError();

	if (code == AL_NO_ERROR)
		return;
	printf("%s\n\t", X);
	switch (code)
	{
	case AL_INVALID_NAME:
		printf("AL_INVALID_NAME  a bad name (ID) was passed to an OpenAL function\n");
		break;
	case AL_INVALID_ENUM:
		printf("AL_INVALID_ENUM an invalid enum value was passed to an OpenAL function\n");
		break;
	case AL_INVALID_VALUE:
		printf("AL_INVALID_ENUM an invalid value was passed to an OpenAL function\n");
		break;
	case AL_INVALID_OPERATION:
		printf("AL_INVALID_OPERATION  the requested operation is not valid\n");
		break;
	case AL_OUT_OF_MEMORY:
		printf("AL_INVALID_OPERATION  the requested operation resulted in OpenAL running out of memory\n");
		break;
	}
}
#else
#define CHECK_ALERROR(X)
#endif
	
	 
#endif _FRAMEWORK_H_