#pragma once

#include "Element.h"
#include "Container.h"

class __declspec(dllexport) GUIForm : public GUIContainer
{
public:
	GUIForm(float x, float y, float width, float height);
	virtual ~GUIForm();
	virtual void ElementDraw();
	virtual void Update(float delta);
	virtual void MouseMove(int x, int y, MouseFlags flags);
};