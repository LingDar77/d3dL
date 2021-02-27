

#include "window.h"
#include <tchar.h>
#include <iostream>
LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    auto p = reinterpret_cast<window *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    switch (msg)
    {
    case WM_CLOSE:
    {

        DestroyWindow(hWnd);
        // p->createWindow(100,100,480,320,"you were tricked!");
        auto cnt = p->searchHwnd(hWnd);
        if (cnt != p->h.size())
            p->h.erase(p->h.begin() + cnt);
        if (p->h.empty())
        {
            PostQuitMessage(0);
        }
        return 0;
    }
    case WM_KEYDOWN:
    {
        p->kbd.keyDown(static_cast<unsigned char>(wParam),hWnd);
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