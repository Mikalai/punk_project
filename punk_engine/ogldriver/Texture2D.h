#ifndef _PUNK_TEXTURE
#define _PUNK_TEXTURE

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include "../PunkEngine/PunkEngine.h"

class Driver;
class TImage;

class TTexture2D : public ITexture2D
{
public:
	virtual ~TTexture2D();
	TTexture2D();
	virtual bool Create(Image* image);
	virtual unsigned Id() const;
	void Apply();
	GLuint m_textureName;
};

#endif#ifndef _PUNK_TEXTURE
#define _PUNK_TEXTURE

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include "../PunkEngine/PunkEngine.h"

class TDriver;
class TImage;

class TTexture2D : public ITexture2D
{
public:
	virtual ~TTexture2D();
	TTexture2D();
	virtual bool Create(Image* image);
	virtual unsigned Id() const;
	void Apply();
	GLuint m_textureName;
};

#endif