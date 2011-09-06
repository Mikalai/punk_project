#include "../PunkEngine/common/IDriver.h"
#include "../PunkEngine/common/types.h"
#include "../System/Time/time.h"

#include "Render.h"
#include "Scene.h"
#include "Extensions.h"


#define SETUP_ADAPTER_COMBOBOX		1
#define SETUP_FULLSCREEN_CHECKBOX	2
#define SETUP_MODES_COMBOBOX		3
#define SETUP_OK_BUTTON				4

struct TSetupWindow
{
	HWND window;
	HWND adapterCombo;
	HWND fullscreenCheck;
	HWND modesCombo;
	HWND okButton;
};

static TSetupWindow g_setupWindow;

LRESULT CALLBACK UserWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace DriverInfo
{
	static const PunkString m_keyWords[] = {"get_screen_width",
	"get_screen_height",
	"get_gl_extensions"};

	static const int NOT_FOUND = -1;
	static const int FIRST_COMMAND = 0;
	static const int GET_SCREEN_WIDTH = 0;
	static const int GET_SCREEN_HEIGHT = 1;
	static const int GET_GL_EXTENSIONS = 2;
	static const int LAST_COMMAND = 3;

	inline int CommandToID(const PunkString& command)
	{
		for (int i = FIRST_COMMAND; i < LAST_COMMAND; i++)
		{
			if (command == m_keyWords[i])
				return i;
		}
		return -1;
	}

	class Info
	{
	public:
		static std::vector<PunkString> GetScreenWidth(TDriver* driver);
		static std::vector<PunkString> GetScreenHeight(TDriver* driver);
		static std::vector<PunkString> GetGLExtensions(TDriver* driver);
	};
}

class TDriver : public IDriver
{
	friend class DriverInfo::Info;
public:
	TDriver();
	virtual ~TDriver();
	virtual bool Init();
	virtual bool Reset();
	virtual bool CreateSetupWindow();	
	virtual bool MakeScreenShot();	
	virtual bool Resize();
	virtual IScene* GetScene();
	virtual IRender* GetRender();
	virtual bool SwapBuffers();
	virtual std::vector<PunkString> Request(const PunkString& request);
	HDC GetDC();
	HWND GetWnd();
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	bool SetGUIManager(IGUIManager* guiManager);
	bool IsExtensionSupported(const char* extension);
	int GetMaxTextureUnits() const;
	bool Reboot();
private:
	bool Clear();
	bool ReadSetupFile(const char* filename);
	bool CreateUserWindow();
	bool InitOpenGL();
	bool InitView();

	struct ScreenDesc
	{
		unsigned width;
		unsigned height;
		unsigned bitsPerPixel;
		unsigned refresh;
		GLint viewport[4];
		bool fullScreen;
	};

	ScreenDesc m_screen;
	HWND m_window;
	HDC m_deviceContext;
	HGLRC m_oglContext;
	GLuint m_pixelFormat;

	Time m_time;
	IGUIManager* m_guiManager;
	Render* m_render;
	Scene* m_scene;
	friend LRESULT CALLBACK UserWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

extern TDriver* g_driver;