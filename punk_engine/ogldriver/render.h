#pragma once

#include "../PunkEngine/common/IRender.h"
#include "Text.h"
class Driver;

class Render : public IRender
{
	Driver* m_driver;
	TText* m_textRender;
	float m_zNear;
	float m_zFar;
	bool m_useShadowMap;
	GLuint m_shadowTexture;
	IGUIManager* m_guiManager;
public:
	Render(Driver* driver);
	virtual ~Render();
	virtual bool RenderSprite(float x, float y, float width, float height);
	virtual bool RenderRect(float x, float y, float width, float height);
	virtual bool RenderText(float x, float y, float rectWidth, float rectHeight, const char* text, ...);
	virtual bool SmartRenderText(float x, float y, float rectWidth, float rectHeight, TextOptions options, int* lines, const char* text, ...);
	virtual bool SetColor(float r, float g, float b, float a);
	virtual bool SetViewPort(int x, int y, int width, int height);
	virtual bool Enter2DMode(int viewPortX = 0, int viewPortY = 0, int viewPortWidth = 0, int viewPortHeight = 0, int x = 0, int y = 0, int width = 0, int height = 0);
	virtual bool Leave2DMode();
	virtual bool SetFont(const char* fontName, int size);
	virtual bool UseShadowMap(bool use = true);
	virtual void SetZNear(float value);
	virtual void SetZFar(float value);
	virtual float GetZNear() const;
	virtual float GetZFar() const;
	virtual bool BeginRender(RenderTarget target = RENDER_BUFFER);
	virtual bool EndRender(RenderTarget target = RENDER_BUFFER);
	virtual void SetGUIManager(IGUIManager* guiManager);
	virtual float GetSrceenWidth() const;
	virtual float GetScreenHeight() const;
private:
	bool RenderStatistic();
	bool GenerateTextureMatrix();
};
#pragma once

#include "../PunkEngine/common/IRender.h"
#include "Text.h"
class TDriver;

class Render : public IRender
{
	TDriver* m_driver;
	TText* m_textRender;	
	float m_zNear;
	float m_zFar;
	bool m_useShadowMap;
	GLuint m_shadowTexture;
	IGUIManager* m_guiManager;
public:
	Render(TDriver* driver);
	virtual ~Render();
	virtual bool RenderSprite(float x, float y, float width, float height);
	virtual bool RenderRect(float x, float y, float width, float height);
	virtual bool RenderText(float x, float y, float rectWidth, float rectHeight, const char* text, ...);
	virtual bool SmartRenderText(float x, float y, float rectWidth, float rectHeight, TextOptions options, int* lines, const char* text, ...);
	virtual bool SetColor(float r, float g, float b, float a);
	virtual bool SetViewPort(int x, int y, int width, int height);
	virtual bool Enter2DMode(int viewPortX = 0, int viewPortY = 0, int viewPortWidth = 0, int viewPortHeight = 0, int x = 0, int y = 0, int width = 0, int height = 0);
	virtual bool Leave2DMode();
	virtual bool SetFont(const char* fontName, int size);
	virtual bool UseShadowMap(bool use = true);	
	virtual void SetZNear(float value);
	virtual void SetZFar(float value);
	virtual float GetZNear() const;
	virtual float GetZFar() const;
	virtual bool BeginRender(RenderTarget target = RENDER_BUFFER);
	virtual bool EndRender(RenderTarget target = RENDER_BUFFER);	
	virtual void SetGUIManager(IGUIManager* guiManager);
	virtual float GetSrceenWidth() const;
	virtual float GetScreenHeight() const;
private:
	bool RenderStatistic();
	bool GenerateTextureMatrix();
};