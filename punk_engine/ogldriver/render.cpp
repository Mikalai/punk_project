#include "render.h"
#include "driver.h"
#include "../math/math.h"

Render::Render(Driver* driver) : m_driver(driver), m_zNear(0.1f), m_zFar(100.0)
{
	m_textRender = new TText(m_driver);
}

Render::~Render()
{
	DELETE_POINTER(m_textRender);
}

bool Render::RenderRect(float x, float y, float width, float height)
{
	glRectf(x,y,x+width,y+height);
/*	glBegin(GL_QUADS);
	glVertex3f(0,0,-1);
	glVertex3f(100,0,-1);
	glVertex3f(100,100,-1);
	glVertex3f(0,100,-1);
	glEnd();*/
	return true;
}

bool Render::RenderSprite(float x, float y, float width, float height)
{
	return false;
}

bool Render::RenderText(float x, float y, float rectWidth, float rectHeight, const char* text, ...)
{
	char* buffer = new char[PUNK_MAX_AVERAGE_BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer[0])*PUNK_MAX_AVERAGE_BUFFER_SIZE);
	try
	{
		va_list argumentPointer;
		va_start(argumentPointer, text);
		vsnprintf_s(buffer, PUNK_MAX_AVERAGE_BUFFER_SIZE*sizeof(buffer[0]), PUNK_MAX_AVERAGE_BUFFER_SIZE, text, argumentPointer);
		va_end(argumentPointer);

#ifdef _DEBUG
		if (m_textRender == NULL)
			throw Exception(PUNK_TEXT("There is no text render, so i can't render text"));
#endif
		m_textRender->Print(x, y, buffer);
		DELETE_ARRAY(buffer);
	}
	catch(...)
	{
		DELETE_ARRAY(buffer);
		throw;
	}

	return true;
}

bool Render::SmartRenderText(float x, float y, float rectWidth, float rectHeight, TextOptions options, int* lines, const char* text, ...)
{
	int size = strlen(text)+PUNK_MAX_AVERAGE_BUFFER_SIZE;
	char* buffer = new char[size];
	memset(buffer, 0, sizeof(buffer[0])*size);
	try
	{
		va_list argumentPointer;
		va_start(argumentPointer, text);
		vsnprintf_s(buffer, size*sizeof(buffer[0]), size, text, argumentPointer);
		va_end(argumentPointer);

#ifdef _DEBUG
		if (m_textRender == NULL)
			throw Exception(PUNK_TEXT("There is no text render, so i can't render text"));
#endif
		m_textRender->SmartPrint(x, y, rectWidth, rectHeight, options, buffer, lines);
		DELETE_ARRAY(buffer);
	}
	catch(...)
	{
		DELETE_ARRAY(buffer);
		throw;
	}

	return true;
}

bool Render::SetColor(float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
	return true;
}

bool Render::Enter2DMode(int viewPortX, int viewPortY, int viewPortWidth, int viewPortHeight, int x, int y, int width, int height)
{
	if (viewPortWidth == 0 || viewPortHeight == 0)
	{
		viewPortWidth = m_driver->GetWindowWidth();
		viewPortHeight = m_driver->GetWindowHeight();
	}
	else if (viewPortWidth < 0 || viewPortHeight < 0)
		return false;

	if (width == 0 || height == 0)
	{
		width = m_driver->GetWindowWidth();
		height = m_driver->GetWindowHeight();
	}
	else if (width < 0 || height < 0)
		return false;

	glViewport(viewPortX, m_driver->GetWindowHeight()-viewPortY-viewPortHeight, viewPortWidth, viewPortHeight);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(x, width, height, y);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	return true;
}

bool Render::SetViewPort(int x, int y, int width, int height)
{
	glViewport(x,y,width,height);
	return true;
}

float Render::GetSrceenWidth() const
{
	return (float)m_driver->GetWindowWidth();
}

float Render::GetScreenHeight() const
{
	return (float)m_driver->GetWindowHeight();
}

