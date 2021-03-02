#ifndef CADE523D_E26E_4A14_8F95_A1991A806AAF
#define CADE523D_E26E_4A14_8F95_A1991A806AAF
#include "win.h"
#include <chrono>
#include <sstream>
class window;
class timer
{
    friend class window;
    std::chrono::steady_clock::time_point last;
    HWND hWnd;

public:
    ~timer()
    {
        std::cout<<hWnd<<"destroyed"<<std::endl;
    }
    timer(HWND h) : last(last = std::chrono::steady_clock::now()), hWnd(h)
    {
    }
    float mark()
    {
        const auto old = last;
        last = std::chrono::steady_clock::now();
        const std::chrono::duration<float> t = last - old;
        return t.count();
    }
    float peek() const
    {
        return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
    }
};
#endif /* CADE523D_E26E_4A14_8F95_A1991A806AAF */
