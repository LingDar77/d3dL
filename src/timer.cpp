#include "timer.h"
 float timer::mark()
    {
        const auto old = last;
        last = std::chrono::steady_clock::now();
        const std::chrono::duration<float> t = last - old;
        return t.count();
    }
    float timer::peek() const
    {
        return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
    }