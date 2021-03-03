

#include "window.h"
#include <tchar.h>
#include <set>
#include <iostream>

LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    auto p = reinterpret_cast<window *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    switch (msg)
    {
    case WM_CLOSE:
    {

        // p->createWindow(100,100,480,320,"you were tricked!");
        auto cnt = p->searchHwnd(hWnd);
        if (cnt != p->h.size())
        {
            DestroyWindow(hWnd);
            p->h.erase(p->h.begin() + cnt);
            delete p->ts[cnt];
            p->ts.erase(p->ts.begin() + cnt);
        }
        if (p->h.empty())
        {
            PostQuitMessage(0);
        }
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
class move
{
private:
    void forward()
    {
        std::cout << "you are moving forward" << std::endl;
    }
    void back()
    {
        std::cout << "you are moving back" << std::endl;
    }
    void left()
    {
        std::cout << "you are moving left" << std::endl;
    }
    void right()
    {
        std::cout << "you are moving right" << std::endl;
    }

public:
    virtual void carry(keyType key)
    {
        static keyMap map;
        if (key == map.getKey("W"))
        {
            forward();
        }
        if (key == map.getKey("A"))
        {
            left();
        }
        if (key == map.getKey("S"))
        {
            back();
        }
        if (key == map.getKey("D"))
        {
            right();
        }
    };
};
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
    HICON hIconSm = (HICON)::LoadImage(
        hInstance,
        TEXT(ICON.c_str()),
        IMAGE_ICON,
        16, 16,
        LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    HICON hIcon = (HICON)::LoadImage(
        hInstance,
        TEXT(ICON.c_str()),
        IMAGE_ICON,
        32, 32,
        LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    wc.hIconSm = hIconSm;
    wc.hIcon = hIcon;
    wc.lpfnWndProc = HandleMsgSetup;
    RegisterClassEx(&wc);
}
void window::doFrame()
{
    for (auto &i : ts)
    {
        std::stringstream ss;
        ss << i->peek();
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
    ShowWindow(hWnd, SW_SHOW);
}