bool Render::Leave2DMode()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	return true;
}

bool Render::UseShadowMap(bool use)
{
	if (use)
	{
		if (m_shadowTexture != 0)
			glDeleteTextures(1, &m_shadowTexture);
		glGenTextures(1, &m_shadowTexture);
		glBindTexture(GL_TEXTURE_2D, m_shadowTexture);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			PUNK_SHADOW_MAP_WIDTH, PUNK_SHADOW_MAP_HEIGHT, 0,
			GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL );

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL );
		glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,
			GL_COMPARE_R_TO_TEXTURE );

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

		glPolygonOffset(2, 2);
		/*		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glTexGeni( GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		/**/
		glCullFace( GL_BACK );

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_LIGHT0 );
		glEnable( GL_LIGHTING );
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_TEXTURE_GEN_S );
		glEnable( GL_TEXTURE_GEN_T );
		glEnable( GL_TEXTURE_GEN_R );
		glEnable( GL_TEXTURE_GEN_Q );
		glEnable( GL_COLOR_MATERIAL );
		glEnable( GL_CULL_FACE );

		m_useShadowMap = true;
	}
	else
	{
		glDeleteTextures(1, &m_shadowTexture);
		glDisable( GL_TEXTURE_GEN_S );
		glDisable( GL_TEXTURE_GEN_T );
		glDisable( GL_TEXTURE_GEN_R );
		glDisable( GL_TEXTURE_GEN_Q );

		m_useShadowMap = false;
	}

	return true;
}

bool Render::SetFont(const char* fontName, int size)
{
	return m_textRender->SetFont(fontName, size);
}

bool Render::GenerateTextureMatrix()
{
	ILightManager* lightManager = m_driver->GetScene()->GetLightManager();

	glBindTexture(GL_TEXTURE_2D, m_shadowTexture);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_Q);

	float PS[] = {1, 0, 0, 0};
	float PT[] = {0, 1, 0, 0};
	float PR[] = {0, 0, 1, 0};
	float PQ[] = {0, 0, 0, 1};

	glTexGenfv(GL_S, GL_EYE_PLANE, PS);
	glTexGenfv(GL_T, GL_EYE_PLANE, PT);
	glTexGenfv(GL_R, GL_EYE_PLANE, PR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, PQ);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5f, 0.5f, 0.5f);
	glScalef(0.5f, 0.5f, 0.5f);
	gluPerspective(2*lightManager->GetLight(0)->GetSpotCutoff(), PUNK_SHADOW_MAP_WIDTH/PUNK_SHADOW_MAP_HEIGHT, m_zNear, m_zFar);
	const float* lightDir = lightManager->GetLight(0)->GetSpotDirection();
	const float* lightPos = lightManager->GetLight(0)->GetPosition();
	gluLookAt(lightPos[0], lightPos[1], lightPos[2], 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);

	/*	    GLfloat  tmpMatrix[16];

	glPushMatrix();
	glLoadIdentity();
	glTranslatef( 0.5, 0.5, 0.0 );
	glScalef( 0.5, 0.5, 1.0 );
	gluPerspective( 60.0, 1.0, 1.0, 1000.0 );
	GLfloat lightPos[4];
	const float* lightDir = m_lightManager.GetLight(0)->GetSpotDirection();
	glGetLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	gluLookAt( lightPos[0], lightPos[1], lightPos[2], lightPos[0]+lightDir[0], lightPos[1]+lightDir[1], lightPos[2]+lightDir[2], 0, 1, 0 );
	//gluLookAt(5,0,5, 0, 0, 0, 0, 1, 0);
	glGetFloatv( GL_MODELVIEW_MATRIX, tmpMatrix );
	glPopMatrix();

	transposeMatrix( tmpMatrix );

	glBindTexture(GL_TEXTURE_2D, m_shadowTexture);
	glTexGenfv( GL_S, GL_OBJECT_PLANE, &tmpMatrix[0] );
	glTexGenfv( GL_T, GL_OBJECT_PLANE, &tmpMatrix[4] );
	glTexGenfv( GL_R, GL_OBJECT_PLANE, &tmpMatrix[8] );
	glTexGenfv( GL_Q, GL_OBJECT_PLANE, &tmpMatrix[12] );
	/**/
	return true;
}

