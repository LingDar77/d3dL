

#include "window.h"
#include <tchar.h>
#include <set>
#include <iostream>
#include "resource.h"


LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    auto p = reinterpret_cast<window *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    switch (msg)
    {
    case WM_CLOSE:
    {
        // p->createWindow(100,100,480,320,"you were tricked!");
        p->destroyWindow(hWnd);
        return 0;
    }
    case WM_SYSKEYDOWN:
    {
        p->kbd.SysDown(static_cast<unsigned char>(wParam), hWnd);
        break;
    }
    case WM_SYSKEYUP:
    {
        p->kbd.SysUp(static_cast<unsigned char>(wParam), hWnd);
        break;
    }
    case WM_KEYDOWN:
    {
        p->kbd.keyDown(static_cast<unsigned char>(wParam), hWnd);
        break;
    }
    case WM_KEYUP:
    {
        p->kbd.keyUp(static_cast<unsigned char>(wParam), hWnd);
        break;
    }
    case WM_MOUSEMOVE:
    {
        p->kbd.mouseMove(hWnd, wParam, lParam);
        break;
    }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW *const pcreate = reinterpret_cast<CREATESTRUCTW *>(lParam);
        window *const pWnd = reinterpret_cast<window *>(pcreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&HandleMsgThunk));
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
void kbdHandler(keyType &key)
{
    static keyType preKey;
    static move m;
    m.carry(key);
    preKey = key;
}
std::optional<int> window::processer()
{

    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return msg.wParam;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return {};
}
winClass::winClass(HINSTANCE h, char *name, char *icon) : hInstance(h), className(name), ICON(icon)
{
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(wc);
    wc.hInstance = hInstance;
    wc.lpszClassName = className.c_str();
    wc.style = CS_OWNDC;
    wc.hIconSm = static_cast<HICON>(LoadImage(h,MAKEINTRESOURCE( IDI_ICON1 ),IMAGE_ICON,16,16,0));
    wc.hIcon = static_cast<HICON>(LoadImage(h,MAKEINTRESOURCE( IDI_ICON1 ),IMAGE_ICON,32,32,0));
    wc.lpfnWndProc = HandleMsgSetup;
    RegisterClassEx(&wc);
}
void window::doFrame()
{
    
    for (unsigned cnt=0;cnt<gr.size();++cnt)
    {
        std::stringstream ss;
        ss << ts[cnt]->peek();
        gr[cnt]->endFrame();
        const float c=sin(ts[cnt]->peek()); 
        gr[cnt]->clearBuffer(c,c*c,c/2);
        // SetWindowText(i->hWnd,_T(ss.str().c_str()));
        
    }
}
void window::createWindow(const winClass *wc, unsigned X, unsigned Y, unsigned wh, unsigned ht, char *name)
{
    HWND hWnd = CreateWindowEx(0, _T(wc->className.c_str()), name,
                               WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                               X, Y, wh, ht, nullptr, nullptr, hInstance, this);
    h.push_back(hWnd);
    ts.push_back(new timer{hWnd});
    gr.push_back(new graphics{hWnd});
    ShowWindow(hWnd, SW_SHOW);
}
void window::destroyWindow(HWND hWnd)
{
    auto cnt = searchHwnd(hWnd);
    if (cnt != h.size())
    {
        delete gr[cnt];
        gr.erase(gr.begin() + cnt);
        DestroyWindow(hWnd);
        h.erase(h.begin() + cnt);
        delete ts[cnt];
        ts.erase(ts.begin() + cnt);
    }
    if (h.empty())
    {
        PostQuitMessage(0);
    }
}