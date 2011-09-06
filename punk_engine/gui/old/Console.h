#pragma once

#include "Element.h"
#include "../Util/PunkString.h"
#include "TextBox.h"
#include "ScrollBar.h"
#include "../PunkEngine/common/gui/IConsole.h"
#include <vector>

class __declspec(dllexport) GUIConsole : public GUIElement
{
	std::vector<PunkString> m_history;
	std::vector<GUIElement*> m_child;
public:
	GUIConsole();
	virtual ~GUIConsole();
	virtual void ElementDraw();
	virtual void Update(float delta);
	void Add(PunkString text);
	PunkString Last();
	virtual void Resize(unsigned width, unsigned height);
	virtual void OnKeyEnter(Handler eventHandler);

	virtual void MouseLeftButtonDown(int x, int y, MouseFlags flags);
	virtual void MouseMove(int x, int y, MouseFlags flags);
	virtual void MouseLeave(int x, int y, MouseFlags flags);
	virtual void MouseLeftButtonUp(int x, int y, MouseFlags flags);
	virtual void KeyChar(unsigned code, KeyFlags flags);
	virtual void KeyDown(unsigned code, KeyFlags flags);
	virtual void MouseWheel(int delta, int x, int y, MouseFlags);
private:
	void OnEnterHandlerCallback(Parameters params);
};