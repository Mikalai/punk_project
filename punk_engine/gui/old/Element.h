#pragma once

#include "../Util/PunkString.h"
#include "../PunkEngine/common/types.h"
#include "../PunkEngine/common/ITexture2D.h"
#include "../PunkEngine/common/types.h"
#include "Type.h"
class __declspec(dllexport) GUIElement
{
protected:
	GUIElement* m_parent;
	float m_width;
	float m_height;
	float m_x;
	float m_y;
	float m_zDepth;
	int m_prevMouseX;
	int m_prevMouseY;
	PunkString m_text;
	Color m_backColor;
	Color m_fontColor;
	int m_fontSize;
	PunkString m_fontName;
	ITexture2D* m_background;
	bool m_isFocused;
	bool m_left;
	bool m_right;
	bool m_middle;	
	bool m_isVisible;
	bool m_isEnable;
	bool m_isMouseOver;
	
public:
	virtual void ElementDraw() = 0;	
	virtual void Update(float delta) = 0;
	
	void Draw();
	GUIElement();
	GUIElement(const GUIElement& element);
	GUIElement(float x, float y, float width, float height, PunkString text);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetPosition(float x, float y);
	void GetPosition(float* x, float* y);
	void SetSize(float width, float height);
	float GetX() const;
	float GetY() const;
	float GetWidth() const;
	float GetHeight() const;
	void SetText(const PunkString& text);
	const PunkString& GetText() const;
	GUIElement& operator = (const GUIElement& element);
	void SetFontColor(float r, float g, float b, float a);
	void SetBackColor(float r, float g, float b, float a);
	const Color& GetFontColor() const;
	const Color& GetBackColor() const;
	void SetFontSize(int size);
	int GetFontSize() const;
	void SetFont(const PunkString& fontName, int size);
	const PunkString& GetFontName() const;
	bool IsPointIn(int x, int y);	
	bool IsVisible() const;
	void SetVisible(bool isVisible);
	bool IsEnabled() const;
	void SetEnabled(bool isEnabled);
	void Enable();
	void Disable();
	void Show();
	void Hide();
	void SetParent(GUIElement* element);
	void SetZDepth(float depth);
	float GetZDepth() const;
	bool IsMouseOver() const;
	void SetFocused(bool isFocused = true);
	bool IsFocused() const;
	GUIElement* GetParent();
	virtual void MouseMove(int x, int y, MouseFlags flags);
	virtual void MouseLeftButtonDoubleClick(int x, int y, MouseFlags flags);
	virtual void MouseLeftButtonDown(int x, int y, MouseFlags flags);
	virtual void MouseLeftButtonUp(int x, int y, MouseFlags flags);
	virtual void MouseRightButtonDoubleClick(int x, int y, MouseFlags flags);
	virtual void MouseRightButtonDown(int x, int y, MouseFlags flags);
	virtual void MouseRightButtonUp(int x, int y, MouseFlags flags);
	virtual void MouseMiddleButtonDoubleClick(int x, int y, MouseFlags flags);
	virtual void MouseMiddleButtonDown(int x, int y, MouseFlags flags);
	virtual void MouseMiddleButtonUp(int x, int y, MouseFlags flags);
	virtual void MouseWheel(int delta, int x, int y, MouseFlags flags);
	virtual void KeyChar(unsigned code, KeyFlags flags);
	virtual void KeyDown(unsigned code, KeyFlags flags);
	virtual void KeyUp(unsigned code, KeyFlags flags);
	virtual void MouseRightButtonClick(int x, int y, MouseFlags flags);
	virtual void MouseLeftButtonClick(int x, int y, MouseFlags flags);
	virtual void MouseMiddleButtonClick(int x, int y, MouseFlags flags);
	virtual void Resize(unsigned width, unsigned height);
	virtual void MouseEnter(int x, int y, MouseFlags flags);
	virtual void MouseLeave(int x, int y, MouseFlags flags);
public:
	virtual void OnClick(Handler eventHandler);
	virtual void OnDblClk(Handler eventHandler);
	virtual void OnMouseEnter(Handler eventHandler);
	virtual void OnMouseLeave(Handler eventHandler);	
	virtual void OnKeyEnter(Handler eventHandler);

protected:
	Handler onButtonClickMethod;
	Handler onButtonDblclkMethod;
	Handler onMouseEnterMethod;
	Handler onMouseLeaveMethod;
	Handler onKeyEnterMethod;

public:
	struct Compare
	{
		bool operator () (GUIElement* e1, GUIElement* e2)
		{
			return e1->GetZDepth() > e2->GetZDepth();
		}
	};
};