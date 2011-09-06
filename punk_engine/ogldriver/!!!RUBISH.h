
class Mesh
{
	void* data;
};

//
	//	Setup window elements identifiers
	//
	const int SETUP_ADAPTER_COMBOBOX		1;
	const int SETUP_FULLSCREEN_CHECKBOX		2;
	const int SETUP_MODES_COMBOBOX			3;
	const int SETUP_OK_BUTTON				4;

	//
	//	Setup window child windows
	//
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

		//
	//	i don't know what for do i need that for now
	//
	namespace DriverInfo
	{
		static const PunkString m_keyWords[] = {"get_screen_width",
			"get_screen_height",
			"get_gl_extensions"};

		static const int NOT_FOUND = -1;
		static const int FIRST_COMMAND = 0;
		static const int GET_SCREEN_WIDTH = 0;
		static const int GET_SCREEN_HEIGHT = 1;
		static const int GET_GL_ENSIONS = 2;
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
			static std::vector<PunkString> GetScreenWidth(Driver* driver);
			static std::vector<PunkString> GetScreenHeight(Driver* driver);
			static std::vector<PunkString> GetGLExtensions(Driver* driver);
		};
	}
		friend LRESULT CALLBACK UserWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

				bool ReadSetupFile(const char* filename);
		bool CreateUserWindow();
		bool CreateSetupWindow();	

		const float g_zNear = 0.01f;
const float g_zFar = 1000.0f;

const float g_zShadowNear = 1.0f;
const float g_zShadowFar = 20.0f;

bool Driver::ReadSetupFile(const char* filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rt");
	if (!f)
		CreateSetupWindow();
	fopen_s(&f, filename, "rt");
	if (!f)
		return false;
	fscanf_s(f, "%d%d%d%d", &m_screen.width, &m_screen.height, &m_screen.bitsPerPixel, &m_screen.refresh);
	fscanf_s(f, "%d", &m_screen.fullScreen);
	fclose(f);
	return true;
}

	if (!ReadSetupFile("video.cfg"))
		return false;
	if (!CreateUserWindow())
		return false;