bool Render::RenderStatistic()
{
	IScene* scene = m_driver->GetScene();
	static int count = 0;
	static int oldCount = 0;
	static float time = 0;
	float x = 10.0f;
	float y = 40.0f;
	Enter2DMode();
	SetColor(1,1,1,1);
	RenderText(x,y,0,0,"Mesh count: %d", 0);
	y += 20.0f;
	RenderText(x,y,0,0,"Texture count: %d", 0);
	y += 20.0f;
	RenderText(x, y, 0, 0, "Image count: %d", 0);
	y += 20.0f;
	RenderText(x, y, 0, 0, "FPS: %d", 0);
	//time += m_time.GetTimeFromLastGetTime();
	count++;
	if (time > 1)
	{
		oldCount = count;
		count = 0;
		time = 0;
	}
	Leave2DMode();
	return true;
}

void Render::SetZFar(float value)
{
	m_zFar = value;
}

void Render::SetZNear(float value)
{
	m_zNear = value;
}

float Render::GetZFar() const
{
	return m_zFar;
}

float Render::GetZNear() const
{
	return m_zNear;
}

bool Render::BeginRender(RenderTarget target)
{
	ILightManager* lightManager = m_driver->GetScene()->GetLightManager();
	lightManager->SetAmbient(.6,.6,.6,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	m_driver->GetScene()->GetCamera()->Apply();
	return true;
}


bool Render::EndRender(RenderTarget target)
{
	m_driver->SwapBuffers();
	return true;
}

void Render::SetGUIManager(IGUIManager *guiManager)
{
	m_guiManager = guiManager;
	m_driver->SetGUIManager(m_guiManager);
}
#include "Render.h"
#include "Driver.h"
#include "../Math/Math.h"

Render::Render(TDriver* driver) : m_driver(driver), m_zNear(0.1f), m_zFar(100.0)
{
	m_textRender = new TText(m_driver);
}

Render::~Render()
{
	DELETE_POINTER(m_textRender);
}

bool Render::RenderRect(float x, float y, float width, float height)
{
	glRectf(x,y,x+width,y+height);
/*	glBegin(GL_QUADS);
	glVertex3f(0,0,-1);
	glVertex3f(100,0,-1);
	glVertex3f(100,100,-1);
	glVertex3f(0,100,-1);
	glEnd();*/
	return true;
}

bool Render::RenderSprite(float x, float y, float width, float height)
{
	return false;
}

bool Render::RenderText(float x, float y, float rectWidth, float rectHeight, const char* text, ...)
{
	char* buffer = new char[PUNK_MAX_AVERAGE_BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer[0])*PUNK_MAX_AVERAGE_BUFFER_SIZE);
	try
	{
		va_list argumentPointer;
		va_start(argumentPointer, text);
		vsnprintf_s(buffer, PUNK_MAX_AVERAGE_BUFFER_SIZE*sizeof(buffer[0]), PUNK_MAX_AVERAGE_BUFFER_SIZE, text, argumentPointer);
		va_end(argumentPointer);

#ifdef _DEBUG
		if (m_textRender == NULL)
			throw Exception(PUNK_TEXT("There is no text render, so i can't render text"));
#endif
		m_textRender->Print(x, y, buffer);
		DELETE_ARRAY(buffer);
	}
	catch(...)
	{
		DELETE_ARRAY(buffer);
		throw;
	}

	return true;
}

