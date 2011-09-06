//#include "../Util/Util.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <commctrl.h>
#include <algorithm>
#endif

#ifdef _WIN64
#include <windows.h>
#endif

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>
#include "Driver.h"

const float g_zNear = 0.01f;
const float g_zFar = 1000.0f;

const float g_zShadowNear = 1.0f;
const float g_zShadowFar = 20.0f;

TDriver::TDriver() : m_guiManager(NULL)
{	
}

bool TDriver::ReadSetupFile(const char* filename)
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

bool TDriver::Init()
{
	if (!ReadSetupFile("video.cfg"))
		return false;
	if (!CreateUserWindow())
		return false;
	if (!InitOpenGL())
		return false;
	if (!InitView())
		return false;
	const char* version = (const char*)glGetString(GL_VERSION);
	MessageBoxA(0, version, "Version", MB_OK|MB_ICONINFORMATION);
	return true;
}

bool TDriver::InitView()
{
	glViewport(0, 0, m_screen.width, m_screen.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)m_screen.width/(GLdouble)m_screen.height, g_zNear, g_zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4,4,4, 0, 0, 0, 0, 1, 0);
	return true;
}

bool TDriver::Resize()
{
	if (!m_screen.fullScreen)
	{
		RECT rect;
		GetClientRect(m_window, &rect);
		m_screen.width = rect.right - rect.left;
		m_screen.height = rect.bottom - rect.top;
	}
	glViewport(0,0,m_screen.width, m_screen.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)m_screen.width/(GLdouble)m_screen.height, g_zNear, g_zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4,4,4, 0, 0, 0, 0, 1, 0);
	return true;
}

bool TDriver::InitOpenGL()
{
	m_deviceContext = ::GetDC(m_window);

	if (m_screen.fullScreen)
	{
		DEVMODE mode;
		ZeroMemory(&mode, sizeof(mode));
		mode.dmSize = sizeof(mode);
		mode.dmPelsWidth = m_screen.width;
		mode.dmPelsHeight = m_screen.height;
		mode.dmBitsPerPel = m_screen.bitsPerPixel;
		mode.dmDisplayFrequency = m_screen.refresh;
		mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

		MoveWindow(m_window, 0, 0, m_screen.width, m_screen.height, TRUE);

		if (ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			return false;
	}

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(pfd),
		1, 
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		m_screen.bitsPerPixel,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0, 
		0, 0, 0
	};

	if (!(m_pixelFormat = ChoosePixelFormat(m_deviceContext, &pfd)))
		return false;

	if (!SetPixelFormat(m_deviceContext, m_pixelFormat, &pfd))
		return false;

	if ((m_oglContext = wglCreateContext(m_deviceContext)) == NULL)
		return false;

	if (!wglMakeCurrent(m_deviceContext, m_oglContext))
		return false;

	SetFocus(m_window);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	//glEnable( GL_CULL_FACE );

	m_scene = new Scene(this);
	m_render = new Render(this);

	Extensions::InitExtensions();
	return true;
}

