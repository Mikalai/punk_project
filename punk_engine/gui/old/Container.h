#pragma once

#include "Element.h"
#include <vector>

class __declspec(dllexport) GUIContainer : public GUIElement
{
protected:
	std::vector<GUIElement*> m_child;
	GUIElement* m_focusedElement;
public:
	GUIContainer(float x, float y, float width, float height);
	void AddControl(GUIElement* element);
	GUIElement* GetControl(unsigned index);
	void Remove(GUIElement* element);
	unsigned GetCount() const;
	
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
	virtual void Resize(unsigned width, unsigned height);
	virtual void MouseEnter(int x, int y, MouseFlags flags);
	virtual void MouseLeave(int x, int y, MouseFlags flags);
};