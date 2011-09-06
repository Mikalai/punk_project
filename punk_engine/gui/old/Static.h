#pragma once
#include "Element.h"
#include "../PunkEngine/common/gui/IStatic.h"

class GUIStatic : public GUIElement, public IStatic
{
public:
	GUIStatic(float x, float y, PunkString text);
	virtual void Draw();
	virtual void Update(float delta);
	virtual void SetText(const PunkString& text);
	virtual bool IsVisible() const;
	virtual void SetVisible(bool isVisible);
	virtual bool IsEnabled() const;
	virtual void SetEnabled(bool isEnabled);
	virtual void SetSize(float width, float height);
	virtual void SetPosition(float x, float y);
	virtual void Enable();
	virtual void Disable();
	virtual void Show();
	virtual void Hide();
};