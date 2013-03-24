#include "camera_capture_win32.h"
#include "../window/module.h"
#include "../logger.h"
#include <Vfw.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <dshow.h>

#include "../../system/profiler.h"
#include "../../system/environment.h"
#include "../../images/formats.h"
#include "../../images/converter/yuy2_to_rgb.h"
#include "../../gpu/common/texture2d.h"
#include "../../gpu/opengl/gl/module.h"
#include "../../system/timer.h"
#include "../../gpu/opencl/module.h"
#pragma comment (lib, "vfw32.lib")

namespace System
{	
	System::Timer g_timer;
	void* buffer;
	int* length;
	CRITICAL_SECTION* m_cs;

	void SetCriticalSection(CRITICAL_SECTION* cs)
	{
		m_cs = cs;
	}

	void SetTexture(void* value, int* len)
	{
		buffer = value;
		length = len;
	}

	HRESULT BuildPreviewGraph(ICaptureGraphBuilder2* pBuilder, IBaseFilter* pCap)
	{
		HRESULT hr = pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, pCap, nullptr, nullptr);
		if (FAILED(hr))
		{
			out_error() << "Can't build preview graph" << std::endl;
		}
		return hr;
	}

	HRESULT CreateFilter(IGraphBuilder* pGraph, IMoniker* pMoniker, IBaseFilter** pCap)
	{
		*pCap = NULL;
		HRESULT hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pCap);
		if (SUCCEEDED(hr))
		{
			hr = pGraph->AddFilter(*pCap, L"Capture Filter");
			if (FAILED(hr))
			{
				out_error() << "Can't add filter to graph builder" << std::endl;
			}
		}
		return hr;
	}

	HRESULT InitCaptureGraphBuilder(
		IGraphBuilder **ppGraph,  // Receives the pointer.
		ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
		)
	{
		if (!ppGraph || !ppBuild)
		{
			return E_POINTER;
		}
		IGraphBuilder *pGraph = NULL;
		ICaptureGraphBuilder2 *pBuild = NULL;

		// Create the Capture Graph Builder.
		HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, 
			CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pBuild );
		if (SUCCEEDED(hr))
		{
			// Create the Filter Graph Manager.
			hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER,
				IID_IGraphBuilder, (void**)&pGraph);
			if (SUCCEEDED(hr))
			{
				// Initialize the Capture Graph Builder.
				pBuild->SetFiltergraph(pGraph);

				// Return both interface pointers to the caller.
				*ppBuild = pBuild;
				*ppGraph = pGraph; // The caller must release both interfaces.
				return S_OK;
			}
			else
			{
				pBuild->Release();
			}
		}
		return hr; // Failed
	}

	HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum)
	{
		// Create the System Device Enumerator.
		ICreateDevEnum *pDevEnum;
		HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,  
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

		if (SUCCEEDED(hr))
		{
			// Create an enumerator for the category.
			hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
			if (hr == S_FALSE)
			{
				hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
			}
			pDevEnum->Release();
		}
		return hr;
	}

	void DisplayDeviceInformation(IEnumMoniker *pEnum)
	{
		IMoniker *pMoniker = NULL;

		while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
		{
			IPropertyBag *pPropBag;
			HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
			if (FAILED(hr))
			{
				pMoniker->Release();
				continue;  
			} 

			VARIANT var;
			VariantInit(&var);

			// Get description or friendly name.
			hr = pPropBag->Read(L"Description", &var, 0);
			if (FAILED(hr))
			{
				hr = pPropBag->Read(L"FriendlyName", &var, 0);
			}
			if (SUCCEEDED(hr))
			{
				out_message() << "Capture device: " << var.bstrVal << std::endl;
				VariantClear(&var); 
			}

			hr = pPropBag->Write(L"FriendlyName", &var);

			// WaveInID applies only to audio capture devices.
			hr = pPropBag->Read(L"WaveInID", &var, 0);
			if (SUCCEEDED(hr))
			{
				out_message() << "Audio device: " << var.lVal << std::endl;
				VariantClear(&var); 
			}

			hr = pPropBag->Read(L"DevicePath", &var, 0);
			if (SUCCEEDED(hr))
			{
				// The device path is not intended for display.
				out_message() << "Video device: " << var.bstrVal << std::endl;
				VariantClear(&var); 
			}

			pPropBag->Release();
			pMoniker->Release();
		}
	}

	//int w,h; HWND hwnd; MSG msg = {0}; BITMAPINFOHEADER bmih={0}; 

	//struct __declspec(  uuid("{71771540-2017-11cf-ae26-0020afd79767}")  ) CLSID_Sampler;	

	DWORD no;
