#pragma once

#include "Element.h"
#include "Button.h"
#include <vector>

class __declspec(dllexport) GUIScrollBar : public GUIElement
{
	std::vector<GUIButton*> m_btns;
	int m_pos;
	int m_max;
	bool m_isVertical;
public:
	GUIScrollBar(float x, float y, float width, float height, int maxPos, bool isVertical = true);
	virtual ~GUIScrollBar();
	virtual void ElementDraw();
	virtual void Update(float delta);
	void SetScrollPosition(int pos);
	int GetScrollPosition() const;
	void SetMaxScroll(int max);
	int GetMaxScroll() const;
	void ResizeElements();	

	virtual void MouseLeftButtonDown(int x, int y, MouseFlags flags);
	virtual void MouseMove(int x, int y, MouseFlags flags);
	virtual void MouseLeave(int x, int y, MouseFlags flags);
	virtual void MouseLeftButtonUp(int x, int y, MouseFlags flags);

protected:
	void MoveDown(Parameters p);
	void MoveUp(Parameters p);
	void MoveDownPage(Parameters p);
	void MoveUpPage(Parameters p);	
};