//
	//log
			const char* version = (const char*)glGetString(GL_VERSION);
		MessageBoxA(0, version, "Version", MB_OK|MB_ICONINFORMATION);

		///////////////
			LRESULT CALLBACK UserWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static Driver* driver;

		switch(msg)
		{
		case WM_KEYUP:
			if (driver->m_guiManager)
				driver->m_guiManager->KeyUp(wParam, (KeyFlags)lParam);
			break;
		case WM_SYSKEYDOWN:
			if (wParam == VK_RETURN && lParam)		//?????????
			{
				driver->m_screen.fullScreen = !driver->m_screen.fullScreen;
				driver->Reboot();			
				return S_OK;
			}

			break;
		case WM_KEYDOWN:	
			if (driver->m_guiManager)
				driver->m_guiManager->KeyDown(wParam, (KeyFlags)lParam);
			if (wParam == 'p' || wParam == 'P')
				driver->MakeScreenShot();
			break;
		case WM_CHAR:
			if (driver->m_guiManager)
				driver->m_guiManager->KeyChar(wParam, (KeyFlags)lParam);
			break;
		case WM_MOUSEMOVE:
			{
				if (driver->m_guiManager)
					driver->m_guiManager->MouseMove(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
				static WORD x = 500;
				static WORD y = 500;
				ICamera* camera = driver->GetScene()->GetCamera();
				camera->Pitch(float(x-LOWORD(lParam)));
				camera->Heading(-1.0f*float(y-HIWORD(lParam)));
				x = LOWORD(lParam);
				y = HIWORD(lParam);				
			}
			break;
		case WM_MOUSEWHEEL:
			{
				if (driver->m_guiManager)
					driver->m_guiManager->MouseWheel(GET_WHEEL_DELTA_WPARAM(wParam)/WHEEL_DELTA, LOWORD(lParam), HIWORD(lParam), (MouseFlags)HIWORD(wParam)); 
				int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
				ICamera* camera = driver->GetScene()->GetCamera();
				camera->MoveNorth(0.005f*float(zDelta));
			}
			break;
		case WM_LBUTTONDBLCLK:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseLeftButtonDoubleClick(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_LBUTTONDOWN:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseLeftButtonDown(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_LBUTTONUP:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseLeftButtonUp(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_RBUTTONDBLCLK:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseRightButtonDoubleClick(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_RBUTTONDOWN:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseRightButtonDown(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_RBUTTONUP:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseRightButtonUp(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_MBUTTONDBLCLK:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseMiddleButtonDoubleClick(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_MBUTTONDOWN:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseMiddleButtonDown(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_MBUTTONUP:
			if (driver->m_guiManager)
				driver->m_guiManager->MouseMiddleButtonUp(LOWORD(lParam), HIWORD(lParam), (MouseFlags)wParam);
			break;
		case WM_CREATE:
			{
				CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
				driver = (Driver*)cs->lpCreateParams;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			driver->Resize();
			if (driver->m_guiManager)
				driver->m_guiManager->Resize(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
/*
	bool Driver::CreateUserWindow()
	{
		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hInstance = GetModuleHandle(0);
		wc.lpfnWndProc = UserWindowProc;
		wc.lpszClassName = T("Punk Render");
		wc.lpszMenuName = 0;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		if (!RegisterClass(&wc))
			return false;

		RECT rect;
		rect.left = 0;
		rect.right = m_screen.width;
		rect.top = 0;
		rect.bottom = m_screen.height;


		DWORD style = 0;
		DWORD styleEx = 0;
		if (m_screen.fullScreen)
		{
			style = WS_POPUP;
			styleEx = WS_EX_APPWINDOW;
		}
		else
		{
			style = WS_OVERLAPPEDWINDOW;
			styleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		}

		AdjustWindowRectEx(&rect, style, false, styleEx);

		m_window = CreateWindowEx(styleEx, T("Punk Render"), T("Punk Engine"), style,
			0, 0, rect.right-rect.left, rect.bottom-rect.top, 0, 0, GetModuleHandle(0), (void*)this);

		GetClientRect(m_window, &rect);
		ShowWindow(m_window, SW_SHOW);
		UpdateWindow(m_window);

		return true;
	}
*/
	//
	//
	//
		bool EnumDevices()
	{
		DISPLAY_DEVICE device;
		device.cb = sizeof(device);
		DWORD i = 0;
		while (EnumDisplayDevices(0, i, &device, 0) != 0)
		{
			SendMessage(g_setupWindow.adapterCombo, CB_ADDSTRING, 0, (LPARAM)device.DeviceString);
			i++;
		}
		return true;
	}

	bool EnumModes(int adapter)
	{
		SendMessage(g_setupWindow.modesCombo, CB_RESETCONTENT, 0, 0);
		DISPLAY_DEVICE device;
		device.cb = sizeof(device);
		if (EnumDisplayDevices(0, adapter, &device, 0) == 0)
			return false;

		DEVMODE mode;
		ZeroMemory(&mode, sizeof(mode));
		mode.dmSize = sizeof(mode);
		DWORD modeNum = 0;
		while (EnumDisplaySettings(device.DeviceName, modeNum, &mode) != 0)
		{
			Char buf[256];
			_itot_s(mode.dmPelsWidth, buf, 256, 10);
			PunkString str;
			str += buf;
			str += PUNK_T(" ");
			_itot_s(mode.dmPelsHeight, buf, 256, 10);
			str += buf;
			str += PUNK_T(" ");
			_itot_s(mode.dmBitsPerPel, buf, 256, 10);
			str += buf;
			str += PUNK_T(" ");
			_itot_s(mode.dmDisplayFrequency, buf, 256, 10);
			str += buf;

			SendMessage(g_setupWindow.modesCombo, CB_ADDSTRING, 0, (LPARAM)str.CString());

			modeNum++;
		}
		return true;
	}

	bool SaveSettings()
	{
		FILE* f = 0;
		fopen_s(&f, "video.cfg", "wt");
		Char buf[512];
		Char buf2[512];
		ZeroMemory(buf2, sizeof(buf2));
		ZeroMemory(buf, 512);
		SendMessage(g_setupWindow.modesCombo, CB_GETLBT, (WPARAM)SendMessage(g_setupWindow.modesCombo, CB_GETCURSEL, 0, 0), (LPARAM)buf);
		//	WideCharToMultiByte(CP_ACP, 0, buf, wcslen(buf), buf2, 512, 0, 0);
		fprintf(f, "%s\n", buf);
		int check = (int)SendMessage(g_setupWindow.fullscreenCheck, BM_GETCHECK, 0, 0);
		fprintf(f, "%d\n", check);
		fclose(f);
		return true;
	}

	LRESULT CALLBACK SetupWindowFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
					{
						switch(LOWORD(wParam))
						{
						case SETUP_OK_BUTTON:
							SaveSettings();
							PostQuitMessage(0);
							break;
						case SETUP_FULLSCREEN_CHECKBOX:
							SendMessage(g_setupWindow.fullscreenCheck, BM_SETCHECK, (SendMessage(g_setupWindow.fullscreenCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) ? BST_UNCHECKED : BST_CHECKED, 0);
							break;
						}
					}
				case CBN_SELENDOK:
					{
						switch (LOWORD(wParam))
						{
						case SETUP_ADAPTER_COMBOBOX:
							EnumModes(SendMessage(g_setupWindow.adapterCombo, CB_GETCURSEL, 0, 0));
							break;
						}
					}
					break;
				}
			}
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	bool Driver::CreateSetupWindow()
	{
		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpfnWndProc = SetupWindowFunc;
		wc.lpszClassName = T("Punk OGL Setup");
		wc.lpszMenuName = 0;
		wc.style = 0;

		if (!RegisterClass(&wc))
			return false;

		int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
		int desktopHeight = GetSystemMetrics(SM_CYSCREEN);
		int windowWidth = 400;
		int windowHeight = 400;

		g_setupWindow.window = CreateWindowEx(0, T("Punk OGL Setup"), T("Punk OpenGL Video Driver Setup"), 
			WS_SYSMENU, desktopWidth/2 - windowWidth/2, desktopHeight/2 - windowHeight/2,
			windowWidth, windowHeight, 0, 0, GetModuleHandle(0), 0);

		g_setupWindow.adapterCombo = CreateWindowEx(0, WC_COMBOBOX, NULL, WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,
			10, 10, 200, 200, g_setupWindow.window, (HMENU)SETUP_ADAPTER_COMBOBOX, GetModuleHandle(0), 0);

		g_setupWindow.fullscreenCheck = CreateWindowEx(0, WC_BUTTON, T("Full Screen"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX, 230, 10,
			200, 20, g_setupWindow.window, (HMENU)SETUP_FULLSCREEN_CHECKBOX, GetModuleHandle(0), 0);

		g_setupWindow.modesCombo = CreateWindowEx(0, WC_COMBOBOX, NULL, WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,
			10, 50, 200, 200, g_setupWindow.window, (HMENU)SETUP_MODES_COMBOBOX, GetModuleHandle(0), 0);

		g_setupWindow.okButton = CreateWindowEx(0, WC_BUTTON, T("Ok"), WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
			windowWidth/2-100, windowHeight-50, 200, 20, g_setupWindow.window, (HMENU)SETUP_OK_BUTTON, GetModuleHandle(0), 0);

		EnumDevices();

		ShowWindow(g_setupWindow.window, SW_SHOW);
		UpdateWindow(g_setupWindow.window);

		MSG msg;

		while (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ShowWindow(g_setupWindow.window, SW_HIDE);
		UnregisterClass(T("Punk OGL Setup"), GetModuleHandle(0));
		return true;
	}

	HDC Driver::GetDC()
	{
		return m_deviceContext;
	}

	HWND Driver::GetWnd()
	{
		return m_window;
	}

	int Driver::GetWindowWidth() const 
	{
		return m_screen.width;
	}

	int Driver::GetWindowHeight() const
	{
		return m_screen.height;
	}

	std::vector<PunkString> Driver::Request(const PunkString &request)
	{
		int id = DriverInfo::CommandToID(request);
		switch(id)
		{
		case DriverInfo::GET_SCREEN_HEIGHT:
			return DriverInfo::Info::GetScreenHeight(this);
			break;
		case DriverInfo::GET_SCREEN_WIDTH:
			return DriverInfo::Info::GetScreenWidth(this);
			break;
		case DriverInfo::GET_GL_ENSIONS:
			return DriverInfo::Info::GetGLExtensions(this);
			break;
		default:
			{
				std::vector<PunkString> list;
				list.push_back(PunkString("unknown command: ") + request);
				return list;
			}
		};
	}