bool TDriver::Reboot()
{	
	if (!m_screen.fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
		MoveWindow(m_window, 100, 100, m_screen.width, m_screen.height, TRUE);
	}
	else
	{
		ReadSetupFile("video.cfg");
		m_screen.fullScreen = true;
		DEVMODE mode;
		ZeroMemory(&mode, sizeof(mode));
		mode.dmSize = sizeof(mode);
		mode.dmPelsWidth = m_screen.width;
		mode.dmPelsHeight = m_screen.height;
		mode.dmBitsPerPel = m_screen.bitsPerPixel;
		mode.dmDisplayFrequency = m_screen.refresh;
		mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

		MoveWindow(m_window, 0, 0, m_screen.width, m_screen.height, TRUE);

		if (ChangeDisplaySettings(&mode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			return false;
		
		ShowCursor(FALSE);
	}


	if (m_screen.fullScreen)
	{
		SetWindowLong(m_window, GWL_STYLE, WS_POPUP);
		SetWindowLong(m_window, GWL_EXSTYLE, WS_EX_APPWINDOW);
	}
	else
	{
		SetWindowLong(m_window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowLong(m_window, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);				
	}

	ShowWindow(m_window, SW_SHOW);
	UpdateWindow(m_window);
	//return InitOpenGL();
	return true;
}

LRESULT CALLBACK UserWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static TDriver* driver;
	
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
			driver = (TDriver*)cs->lpCreateParams;
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

bool TDriver::CreateUserWindow()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = UserWindowProc;
	wc.lpszClassName = TEXT("Punk Render");
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

	m_window = CreateWindowEx(styleEx, TEXT("Punk Render"), TEXT("Punk Engine"), style,
		0, 0, rect.right-rect.left, rect.bottom-rect.top, 0, 0, GetModuleHandle(0), (void*)this);

	GetClientRect(m_window, &rect);
	ShowWindow(m_window, SW_SHOW);
	UpdateWindow(m_window);

	return true;
}

TDriver::~TDriver()
{
	DELETE_POINTER(m_render);
	DELETE_POINTER(m_scene);
}

bool TDriver::Reset()
{
	return Clear();	
}

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
		str += PUNK_TEXT(" ");
		_itot_s(mode.dmPelsHeight, buf, 256, 10);
		str += buf;
		str += PUNK_TEXT(" ");
		_itot_s(mode.dmBitsPerPel, buf, 256, 10);
		str += buf;
		str += PUNK_TEXT(" ");
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
	SendMessage(g_setupWindow.modesCombo, CB_GETLBTEXT, (WPARAM)SendMessage(g_setupWindow.modesCombo, CB_GETCURSEL, 0, 0), (LPARAM)buf);
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

bool TDriver::CreateSetupWindow()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = SetupWindowFunc;
	wc.lpszClassName = TEXT("Punk OGL Setup");
	wc.lpszMenuName = 0;
	wc.style = 0;

	if (!RegisterClass(&wc))
		return false;

	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowWidth = 400;
	int windowHeight = 400;

	g_setupWindow.window = CreateWindowEx(0, TEXT("Punk OGL Setup"), TEXT("Punk OpenGL Video Driver Setup"), 
		WS_SYSMENU, desktopWidth/2 - windowWidth/2, desktopHeight/2 - windowHeight/2,
		windowWidth, windowHeight, 0, 0, GetModuleHandle(0), 0);

	g_setupWindow.adapterCombo = CreateWindowEx(0, WC_COMBOBOX, NULL, WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,
		10, 10, 200, 200, g_setupWindow.window, (HMENU)SETUP_ADAPTER_COMBOBOX, GetModuleHandle(0), 0);

	g_setupWindow.fullscreenCheck = CreateWindowEx(0, WC_BUTTON, TEXT("Full Screen"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX, 230, 10,
		200, 20, g_setupWindow.window, (HMENU)SETUP_FULLSCREEN_CHECKBOX, GetModuleHandle(0), 0);

	g_setupWindow.modesCombo = CreateWindowEx(0, WC_COMBOBOX, NULL, WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,
		10, 50, 200, 200, g_setupWindow.window, (HMENU)SETUP_MODES_COMBOBOX, GetModuleHandle(0), 0);

	g_setupWindow.okButton = CreateWindowEx(0, WC_BUTTON, TEXT("Ok"), WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
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
	UnregisterClass(TEXT("Punk OGL Setup"), GetModuleHandle(0));
	return true;
}

HDC TDriver::GetDC()
{
	return m_deviceContext;
}

HWND TDriver::GetWnd()
{
	return m_window;
}

int TDriver::GetWindowWidth() const 
{
	return m_screen.width;
}

int TDriver::GetWindowHeight() const
{
	return m_screen.height;
}

bool TDriver::MakeScreenShot()
{
	FILE *f = 0;
	fopen_s(&f, "screenshot.bmp", "wb");
	if (f == 0)
		return false;
	try
	{
		GLubyte* data = 0;
		GLenum type = 0;
		if (m_screen.bitsPerPixel == 8)
		{
			type = GL_UNSIGNED_BYTE_2_3_3_REV;
			data = new GLubyte[m_screen.width*m_screen.height];
			memset(data, 0, m_screen.width*m_screen.height);
		}
		else if (m_screen.bitsPerPixel == 16)
		{
			type = GL_UNSIGNED_SHORT_4_4_4_4_REV;
			data = new GLubyte[m_screen.width*m_screen.height*2];
			memset(data, 0, m_screen.width*m_screen.height*2);
		}
		else if (m_screen.bitsPerPixel == 32)
		{
			type = GL_UNSIGNED_INT_8_8_8_8_REV;
			data = new GLubyte[m_screen.width*m_screen.height*4];
			memset(data, 0, m_screen.width*m_screen.height*4);
		}
		else
			return false;

		try
		{
			glReadPixels(0, 0, m_screen.width, m_screen.height, GL_RGBA, type, data);

			BITMAPFILEHEADER fileHeader;
			memset(&fileHeader, 0, sizeof(fileHeader));
			fileHeader.bfType = 19778;
			fileHeader.bfReserved1 = 0;
			fileHeader.bfReserved2 = 0;
			fileHeader.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+m_screen.width*m_screen.height*3;
			fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
			BITMAPINFOHEADER infoHeader;
			memset(&infoHeader, 0, sizeof(infoHeader));
			infoHeader.biSize = sizeof(infoHeader);
			infoHeader.biWidth = m_screen.width;
			infoHeader.biHeight = m_screen.height;
			infoHeader.biPlanes = 1;
			switch(type)
			{
			case GL_UNSIGNED_BYTE_2_3_3_REV:
				infoHeader.biBitCount = 8;
				break;
			case GL_UNSIGNED_SHORT_4_4_4_4_REV:
				infoHeader.biBitCount = 16;
				break;
			case GL_UNSIGNED_INT_8_8_8_8_REV:
				infoHeader.biBitCount = 24;
				break;
			default:
				return false;
			}			
			infoHeader.biCompression = BI_RGB;
			fwrite(&fileHeader, sizeof(fileHeader), 1, f);
			fwrite(&infoHeader, sizeof(infoHeader), 1, f);
			if (type == GL_UNSIGNED_INT_8_8_8_8_REV)
			{
				for (unsigned i = 0; i < m_screen.width*m_screen.height; i++)
				{
					fwrite(data + i*4 + 2, sizeof(data[0]), 1, f);
					fwrite(data + i*4 + 1, sizeof(data[0]), 1, f);
					fwrite(data + i*4, sizeof(data[0]), 1, f);
				}
			}
			else if (type == GL_UNSIGNED_SHORT_4_4_4_4_REV)
			{
				throw Exception(PUNK_TEXT("I don't know how to export 4 bits per red \
									 4 bits per green 4 bits per blue and 4 bits per alpha surface \
									 into bitmap with 16 bits per pixel"));
			}
			else if (type == GL_UNSIGNED_BYTE_2_3_3_REV)
			{
				throw Exception(PUNK_TEXT("Oh, the same shit like with 16 bits"));
			}

			DELETE_ARRAY(data);
		}
		catch(...)
		{
			DELETE_ARRAY(data);
			throw;
		}
		fclose(f);
	}
	catch(...)
	{
		fclose(f);
		throw;
	}
	return true;
}

bool TDriver::Clear()
{
	this->~TDriver();
	return true;
}

IScene* TDriver::GetScene()
{
	return m_scene;
}

IRender* TDriver::GetRender()
{
	return m_render;
}

bool TDriver::SetGUIManager(IGUIManager *guiManager)
{
	m_guiManager = guiManager;
	return true;
}

bool TDriver::SwapBuffers()
{
	return ::SwapBuffers(m_deviceContext) != 0;
}

std::vector<PunkString> TDriver::Request(const PunkString &request)
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
	case DriverInfo::GET_GL_EXTENSIONS:
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

bool TDriver::IsExtensionSupported(const char* ext)
{
	PunkString str =  (Char*)glGetString(GL_EXTENSIONS);
	std::vector<PunkString> list = str.Split(" ");
	std::vector<PunkString>::iterator i = std::find(list.begin(), list.end(), ext);
	if (i != list.end())
		return true;
	return false;
}

int TDriver::GetMaxTextureUnits() const
{
	int max = 0;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &max);
	return max;
}