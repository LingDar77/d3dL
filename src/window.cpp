

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
public:
    virtual void carry(){};
};
class mForward : move
{
    keyType key{"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000001100000000000000000"};
       
        public : mForward(keyType &k) : key(k)
    {
    }
    mForward(){};
    void carry(keyType Key)
    {
        if ((Key & key) == Key) //if key&tk == tk shows that the target keys are pressed
        {
            std::cout << "carrying move forward" << std::endl;
        }
    }
};
void kbdHandler(keyType &key)
{
    static keyType preKey;
    static mForward m;
    if (key[VK_MENU])
        std::cout << "Alt was pressed" << std::endl;
    if (preKey[VK_MENU] && key[VK_MENU])
        std::cout << "Alt was pressing" << std::endl;
    if (!key[VK_MENU] && preKey[VK_MENU])
        std::cout << "Alt was released" << std::endl;

    if (key[VK_CONTROL] && key['A'] && key[VK_MENU])
        std::cout << "Ctrl+Alt+A was pressed" << std::endl;
    if (!key[VK_CONTROL] && !key['A'] && !key[VK_MENU])
    {
        m.carry(key);
        std::cout << "Ctrl+Alt+A was released" << std::endl;
    }
    preKey = key;
}
