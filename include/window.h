#ifndef EF9A49F1_7516_4A51_9BEB_1FC15E6AC66B
#define EF9A49F1_7516_4A51_9BEB_1FC15E6AC66B
#include "win.h"
#include <vector>
#include <bitset>
#include <string>
#include "timer.h"
#include <optional>
#include "keyMap.h"
class window;
LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
void kbdHandler(keyType &key);
class interact
{
public:
    interact(void (*f)(keyType &)) : function(f) {}
    interact() : function(&kbdHandler) {}
    ~interact()
    {
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
    void mouseLClick(HWND hWnd, WPARAM wParam, LPARAM lParam)
    {
    }
    void mouseRClick(HWND hWnd, WPARAM wParam, LPARAM lParam)
    {
    }
    void mouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
    {
        POINTS pts = MAKEPOINTS(lParam);
        // std::cout << pts.x << " " << pts.y << std::endl;
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
    keyType key = {0};
    void (*function)(keyType &);
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
    winClass(HINSTANCE h, char *name, char *icon);
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
    std::vector<timer *> ts;
    interact kbd;

public:
    void doFrame();
    std::optional<int> processer();
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
    void createWindow(const winClass *wc, unsigned X, unsigned Y, unsigned wh, unsigned ht, char *name);
    window(HINSTANCE h) : hInstance(h){};
    ~window() noexcept
    {
        for (auto &i : ts)
            delete i; //destroy timers
        for (auto &i : h)
            DestroyWindow(i); //destroy windows
    }
};

#endif /* EF9A49F1_7516_4A51_9BEB_1FC15E6AC66B */
