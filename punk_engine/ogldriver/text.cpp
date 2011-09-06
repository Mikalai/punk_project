#include <stdio.h>
#include <stdarg.h>
#include "Text.h"
#include "Driver.h"

TText::TText(Driver* driver) : m_driver(driver)
{
	m_diffuse[0] = 1.0f;
	m_diffuse[1] = 1.0f;
	m_diffuse[2] = 1.0f;
	m_diffuse[3] = 1.0f;

	m_specular[0] = 0.0f;
	m_specular[1] = 0.0f;
	m_specular[2] = 0.0f;
	m_specular[3] = 0.0f;


	m_curFont.base = glGenLists(PUNK_ELEMENTS_COUNT);

	HFONT font;
	HFONT oldFont;
	font = CreateFontA(16, 0, 0, 0, FW_BOLD, 0, 0, 0, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "System");	
	oldFont = (HFONT)SelectObject(driver->GetDC(), font);
	wglUseFontBitmapsA(driver->GetDC(), 0, PUNK_ELEMENTS_COUNT, m_curFont.base);
	SelectObject(driver->GetDC(), oldFont);
	DeleteObject(font);

	m_curFont.size = 16;
	m_curFont.name = "System";
	m_fontsCollection[(PunkString("System")+16).CString()] = m_curFont;
}

TText::~TText()
{
	for (std::map<std::string, FontDesc>::iterator i = m_fontsCollection.begin(); i != m_fontsCollection.end(); i++)
		glDeleteLists(i->second.base, PUNK_ELEMENTS_COUNT);
	m_fontsCollection.clear();
}

bool TText::SetFont(const char *fontName, int size)
{
	m_curFont = m_fontsCollection[(PunkString(fontName)+size).CString()];

	if (m_curFont.base == 0)
	{
		m_curFont.name = PunkString(fontName)+size;
		m_curFont.base = glGenLists(PUNK_ELEMENTS_COUNT);

		HFONT font;
		HFONT oldFont;
		font = CreateFontA(size, 0, 0, 0, FW_BOLD, 0, 0, 0, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, fontName);	
		oldFont = (HFONT)SelectObject(m_driver->GetDC(), font);
		wglUseFontBitmapsA(m_driver->GetDC(), 0, PUNK_ELEMENTS_COUNT, m_curFont.base);
		SelectObject(m_driver->GetDC(), oldFont);
		DeleteObject(font);

		m_curFont.size = size;
		m_fontsCollection[(PunkString(fontName)+size).CString()] = m_curFont;		
	}
	return true;
}

TText::TText(const TText &text)
{
	if (this != &text)
	{
		m_curFont = text.m_curFont;
	}
}

TText& TText::operator =(TText &text)
{
	if (this != &text)
	{
		m_curFont = text.m_curFont;
	}
	return *this;
}

void TText::SetColor(float r, float g, float b, float a)
{
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
	m_diffuse[3] = a;
}

float* TText::GetColor()
{
	return m_diffuse;
}

