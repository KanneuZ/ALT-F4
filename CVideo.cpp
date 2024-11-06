#include "CVideo.h"

CVideo::CVideo() {}

CVideo::~CVideo() {
    if (pBuild) { pBuild->Release(); pBuild = NULL; }
	if (pGraph) { pGraph->Release(); pGraph = NULL; }
	if (pCap) { pCap->Release(); pCap = NULL; }
	if (pMoniker) { pMoniker->Release(); pMoniker = NULL; }
	if (pEnum) { pEnum->Release(); pEnum = NULL; }
	if (pDevEnum) { pDevEnum->Release(); pDevEnum = NULL; }
	if (pControl) { pControl->Release(); pControl = NULL; }
	if (pWindow) { pWindow->Release(); pWindow = NULL; }
	CoUninitialize();
}

void CVideo::Inisialise() {
	HRESULT hr;

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) { /*Handle Error*/ }
	
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pBuild);
	if (FAILED(hr)) { /*Handle Error*/ }

	hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IFilterGraph, (void**)&pGraph);
	if (FAILED(hr)) { /*Handle Error*/ }

	pBuild->SetFiltergraph(pGraph);
	
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));
	if (FAILED(hr)) { /*Handle Error*/ }

	hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
	if (FAILED(hr)) { /*Handle Error*/ }

    hr = pEnum->Next(1, &pMoniker, NULL);
    if (FAILED(hr)) { /*Handle Error*/ }

	hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pCap);
	if (FAILED(hr)) { /*Handle Error*/ }

	hr = pGraph->AddFilter(pCap, L"Capture Filter");
	if (FAILED(hr)) { /*Handle Error*/ }

	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	if (FAILED(hr)) { /*Handle Error*/ }

	hr = pGraph->QueryInterface(IID_IVideoWindow, (void**)&pWindow);
	if (FAILED(hr)) { /*Handle Error*/ }

    hr = pGraph->QueryInterface(IID_PPV_ARGS(&pControl));
    if (FAILED(hr)) { /*Handle Error*/ }

    hr = pGraph->QueryInterface(IID_PPV_ARGS(&pEvent));
    if (FAILED(hr)) { /*Handle Error*/ }

	hr = pBuild->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, pCap, NULL, NULL);
	if (FAILED(hr)) { /*Handle Error*/ }
}

void CVideo::Start() { pControl->Run(); IsRun = true; }
void CVideo::Stop() { pControl->Stop(); IsRun = false; }
bool CVideo::GetIsRun() { return IsRun; }

void CVideo::GetCurrentFrame() {
	return;
}

void CVideo::SetWindow(int x, int y) {
	pWindow->put_Top(x);
	pWindow->put_Left(y);
}

void CVideo::SetWh(HWND h) { 
	hw = h; 
	pWindow->put_Owner((OAHWND)hw); 
	pWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
	pWindow->put_Top(0);
	pWindow->put_Left(0);
}

HWND CVideo::GetWh() { return HWND(); }

int CVideo::GetWidth(){ 
	long a;
	if (SUCCEEDED(pWindow->get_Width(&a))) return a;
}

int CVideo::GetHight(){ 
	long a;
	if (SUCCEEDED(pWindow->get_Height(&a))) return a;
}

void CVideo::SetIsShow(bool f) { pWindow->put_AutoShow(IsShowing=f); }
bool CVideo::GetIsShow() { return IsShowing; }
