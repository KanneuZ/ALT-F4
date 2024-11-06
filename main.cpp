#include <windows.h>
#include <stdio.h>
#include <dshow.h>
#include "CVideo.h"

LRESULT CALLBACK MainWinProc(HWND, UINT, WPARAM, LPARAM);
#define ID_MYBUTTON 1
#define ID_MYTEXT 2
CVideo cv;

void deb(const char *fmt, ...) {
    va_list argptr;
    char buf[4096];
    int s;
    FILE *fh;

    va_start(argptr, fmt);
    s=vsnprintf(buf, sizeof(buf), fmt, argptr);
    va_end(argptr);

    fh=fopen("objDet.log", "a");
    if (fh==NULL) return;
    fputs(buf, fh);
    fclose(fh);

    printf("%s", buf);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int ss) {
    WNDCLASS wc;
    wc.style=0;
    wc.lpfnWndProc=MainWinProc;
    wc.cbClsExtra=wc.cbWndExtra=0;
    wc.hInstance=hInst;
    wc.hIcon=NULL;
    wc.hCursor=NULL;
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName=NULL;
    wc.lpszClassName="Test 1 MainWnd Class";

    if (!RegisterClass(&wc)) return FALSE;

    HWND hMainWnd = CreateWindow("Test 1 MainWnd Class", "Test 1", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);

    if (!hMainWnd) return FALSE;

    ShowWindow(hMainWnd, ss);
    UpdateWindow(hMainWnd);

    MSG msg;
    
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 

    return msg.wParam; 
}

bool reg(char *str) {
    WNDCLASS wc;
    wc.style=0;
    wc.lpfnWndProc=MainWinProc;
    wc.cbClsExtra=wc.cbWndExtra=0;
    // wc.hInstance=hInst;
    wc.hIcon=NULL;
    wc.hCursor=NULL;
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName=NULL;
    wc.lpszClassName=str;

    if (!RegisterClass(&wc)) return false;
    return true;
}

LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) { 
    switch (msg) {
        case WM_CREATE:
            cv.Inisialise();
            if (reg("new wind")) cv.SetWh(CreateWindow("new wind", "JRYJ", WS_CHILD|WS_BORDER|WS_VISIBLE, 10, 10, cv.GetWidth(), cv.GetHight(), hw, NULL, NULL, NULL));
            // cv.SetIsShow(false);
            PostMessage(hw, WM_COMMAND, ID_MYBUTTON, 0);
            return 0;

        case WM_COMMAND:
            if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MYBUTTON)) cv.Start();
            return 0;

        case WM_DESTROY:
            cv.~CVideo();
            PostQuitMessage(0);
            return 0;
        
        case WM_KEYDOWN:
            switch (wp) {
                case VK_SPACE:
                    if (cv.GetIsRun()) cv.Stop();
                    else cv.Start();
                    
                    // MessageBox(hw, "", "attention", NULL);

                    // cv.GetCurrentFrame();
                    break;
            }
            return 0;
    }

    return DefWindowProc(hw, msg, wp, lp);
}