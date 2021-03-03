#ifndef CADE523D_E26E_4A14_8F95_A1991A806AAF
#define CADE523D_E26E_4A14_8F95_A1991A806AAF
#include "win.h"
#include <chrono>
#include <sstream>
class window;
class timer
{
    friend class window;

private:
    std::chrono::steady_clock::time_point last;
    HWND hWnd;

public:
    ~timer() noexcept
    {
        std::cout << "timer：" << this << " destroyed" << std::endl;
    }
    timer(HWND h) : last(last = std::chrono::steady_clock::now()), hWnd(h)
    {
    }
    void operator==(const timer &) = delete;
    float mark();
    float peek() const;
};
#endif /* CADE523D_E26E_4A14_8F95_A1991A806AAF */