bool Render::SmartRenderText(float x, float y, float rectWidth, float rectHeight, TextOptions options, int* lines, const char* text, ...) 
{
	int size = strlen(text)+PUNK_MAX_AVERAGE_BUFFER_SIZE;
	char* buffer = new char[size];
	memset(buffer, 0, sizeof(buffer[0])*size);
	try
	{
		va_list argumentPointer;
		va_start(argumentPointer, text);
		vsnprintf_s(buffer, size*sizeof(buffer[0]), size, text, argumentPointer);
		va_end(argumentPointer);

#ifdef _DEBUG
		if (m_textRender == NULL)
			throw Exception(PUNK_TEXT("There is no text render, so i can't render text"));
#endif
		m_textRender->SmartPrint(x, y, rectWidth, rectHeight, options, buffer, lines);
		DELETE_ARRAY(buffer);
	}
	catch(...)
	{
		DELETE_ARRAY(buffer);
		throw;
	}

	return true;
}

bool Render::SetColor(float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
	return true;
}

bool Render::Enter2DMode(int viewPortX, int viewPortY, int viewPortWidth, int viewPortHeight, int x, int y, int width, int height)
{	
	if (viewPortWidth == 0 || viewPortHeight == 0)
	{
		viewPortWidth = m_driver->GetWindowWidth();
		viewPortHeight = m_driver->GetWindowHeight();
	}
	else if (viewPortWidth < 0 || viewPortHeight < 0)
		return false;

	if (width == 0 || height == 0)
	{
		width = m_driver->GetWindowWidth();
		height = m_driver->GetWindowHeight();
	}
	else if (width < 0 || height < 0)
		return false;

	glViewport(viewPortX, m_driver->GetWindowHeight()-viewPortY-viewPortHeight, viewPortWidth, viewPortHeight);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(x, width, height, y);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	return true;
}

bool Render::SetViewPort(int x, int y, int width, int height)
{
	glViewport(x,y,width,height);
	return true;
}

float Render::GetSrceenWidth() const
{
	return (float)m_driver->GetWindowWidth();
}

float Render::GetScreenHeight() const
{
	return (float)m_driver->GetWindowHeight();
}

bool Render::Leave2DMode()
{	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	return true;
}

bool Render::UseShadowMap(bool use)
{
	if (use)
	{
		if (m_shadowTexture != 0)
			glDeleteTextures(1, &m_shadowTexture);
		glGenTextures(1, &m_shadowTexture);
		glBindTexture(GL_TEXTURE_2D, m_shadowTexture);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
			PUNK_SHADOW_MAP_WIDTH, PUNK_SHADOW_MAP_HEIGHT, 0,
			GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL );

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL );
		glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,
			GL_COMPARE_R_TO_TEXTURE );

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

		glPolygonOffset(2, 2);
		/*		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		glTexGeni( GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
		/**/
		glCullFace( GL_BACK );

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_LIGHT0 );
		glEnable( GL_LIGHTING );
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_TEXTURE_GEN_S );
		glEnable( GL_TEXTURE_GEN_T );
		glEnable( GL_TEXTURE_GEN_R );
		glEnable( GL_TEXTURE_GEN_Q );
		glEnable( GL_COLOR_MATERIAL );
		glEnable( GL_CULL_FACE );

		m_useShadowMap = true;
	}
	else
	{
		glDeleteTextures(1, &m_shadowTexture);
		glDisable( GL_TEXTURE_GEN_S );
		glDisable( GL_TEXTURE_GEN_T );
		glDisable( GL_TEXTURE_GEN_R );
		glDisable( GL_TEXTURE_GEN_Q );

		m_useShadowMap = false;
	}

	return true;
}

bool Render::SetFont(const char* fontName, int size)
{
	return m_textRender->SetFont(fontName, size);
}

