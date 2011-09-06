#pragma once 

#include "../PunkEngine/common/gui/ITextBox.h"
#include "Element.h"


class __declspec(dllexport) GUITextBox : public GUIElement
{
public:
	GUITextBox(float x, float y, float width, float height, PunkString text);
	virtual ~GUITextBox();
	virtual void ElementDraw();
	virtual void Update(float delta);
	virtual void SetText(double number, int numberOfDigits);
	virtual void SetText(int number, int radix);
	virtual void SetText(float number);
	virtual void SetText(unsigned number, int radix);
	virtual int GetTextAsInteger() const;
	virtual double GetTextAsDouble() const;
	virtual unsigned GetLimit() const;
	virtual void SetLimit(unsigned limit);
	virtual void SetReadOnly(bool isReadOnly);	
	virtual void SetAutoSize(bool isAutoSize);
	virtual void KeyChar(unsigned int code, KeyFlags flags);
	virtual void KeyDown(unsigned int code, KeyFlags flags);	
	virtual void Reset();
	virtual void SetDrawOptions(TextOptions options);
private:
	unsigned m_limit;
	unsigned m_start;
	unsigned m_cursorPos;
	bool m_isReadOnly;
	TextOptions m_options;
};