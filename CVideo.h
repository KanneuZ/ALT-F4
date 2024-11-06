#pragma once
#include <windows.h>
#include <dshow.h>

class CVideo {
    private:
        HWND hw;
        IVideoWindow *pWindow = NULL;

        bool IsShowing = true;        
        bool IsRun;

        ICaptureGraphBuilder2 *pBuild = NULL;
        IGraphBuilder *pGraph = NULL;
        IBaseFilter *pCap = NULL;
        IMoniker *pMoniker = NULL;
        IEnumMoniker *pEnum = NULL;
        ICreateDevEnum *pDevEnum = NULL;
        IMediaControl *pControl = NULL;
        IMediaEventEx *pEvent = NULL;
        IBaseFilter *pGrabberF = NULL;
        IVMRFilterConfig* pConfig = NULL; 

    public:
        CVideo();
        ~CVideo();

        void Inisialise();
        void Start();
        void Stop();
        void GetCurrentFrame();
        void SetWindow(int x, int y);
        void SetIsShow(bool f);

        void SetWh(HWND h);
        HWND GetWh();
        
        int GetWidth();
        int GetHight();

        bool GetIsRun();
        bool GetIsShow();
};