#define DsHook(a,b,c) \
	if (!c##_) \
	{\
	INT_PTR* p=b+*(INT_PTR**)a;  \
	VirtualProtect(&c##_,4,PAGE_EXECUTE_READWRITE,&no);\
	*(INT_PTR*)&c##_=*p; \
	VirtualProtect(p,  4,PAGE_EXECUTE_READWRITE,&no);\
	*p=(INT_PTR)c; \
	}

	//
	GPU::OpenCL::Platform g_platform;
	GPU::OpenCL::Device g_device;
	GPU::OpenCL::Context g_context;
	GPU::OpenCL::Program g_program;
	GPU::OpenCL::CommandQueue g_command;
	GPU::OpenCL::Buffer g_inp;
	GPU::OpenCL::Buffer g_out;
	GPU::OpenCL::Kernel g_kernel;

	//

	void InitOpenCL()
	{
		g_platform.Init();
		g_device.Init(g_platform);
		g_context.Init(g_device);
		g_command.Init(g_context, g_device);
		g_program.Init(g_context, g_device, g_command);
		if (!g_program.CreateFromFile(System::Environment::Instance()->GetOpenCLFolder() + L"yuy2_to_rgb.cl"))
			exit(-1);

		g_inp.Init(g_context, g_command, GPU::OpenCL::Buffer::READ_WRITE, 640*480*2);
		g_out.Init(g_context, g_command, GPU::OpenCL::Buffer::READ_WRITE, 640*480*4);

		if (!g_program.GetKernel(L"yuy2_to_rgb", g_kernel))
			exit(-1);
	}

	HRESULT ( __stdcall * Receive_ ) ( void* inst, IMediaSample *smp ) ; 
	HRESULT   __stdcall   Receive    ( void* inst, IMediaSample *smp ) {     
		BYTE*     buf;    smp->GetPointer(&buf); DWORD len = smp->GetActualDataLength();
		//if (g_timer.GetElapsedTime() > 0.01)
		{
			EnterCriticalSection(m_cs);
			System::Profiler profiler;
			profiler.Start(L"Converting YUY2 to RGB");			
			g_kernel.SetArgument(0, g_inp);
			g_kernel.SetArgument(1, (int)len);
			g_kernel.SetArgument(2, g_out);
			g_inp.Write(buf, len);
			g_kernel.Call(640*480*2/4);
			g_out.Read(buffer, *length);
			//ImageModule::YUY2toRGB((unsigned char*)buf, len, (unsigned char*)buffer, length);		
			profiler.End();
			out_message() << profiler.ToString() << std::endl;
			LeaveCriticalSection(m_cs);
			g_timer.Reset();
		}
		HRESULT   ret  =  Receive_   ( inst, smp );   
		return    ret; 
	}

	void TestCamera()
	{
		InitOpenCL();
		//TCHAR szDeviceName[80];
		//TCHAR szDeviceVersion[80];

		//for (int wIndex = 0; wIndex < 10; wIndex++) 
		//{
		//	if (capGetDriverDescription(
		//		wIndex, 
		//		szDeviceName, 
		//		sizeof (szDeviceName), 
		//		szDeviceVersion, 
		//		sizeof (szDeviceVersion)
		//		)) 
		//	{
		//		// Append name to list of installed capture drivers
		//		// and then let the user select a driver to use.
		//	}
		//} 

		//HWND hWndC = capCreateCaptureWindow(TEXT("PunkCapture"),
		//	WS_CHILD | WS_VISIBLE, 0, 0, 160, 120, *System::Window::Instance(), 1);

		//SendMessage (hWndC, WM_CAP_DRIVER_CONNECT, 0, 0L); 
		//// 
		//// Or, use the macro to connect to the MSVIDEO driver: 
		//// fOK = capDriverConnect(hWndC, 0); 
		//// 
		//// Place code to set up and capture video here. 
		//// 
		////capDriverDisconnect (hWndC); 

		//CAPDRIVERCAPS CapDriverCaps = { }; 
		//CAPSTATUS     CapStatus = { };

		//capDriverGetCaps(hWndC, &CapDriverCaps, sizeof(CAPDRIVERCAPS)); 

		//// Video source dialog box. 
		//if (CapDriverCaps.fHasDlgVideoSource)
		//{
		//	capDlgVideoSource(hWndC); 
		//}

		//// Video format dialog box. 
		//if (CapDriverCaps.fHasDlgVideoFormat) 
		//{
		//	capDlgVideoFormat(hWndC); 

		//	// Are there new image dimensions?
		//	capGetStatus(hWndC, &CapStatus, sizeof (CAPSTATUS));

		//	// If so, notify the parent of a size change.
		//} 

		//// Video display dialog box. 
		//if (CapDriverCaps.fHasDlgVideoDisplay)
		//{
		//	capDlgVideoDisplay(hWndC); 
		//}


		HRESULT hr;
		IGraphBuilder*  graph= 0;  hr = CoCreateInstance( CLSID_FilterGraph, 0, CLSCTX_INPROC,IID_IGraphBuilder, (void **)&graph );
		IMediaControl*  ctrl = 0;  hr = graph->QueryInterface( IID_IMediaControl, (void **)&ctrl );

		ICreateDevEnum* devs = 0;  hr = CoCreateInstance (CLSID_SystemDeviceEnum, 0, CLSCTX_INPROC, IID_ICreateDevEnum, (void **) &devs);
		IEnumMoniker*   cams = 0;  hr = devs?devs->CreateClassEnumerator (CLSID_VideoInputDeviceCategory, &cams, 0):0;  
		IMoniker*       mon  = 0;  hr = cams->Next (1,&mon,0);  // get first found capture device (webcam?)    
		IBaseFilter*    cam  = 0;  hr = mon->BindToObject(0,0,IID_IBaseFilter, (void**)&cam);
		hr = graph->AddFilter(cam, L"Capture Source"); // add web cam to graph as source
		IEnumPins*      pins = 0;  hr = cam?cam->EnumPins(&pins):0;   // we need output pin to autogenerate rest of the graph
		IPin*           pin  = 0;  hr = pins?pins->Next(1,&pin, 0):0; // via graph->Render
		hr = graph->Render(pin); // graph builder now builds whole filter chain including MJPG decompression on some webcams
		IEnumFilters*   fil  = 0;  hr = graph->EnumFilters(&fil); // from all newly added filters
		IBaseFilter*    rnd  = 0;  hr = fil->Next(1,&rnd,0); // we find last one (renderer)
		hr = rnd->EnumPins(&pins);  // because data we are intersted in are pumped to renderers input pin 
		hr = pins->Next(1,&pin, 0); // via Receive member of IMemInputPin interface
		IMemInputPin*   mem  = 0;  hr = pin->QueryInterface(IID_IMemInputPin,(void**)&mem);

		DsHook(mem,6,Receive); // so we redirect it to our own proc to grab image data

		hr = ctrl->Run();   

	};


}

//HWND hWndC;
//void ConnectToCaptureDriver();
//void GetCapabilitiesOfCapture();
//void DisconnectFromCaptureDriver();
//void GetWindowStatus();
//void DisplaySettings();

//void Update()
//{
//	//capGrabFrameNoStop(hWndC);
//}

//void PreviewStart()
//{
//	//STEP 3: Setup the preview window size 

//	CAPSTATUS CapStatus;

//	capGetStatus(hWndC, &CapStatus, sizeof (CAPSTATUS)); 

//	::SetWindowPos(hWndC, NULL, 0, 0, CapStatus.uiImageWidth, CapStatus.uiImageHeight, SWP_NOZORDER | SWP_NOMOVE); 

//	//STEP 4: Previewing video

//	capPreview(hWndC, TRUE);       // start preview 

//	capPreviewRate(hWndC, 15);     // rate, in milliseconds, the frame rate here is just for preview window, not for capturing

//	capPreviewScale(hWndC,TRUE);
//}

//void PreviewStop()
//{

//	capPreview(hWndC, FALSE);        // disables preview 
//}

//void DisplaySettings()
//{
//	CAPDRIVERCAPS CapDriverCaps = { }; 
//	CAPSTATUS     CapStatus = { };

//	capDriverGetCaps(hWndC, &CapDriverCaps, sizeof(CAPDRIVERCAPS)); 

//	// Video source dialog box. 
//	if (CapDriverCaps.fHasDlgVideoSource)
//	{
//		capDlgVideoSource(hWndC); 
//	}

//	// Video format dialog box. 
//	if (CapDriverCaps.fHasDlgVideoFormat) 
//	{
//		capDlgVideoFormat(hWndC); 

//		// Are there new image dimensions?
//		capGetStatus(hWndC, &CapStatus, sizeof (CAPSTATUS));

//		// If so, notify the parent of a size change.
//	} 

//	// Video display dialog box. 
//	if (CapDriverCaps.fHasDlgVideoDisplay)
//	{
//		capDlgVideoDisplay(hWndC); 
//	}
//}

//void GetWindowStatus()
//{

//	CAPSTATUS CapStatus;

//	capGetStatus(hWndC, &CapStatus, sizeof (CAPSTATUS)); 

//	SetWindowPos(hWndC, NULL, 0, 0, CapStatus.uiImageWidth, 
//		CapStatus.uiImageHeight, SWP_NOZORDER | SWP_NOMOVE); 

//	out_message() << "Capture window status: " << std::endl;
//	out_message() << "Image width, in pixels: " << CapStatus.uiImageWidth << std::endl;
//	out_message() << "Image height, in pixels: " << CapStatus.uiImageHeight << std::endl;
//	out_message() << "Live window flag. The value of this member is TRUE if the window is displaying video using the preview method: " << CapStatus.fLiveWindow << std::endl;
//	out_message() << "Overlay window flag. The value of this member is TRUE if the window is displaying video using hardware overlay: " << CapStatus.fOverlayWindow << std::endl;
//	out_message() << "Input scaling flag. The value of this member is TRUE if the window is scaling the input video to the client area when displaying video using preview. This parameter has no effect when displaying video using overlay: " << CapStatus.fScale << std::endl;
//	out_message() << "The x- and y-offset of the pixel displayed in the upper left corner of the client area of the window: (" << CapStatus.ptScroll.x << ", " << CapStatus.ptScroll.y << ")" << std::endl;
//	out_message() << "Default palette flag. The value of this member is TRUE if the capture driver is using its default palette: " << CapStatus.fUsingDefaultPalette << std::endl;
//	out_message() << "Audio hardware flag. The value of this member is TRUE if the system has waveform-audio hardware installed: " << CapStatus.fAudioHardware << std::endl;
//	out_message() << "Capture file flag. The value of this member is TRUE if a valid capture file has been generated: " << CapStatus.fCapFileExists << std::endl;
//	out_message() << "Number of frames processed during the current (or most recent) streaming capture. This count includes dropped frames: " << CapStatus.dwCurrentVideoFrame << std::endl;
//	out_message() << "Number of frames dropped during the current (or most recent) streaming capture. Dropped frames occur when the capture rate exceeds the rate at which frames can be saved to file. In this case, the capture driver has no buffers available for storing data. Dropping frames does not affect synchronization because the previous frame is displayed in place of the dropped frame: " << CapStatus.dwCurrentVideoFramesDropped << std::endl;
//	out_message() << "Number of waveform-audio samples processed during the current (or most recent) streaming capture: " << CapStatus.dwCurrentWaveSamples << std::endl;
//	out_message() << "Time, in milliseconds, since the start of the current (or most recent) streaming capture: " << CapStatus.dwCurrentTimeElapsedMS << std::endl;
//	out_message() << "Handle to current palette: " << (DWORD)CapStatus.hPalCurrent << std::endl;
//	out_message() << "Capturing flag. The value of this member is TRUE when capturing is in progress: " << 
//		CapStatus.fCapturingNow << std::endl;
//	out_message() << "Error return values. Use this member if your application does not support an error callback function: " << CapStatus.dwReturn << std::endl;
//	out_message() << "Number of video buffers allocated. This value might be less than the number specified in the wNumVideoRequested member of the CAPTUREPARMS structure: " << CapStatus.wNumVideoAllocated << std::endl;
//	out_message() << "Number of audio buffers allocated. This value might be less than the number specified in the wNumAudioRequested member of the CAPTUREPARMS structure: " << CapStatus.wNumAudioAllocated << std::endl;

//}

//void ConnectToCaptureDriver()
//{
//	LRESULT fOk = SendMessage(hWndC, WM_CAP_DRIVER_CONNECT, 0, 0);
//	if (FAILED(fOk))
//		out_error() << "Can't connect to capture driver" << std::endl;

//	//	GetCapabilitiesOfCapture();
//	//GetWindowStatus();
//}

//void DisconnectFromCaptureDriver()
//{
//	capDriverDisconnect (hWndC);
//}

//void GetCapabilitiesOfCapture()
//{
//	CAPDRIVERCAPS CapDrvCaps; 

//	SendMessage (hWndC, WM_CAP_DRIVER_GET_CAPS, 
//		sizeof (CAPDRIVERCAPS), (LONG) (LPVOID) &CapDrvCaps); 

//	out_message() << "Index of the capture driver. An index value can range from 0 to 9: " << CapDrvCaps.wDeviceIndex << std::endl;
//	out_message() << "Video-overlay flag. The value of this member is TRUE if the device supports video overlay: "  << CapDrvCaps.fHasOverlay << std::endl;
//	out_message() << "Video source dialog flag. The value of this member is TRUE if the device supports a dialog box for selecting and controlling the video source: " << CapDrvCaps.fHasDlgVideoSource << std::endl;
//	out_message() << "Video format dialog flag. The value of this member is TRUE if the device supports a dialog box for selecting the video format: " << CapDrvCaps.fHasDlgVideoFormat << std::endl;
//	out_message() << "Video display dialog flag. The value of this member is TRUE if the device supports a dialog box for controlling the redisplay of video from the capture frame buffer: " << CapDrvCaps.fHasDlgVideoDisplay << std::endl;
//	out_message() << "Capture initialization flag. The value of this member is TRUE if a capture device has been successfully connected: " << CapDrvCaps.fCaptureInitialized << std::endl;
//	out_message() << "Driver palette flag. The value of this member is TRUE if the driver can create palettes: " << CapDrvCaps.fDriverSuppliesPalettes << std::endl;

//	// Or, use the macro to retrieve the driver capabilities. 
//	// capDriverGetCaps(hWndC, &CapDrvCaps, sizeof (CAPDRIVERCAPS)); 
//}

//void CreateCaptureWindow(int width, int height)
//{
//	hWndC = capCreateCaptureWindow (
//		TEXT("PunkCapture"),   // window name if pop-up 
//		WS_CHILD | WS_VISIBLE,       // window style 
//		0, 0, width, height,              // window position and dimensions
//		(HWND) *(System::Window::Instance()), 
//		(int)0); 

//	if (!hWndC)
//		out_error() << L"Unable to create capture window" << std::endl;
//	else
//		out_message () << "Capture window created successfully" << std::endl;

//	ConnectToCaptureDriver();

//	// OPTIONAL STEP: Setup frame rate
//	CAPTUREPARMS CaptureParms;
//	float FramesPerSec = 30.0;
//	capCaptureGetSetup(hWndC, &CaptureParms, sizeof(CAPTUREPARMS));
//	CaptureParms.dwRequestMicroSecPerFrame = (DWORD) (1.0e6 / FramesPerSec);
//	capCaptureSetSetup(hWndC, &CaptureParms, sizeof (CAPTUREPARMS));

//	// OPTIONAL STEP: Setup resolution
//	BITMAPINFO psVideoFormat;
//	capGetVideoFormat(hWndC, &psVideoFormat,sizeof(psVideoFormat));
//	psVideoFormat.bmiHeader.biWidth = 640;
//	psVideoFormat.bmiHeader.biHeight = 480;
//	capSetVideoFormat(hWndC, &psVideoFormat,sizeof(psVideoFormat));
//	capDriverDisconnect (hWndC, 0);//Can we do better?
//	capDriverConnect (hWndC, 0);  

//	//STEP 3: Setup the preview window size 
//	CAPSTATUS CapStatus;
//	capGetStatus(hWndC, &CapStatus, sizeof (CAPSTATUS)); 
//	::SetWindowPos(hWndC, NULL, 0, 0, CapStatus.uiImageWidth, CapStatus.uiImageHeight, SWP_NOZORDER | SWP_NOMOVE); 

//	//STEP 4: Previewing video
//	capPreview(hWndC, TRUE);       // start preview 
//	capPreviewRate(hWndC, 15);     // rate, in milliseconds, the frame rate here is just for preview window, not for capturing
//	capPreviewScale(hWndC,TRUE);

//	//CAPDRIVERCAPS CapDrvCaps; 

//	//capDriverGetCaps(hWndC, &CapDrvCaps, sizeof (CAPDRIVERCAPS)); 

//	//if (CapDrvCaps.fHasOverlay) 
//	//	capOverlay(hWndC, TRUE);

//	//CAPTUREPARMS p;
//	//capCaptureGetSetup(hWndC, &p, sizeof(p));
//	//p.fYield = TRUE;
//	//capCaptureSetSetup(hWndC, &p, sizeof(p));
//	//SendMessage (hWndC, WM_CAP_SEQUENCE_NOFILE, 0, 0L);
//	////capCaptureSequence(hWndC); 
//}

//void EnumerateCaptureDevices()
//{
//	TCHAR szDeviceName[80];
//	TCHAR szDeviceVersion[80];

//	for (int wIndex = 0; wIndex < 10; wIndex++) 
//	{
//		if (capGetDriverDescription(
//			wIndex, 
//			szDeviceName, 
//			sizeof (szDeviceName), 
//			szDeviceVersion, 
//			sizeof (szDeviceVersion)
//			)) 
//		{
//			out_message() << "Found capture device: " << szDeviceName << " (v. " << szDeviceVersion << ")" << std::endl;
//		}
//	} 
//}

//void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC)
//{
//	HANDLE hf;                  // file handle
//	BITMAPFILEHEADER hdr;       // bitmap file-header
//	PBITMAPINFOHEADER pbih;     // bitmap info-header
//	LPBYTE lpBits;              // memory pointer
//	DWORD dwTotal;              // total count of bytes
//	DWORD cb;                   // incremental count of bytes
//	BYTE *hp;                   // byte pointer
//	DWORD dwTmp;

//	pbih = (PBITMAPINFOHEADER) pbi;
//	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

//	if (!lpBits)
//	{
//		MessageBox(hwnd, TEXT("GlobalAlloc"), TEXT("Error"), MB_OK );
//	}
//	// Retrieve the color table (RGBQUAD array) and the bits
//	// (array of palette indices) from the DIB.
//	if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,DIB_RGB_COLORS))
//	{
//		MessageBox(hwnd, TEXT("GetDIBits"), TEXT("Error"), MB_OK);
//	}
//	// Create the .BMP file.
//	hf = CreateFile(pszFile,GENERIC_READ | GENERIC_WRITE,(DWORD) 0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,(HANDLE) NULL);
//	if (hf == INVALID_HANDLE_VALUE)
//	{
//		MessageBox( hwnd, TEXT("CreateFile"), TEXT("Error"), MB_OK);
//	}

//	hdr.bfType = 0x4d42;  // File type designator "BM" 0x42 = "B" 0x4d = "M"
//	// Compute the size of the entire file.
//	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage);
//	hdr.bfReserved1 = 0;
//	hdr.bfReserved2 = 0;
//	// Compute the offset to the array of color indices.
//	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD);
//	// Copy the BITMAPFILEHEADER into the .BMP file.
//	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp,  NULL) )
//	{
//		MessageBox(hwnd, TEXT("WriteFileHeader"), TEXT("Error"), MB_OK);
//	}
//	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
//	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof (RGBQUAD), (LPDWORD) &dwTmp, NULL))
//	{
//		MessageBox(hwnd, TEXT("WriteInfoHeader"), TEXT("Error"), MB_OK);
//	}
//	// Copy the array of color indices into the .BMP file.
//	dwTotal = cb = pbih->biSizeImage;
//	hp = lpBits;
//	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))
//	{
//		MessageBox(hwnd, TEXT("WriteFile"), TEXT("Error"), MB_OK);
//	}
//	// Close the .BMP file.
//	if (!CloseHandle(hf))
//	{
//		MessageBox(hwnd, TEXT("CloseHandle"), TEXT("Error"), MB_OK);
//	}

//	// Free memory.
//	GlobalFree((HGLOBAL)lpBits);
//}

//PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
//{
//	BITMAP bmp;
//	PBITMAPINFO pbmi;
//	WORD cClrBits;
//	// Retrieve the bitmap color format, width, and height.
//	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
//	{
//		MessageBox(hwnd, TEXT("GetObject"), TEXT("Error"), MB_OK);
//	}
//	// Convert the color format to a count of bits.
//	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
//	if (cClrBits == 1)
//		cClrBits = 1;
//	else if (cClrBits <= 4)
//		cClrBits = 4;
//	else if (cClrBits <= 8)
//		cClrBits = 8;
//	else if (cClrBits <= 16)
//		cClrBits = 16;
//	else if (cClrBits <= 24)
//		cClrBits = 24;
//	else cClrBits = 32;

//	// Allocate memory for the BITMAPINFO structure. (This structure
//	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD
//	// data structures.)

//	if (cClrBits != 24)
//	{
//		pbmi = (PBITMAPINFO) LocalAlloc(LPTR,sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));
//	}
//	// There is no RGBQUAD array for the 24-bit-per-pixel format.
//	else
//		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));

//	// Initialize the fields in the BITMAPINFO structure.
//	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//	pbmi->bmiHeader.biWidth = bmp.bmWidth;
//	pbmi->bmiHeader.biHeight = bmp.bmHeight;
//	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
//	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
//	if (cClrBits < 24)
//	{
//		pbmi->bmiHeader.biClrUsed = (1<<cClrBits);
//	}
//	// If the bitmap is not compressed, set the BI_RGB flag.
//	pbmi->bmiHeader.biCompression = BI_RGB;

//	// Compute the number of bytes in the array of color
//	// indices and store the result in biSizeImage.
//	// For Windows NT, the width must be DWORD aligned unless
//	// the bitmap is RLE compressed. This example shows this.
//	// For Windows 95/98/Me, the width must be WORD aligned unless the
//	// bitmap is RLE compressed.
//	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8 * pbmi->bmiHeader.biHeight;
//	// Set biClrImportant to 0, indicating that all of the
//	// device colors are important.
//	pbmi->bmiHeader.biClrImportant = 0;

//	return pbmi; //return BITMAPINFO
//}
//}