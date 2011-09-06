
#ifndef _PUNK_TEXT
#define _PUNK_TEXT

#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include <map>
#include <string>
#include "../PunkEngine/common/Types.h"

#define PUNK_ELEMENTS_COUNT 256

class Driver;

class TText
{	
public:
	TText(Driver* driver);
	~TText();
	TText(const TText& text);
	TText& operator = (TText& text);

	void SetColor(float r, float g, float b, float a);
	float* GetColor();
	void Print(float x, float y, const char* text);
	void SmartPrint(float x, float y, float width, float height, TextOptions options, const char* text, int* lines);
	bool SetFont(const char* fontName, int size);

public:
	struct FontDesc
	{
		int base, size;
		PunkString name;
		FontDesc() : size(0), base(0), name("") {}
	};
private:
	FontDesc m_curFont;
	std::map<std::string, FontDesc> m_fontsCollection;
	float m_diffuse[4];
	float m_specular[4];
	Driver* m_driver;
};

#endif
#ifndef _PUNK_TEXT
#define _PUNK_TEXT

#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include <map>
#include <string>
#include "../PunkEngine/common/Types.h"

#define PUNK_ELEMENTS_COUNT 256

class TDriver;

class TText
{	
public:
	TText(TDriver* driver);
	~TText();
	TText(const TText& text);
	TText& operator = (TText& text);

	void SetColor(float r, float g, float b, float a);
	float* GetColor();
	void Print(float x, float y, const char* text);
	void SmartPrint(float x, float y, float width, float height, TextOptions options, const char* text, int* lines);
	bool SetFont(const char* fontName, int size);

public:
	struct FontDesc
	{
		int base, size;
		PunkString name;
		FontDesc() : size(0), base(0), name("") {}
	};
private:
	FontDesc m_curFont;
	std::map<std::string, FontDesc> m_fontsCollection;
	float m_diffuse[4];
	float m_specular[4];
	TDriver* m_driver;
};

#endif