bool Render::GenerateTextureMatrix()
{
	ILightManager* lightManager = m_driver->GetScene()->GetLightManager();

	glBindTexture(GL_TEXTURE_2D, m_shadowTexture);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_Q);

	float PS[] = {1, 0, 0, 0};
	float PT[] = {0, 1, 0, 0};
	float PR[] = {0, 0, 1, 0};
	float PQ[] = {0, 0, 0, 1};

	glTexGenfv(GL_S, GL_EYE_PLANE, PS);
	glTexGenfv(GL_T, GL_EYE_PLANE, PT);
	glTexGenfv(GL_R, GL_EYE_PLANE, PR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, PQ);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5f, 0.5f, 0.5f);
	glScalef(0.5f, 0.5f, 0.5f);
	gluPerspective(2*lightManager->GetLight(0)->GetSpotCutoff(), PUNK_SHADOW_MAP_WIDTH/PUNK_SHADOW_MAP_HEIGHT, m_zNear, m_zFar);
	const float* lightDir = lightManager->GetLight(0)->GetSpotDirection();
	const float* lightPos = lightManager->GetLight(0)->GetPosition();
	gluLookAt(lightPos[0], lightPos[1], lightPos[2], 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);

	/*	    GLfloat  tmpMatrix[16];

	glPushMatrix();
	glLoadIdentity();
	glTranslatef( 0.5, 0.5, 0.0 );
	glScalef( 0.5, 0.5, 1.0 );
	gluPerspective( 60.0, 1.0, 1.0, 1000.0 );
	GLfloat lightPos[4];
	const float* lightDir = m_lightManager.GetLight(0)->GetSpotDirection();
	glGetLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	gluLookAt( lightPos[0], lightPos[1], lightPos[2], lightPos[0]+lightDir[0], lightPos[1]+lightDir[1], lightPos[2]+lightDir[2], 0, 1, 0 );
	//gluLookAt(5,0,5, 0, 0, 0, 0, 1, 0);
	glGetFloatv( GL_MODELVIEW_MATRIX, tmpMatrix );
	glPopMatrix();

	transposeMatrix( tmpMatrix );

	glBindTexture(GL_TEXTURE_2D, m_shadowTexture);
	glTexGenfv( GL_S, GL_OBJECT_PLANE, &tmpMatrix[0] );
	glTexGenfv( GL_T, GL_OBJECT_PLANE, &tmpMatrix[4] );
	glTexGenfv( GL_R, GL_OBJECT_PLANE, &tmpMatrix[8] );
	glTexGenfv( GL_Q, GL_OBJECT_PLANE, &tmpMatrix[12] );
	/**/
	return true;
}

bool Render::RenderStatistic()
{
	IScene* scene = m_driver->GetScene();
	static int count = 0;
	static int oldCount = 0;
	static float time = 0;
	float x = 10.0f;
	float y = 40.0f;
	Enter2DMode();
	SetColor(1,1,1,1);
	RenderText(x,y,0,0,"Mesh count: %d", 0);
	y += 20.0f;
	RenderText(x,y,0,0,"Texture count: %d", 0);
	y += 20.0f;
	RenderText(x, y, 0, 0, "Image count: %d", 0);
	y += 20.0f;
	RenderText(x, y, 0, 0, "FPS: %d", 0);	
	//time += m_time.GetTimeFromLastGetTime();
	count++;
	if (time > 1)
	{
		oldCount = count;
		count = 0;
		time = 0;
	}
	Leave2DMode();	
	return true;
}

void Render::SetZFar(float value)
{
	m_zFar = value;
}

void Render::SetZNear(float value)
{
	m_zNear = value;
}

float Render::GetZFar() const
{
	return m_zFar;
}

float Render::GetZNear() const
{
	return m_zNear;
}

bool Render::BeginRender(RenderTarget target)
{
	ILightManager* lightManager = m_driver->GetScene()->GetLightManager();
	lightManager->SetAmbient(.6,.6,.6,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	m_driver->GetScene()->GetCamera()->Apply();
	return true;
}


bool Render::EndRender(RenderTarget target)
{
	m_driver->SwapBuffers();
	return true;
}

void Render::SetGUIManager(IGUIManager *guiManager)
{
	m_guiManager = guiManager;
	m_driver->SetGUIManager(m_guiManager);
}