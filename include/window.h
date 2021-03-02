#ifndef EF9A49F1_7516_4A51_9BEB_1FC15E6AC66B
#define EF9A49F1_7516_4A51_9BEB_1FC15E6AC66B
#include "win.h"
#include <vector>
#include <bitset>
#include <string>
typedef std::bitset<254> keyType; //all keys provided only have 254 kinds, every set express its state
class window;
LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
void kbdHandler(keyType& key);
class keyBoard
{
public:
    keyBoard(void (*f)(keyType&)):function(f){}
    keyBoard():function(&kbdHandler){}
    ~keyBoard(){
    }
    void keyDown(unsigned code, HWND hWnd)
    {
        // if(code!=VK_OEM_1&&code!=VK_OEM_2&&code!=VK_OEM_PERIOD&&code!=VK_OEM_COMMA&&code!=VK_OEM_MINUS&&code!=VK_OEM_PLUS)
        // std::cout <<"In window "<< hWnd<< " key:"<<code<<" was pressed" << std::endl;
        keySet(code, 1);

    }
    void keyUp(unsigned code, HWND hWnd)
    {
        // if(code!=VK_OEM_1&&code!=VK_OEM_2&&code!=VK_OEM_PERIOD&&code!=VK_OEM_COMMA&&code!=VK_OEM_MINUS&&code!=VK_OEM_PLUS)
        // std::cout <<"In window "<< hWnd<< " key:"<<code<<" was released" << std::endl;
        keySet(code, 0);

    }
    void SysUp(unsigned code, HWND hWnd)
    {
        // std::cout <<"In window "<< hWnd<< " System key:"<<code<<" was released" << std::endl;
        keySet(code, 0);
    }
    void SysDown(unsigned code, HWND hWnd)
    {
        // std::cout <<"In window "<< hWnd<< " System key:"<<code<<" was pressed" << std::endl;
        //finally only alt is considered as a system key
        // std::cout<<code<<std::endl;
        keySet(code, 1);
    }
    bool isKeyDown(unsigned code)
    {
        return key[code] == 1;
    }
    bool isKeyUp(unsigned code)
    {
        return key[code] == 0;
    }
    void keySet(unsigned char code, bool value)
    {
        key.set(code, value);
        function(key);
    };

private:
    keyType key={0};
    void (*function)(keyType&);
};
class mouse
{
};
class winClass
{
    friend class window;
    HINSTANCE hInstance;

private:
    std::string className, ICON;

public:
    winClass(HINSTANCE h, char *name, char *icon) : hInstance(h), className(name), ICON(icon)
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
    };
    ~winClass() noexcept
    {
        UnregisterClass(_T(className.c_str()), hInstance);
    };
};

class window
{
    friend class winClass;
    friend LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

private:
    HINSTANCE hInstance;
    std::vector<HWND> h;
    keyBoard kbd;

public:
    HWND getHwnd(size_t t)
    {
        if (t >= h.size())
            throw std::out_of_range("out of range of getHwnd!");
        return h[t];
    }
    //search window instance, failed return size
    size_t searchHwnd(HWND hWnd)
    {
        size_t i;
        for (i = 0; i < h.size(); ++i)
            if (hWnd == h[i])
                return i;
        return i;
    }
    void createWindow(const winClass *wc, unsigned X, unsigned Y, unsigned wh, unsigned ht, char *name)
    {
        HWND hWnd = CreateWindowEx(0, _T(wc->className.c_str()), name,
                                   WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                                   X, Y, wh, ht, nullptr, nullptr, hInstance, this);
        h.push_back(hWnd);
        ShowWindow(hWnd, SW_SHOW);
    }
    window(HINSTANCE h) : hInstance(h){};
    ~window() noexcept
    {
        for (auto &i : h)
            DestroyWindow(i);
    }
};

#endif /* EF9A49F1_7516_4A51_9BEB_1FC15E6AC66B */