void TText::Print(float x, float y, const char *text)
{
	if (m_curFont.base == 0)
		throw Exception("Text font is not created");
	if (text == NULL)
		return;

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glRasterPos3f(x, y, 0.0f);
	glPushAttrib(GL_LIST_BIT);
	glListBase(m_curFont.base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

void TText::SmartPrint(float x, float y, float width, float height, TextOptions options, const char* text, int* lines)
{
	//
	// do some calculations
	//
	unsigned length = strlen(text);
	unsigned offset = 0;
	unsigned maxSegmentLength = (unsigned)(width / m_curFont.size * log((double)m_curFont.size)-1);
	float curx = x;
	float cury = y;
	if (m_curFont.base == 0)
		throw Exception("Text font is not created");
	if (text == NULL)
		return;

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);	
	glPushAttrib(GL_LIST_BIT);
	glListBase(m_curFont.base);
	if (options == TEXT_CLIP)
	{
		glRasterPos3f(curx, cury, 0.0f);
		if (length > maxSegmentLength)
			glCallLists(maxSegmentLength, GL_UNSIGNED_BYTE, text);
		else
			glCallLists(length, GL_UNSIGNED_BYTE, text);
	}
	if (options == TEXT_AUTOSIZE)
	{
		unsigned maxCharacter = (unsigned)(height/m_curFont.size*maxSegmentLength);
		if (maxCharacter < length)
		{
			while (maxCharacter < length || m_curFont.size < 6)
			{
				SetFont(m_curFont.name.CString(), m_curFont.size-1);
				maxSegmentLength = (unsigned)(width / m_curFont.size * 2 - 1);
				maxCharacter = (unsigned)(height/m_curFont.size*maxSegmentLength);
			}	
		}
			maxSegmentLength = (unsigned)(width / m_curFont.size * 2 - 1);
			maxCharacter = (unsigned)(height/m_curFont.size*maxSegmentLength);
			while (offset < length)
			{
				glRasterPos3f(curx, cury, 0.0f);
				if (strlen(text+offset) > maxSegmentLength)
				{
					glCallLists(maxSegmentLength, GL_UNSIGNED_BYTE, text+offset);
					offset += maxSegmentLength;
					cury -= m_curFont.size;
					curx = x;
				}
				else
				{
					glCallLists(strlen(text+offset), GL_UNSIGNED_BYTE, text+offset);
					offset = strlen(text);
				}
			}
	}
	if (options == TEXT_WRAP)
	{
		while (offset < length)
		{
			glRasterPos3f(curx, cury, 0.0f);
			if (strlen(text+offset) > maxSegmentLength)
			{
				glCallLists(maxSegmentLength, GL_UNSIGNED_BYTE, text+offset);
				offset += maxSegmentLength;
				if (lines)
					(*lines)++;
				cury -= m_curFont.size;
				curx = x;
			}
			else
			{
				if (lines)
					(*lines)++;
				glCallLists(strlen(text+offset), GL_UNSIGNED_BYTE, text+offset);
				offset = strlen(text);
			}
		}
	}
	glPopAttrib();
}
#include <stdio.h>
#include <stdarg.h>
#include "Text.h"
#include "Driver.h"

TText::TText(TDriver* driver) : m_driver(driver)
{
	m_diffuse[0] = 1.0f;
	m_diffuse[1] = 1.0f;
	m_diffuse[2] = 1.0f;
	m_diffuse[3] = 1.0f;

	m_specular[0] = 0.0f;
	m_specular[1] = 0.0f;
	m_specular[2] = 0.0f;
	m_specular[3] = 0.0f;


	m_curFont.base = glGenLists(PUNK_ELEMENTS_COUNT);

	HFONT font;
	HFONT oldFont;
	font = CreateFontA(16, 0, 0, 0, FW_BOLD, 0, 0, 0, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "System");	
	oldFont = (HFONT)SelectObject(driver->GetDC(), font);
	wglUseFontBitmapsA(driver->GetDC(), 0, PUNK_ELEMENTS_COUNT, m_curFont.base);
	SelectObject(driver->GetDC(), oldFont);
	DeleteObject(font);

	m_curFont.size = 16;
	m_curFont.name = "System";
	m_fontsCollection[(PunkString("System")+16).CString()] = m_curFont;
}

TText::~TText()
{
	for (std::map<std::string, FontDesc>::iterator i = m_fontsCollection.begin(); i != m_fontsCollection.end(); i++)
		glDeleteLists(i->second.base, PUNK_ELEMENTS_COUNT);
	m_fontsCollection.clear();
}

bool TText::SetFont(const char *fontName, int size)
{
	m_curFont = m_fontsCollection[(PunkString(fontName)+size).CString()];

	if (m_curFont.base == 0)
	{
		m_curFont.name = PunkString(fontName)+size;
		m_curFont.base = glGenLists(PUNK_ELEMENTS_COUNT);

		HFONT font;
		HFONT oldFont;
		font = CreateFontA(size, 0, 0, 0, FW_BOLD, 0, 0, 0, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, fontName);	
		oldFont = (HFONT)SelectObject(m_driver->GetDC(), font);
		wglUseFontBitmapsA(m_driver->GetDC(), 0, PUNK_ELEMENTS_COUNT, m_curFont.base);
		SelectObject(m_driver->GetDC(), oldFont);
		DeleteObject(font);

		m_curFont.size = size;
		m_fontsCollection[(PunkString(fontName)+size).CString()] = m_curFont;		
	}
	return true;
}

TText::TText(const TText &text)
{
	if (this != &text)
	{
		m_curFont = text.m_curFont;
	}
}

TText& TText::operator =(TText &text)
{
	if (this != &text)
	{
		m_curFont = text.m_curFont;
	}
	return *this;
}

void TText::SetColor(float r, float g, float b, float a)
{
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
	m_diffuse[3] = a;
}

float* TText::GetColor()
{
	return m_diffuse;
}

void TText::Print(float x, float y, const char *text)
{
	if (m_curFont.base == 0)
		throw Exception("Text font is not created");
	if (text == NULL)
		return;

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glRasterPos3f(x, y, 0.0f);
	glPushAttrib(GL_LIST_BIT);
	glListBase(m_curFont.base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

void TText::SmartPrint(float x, float y, float width, float height, TextOptions options, const char* text, int* lines)
{
	//
	// do some calculations
	//
	unsigned length = strlen(text);
	unsigned offset = 0;
	unsigned maxSegmentLength = (unsigned)(width / m_curFont.size * log((double)m_curFont.size)-1);
	float curx = x;
	float cury = y;
	if (m_curFont.base == 0)
		throw Exception("Text font is not created");
	if (text == NULL)
		return;

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);	
	glPushAttrib(GL_LIST_BIT);
	glListBase(m_curFont.base);
	if (options == TEXT_CLIP)
	{
		glRasterPos3f(curx, cury, 0.0f);
		if (length > maxSegmentLength)
			glCallLists(maxSegmentLength, GL_UNSIGNED_BYTE, text);
		else
			glCallLists(length, GL_UNSIGNED_BYTE, text);
	}
	if (options == TEXT_AUTOSIZE)
	{
		unsigned maxCharacter = (unsigned)(height/m_curFont.size*maxSegmentLength);
		if (maxCharacter < length)
		{
			while (maxCharacter < length || m_curFont.size < 6)
			{
				SetFont(m_curFont.name.CString(), m_curFont.size-1);
				maxSegmentLength = (unsigned)(width / m_curFont.size * 2 - 1);
				maxCharacter = (unsigned)(height/m_curFont.size*maxSegmentLength);
			}	
		}
			maxSegmentLength = (unsigned)(width / m_curFont.size * 2 - 1);
			maxCharacter = (unsigned)(height/m_curFont.size*maxSegmentLength);
			while (offset < length)
			{
				glRasterPos3f(curx, cury, 0.0f);
				if (strlen(text+offset) > maxSegmentLength)
				{
					glCallLists(maxSegmentLength, GL_UNSIGNED_BYTE, text+offset);
					offset += maxSegmentLength;
					cury -= m_curFont.size;
					curx = x;
				}
				else
				{
					glCallLists(strlen(text+offset), GL_UNSIGNED_BYTE, text+offset);
					offset = strlen(text);
				}
			}
	}
	if (options == TEXT_WRAP)
	{
		while (offset < length)
		{
			glRasterPos3f(curx, cury, 0.0f);
			if (strlen(text+offset) > maxSegmentLength)
			{
				glCallLists(maxSegmentLength, GL_UNSIGNED_BYTE, text+offset);
				offset += maxSegmentLength;
				if (lines)
					(*lines)++;
				cury -= m_curFont.size;
				curx = x;
			}
			else
			{
				if (lines)
					(*lines)++;
				glCallLists(strlen(text+offset), GL_UNSIGNED_BYTE, text+offset);
				offset = strlen(text);
			}
		}
	}
	glPopAttrib();
}
