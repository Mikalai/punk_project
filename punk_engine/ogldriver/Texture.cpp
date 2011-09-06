//
// Simple texture class
//

#ifdef	_WIN32
#include	<windows.h>
#endif

#include	<GL/gl.h>
#include	<GL/glu.h>
#include	<malloc.h>
#include	<memory.h>
#include	"Texture.h"
/*
Texture :: Texture () :
m_width(0),
m_heigh(0),
m_numComponents(0),
m_data(NULL),
m_levels(0),
m_compressed(false),
m_format(GL_NONE)
{}

Texture :: Texture ( int theWidth, int theHeight, int theNumComponents ) :
m_width(theWidth),
m_height(theHeight),
m_numComponents(theNumComponents),
m_data(new char[m_width * m_height * m_numComponents]),
m_levels(1),
m_compressed(false)
{
	switch ( m_numComponents )
	{
	case 1:
		m_format = GL_ALPHA;
		break;

	case 3:
		m_format = GL_RGB;
		break;

	case 4:
		m_format = GL_RGBA;
		break;

	default:
		m_format = -1;
	}
}

Texture :: ~Texture ()
{
	delete[] m_data;
}
// store 32-bit RGBA image into texture in a
// specified line
void Texture::PutLine(int y, unsigned long * bits )
{
	if ( y < 0 || y >= m_height )
		return;

	int offs = y * m_width * m_numComponents;
	char* ptr = data + offs;

	if (m_numComponents == 4)				// RGBA image
		memcpy(ptr, bits, 4 * m_width);
	else
		if (m_numComponents == 3)				// RGB image
		{
			char* src = (char*) bits;

			for ( int i = 0; i < m_width; i++, src += 4 )
			{
				*ptr++ = src [0];
				*ptr++ = src [1];
				*ptr++ = src [2];
			}
		}
		else
			if ( m_numComponents == 1 )				// greyscale image
			{
				for ( int i = 0; i < m_width ; i++, bits++ )
					*ptr++ = *(byte *) bits;
			}
}

bool	Texture :: upload ( int target, bool mipmap )
{
	if ( target == GL_TEXTURE_1D )
	{
		if ( mipmap )
			gluBuild1DMipmaps ( target, getNumComponents (), getWidth (),
			getFormat (), GL_UNSIGNED_BYTE, getData () );
		else
			glTexImage1D      ( target, 0, getNumComponents (), getWidth (), 0,
			getFormat (), GL_UNSIGNED_BYTE, getData () );
	}
	else
	{
		if ( mipmap )
			gluBuild2DMipmaps ( target, getNumComponents (), getWidth (), getHeight (),
			getFormat (), GL_UNSIGNED_BYTE, getData () );
		else
			glTexImage2D      ( target, 0, getNumComponents (), getWidth (), getHeight (), 0,
			getFormat (), GL_UNSIGNED_BYTE, getData () );
	}

	return true;
}

*/