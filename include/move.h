#ifndef A068DCB1_0968_4B5B_9F6A_3DEF0F6CB1ED
#define A068DCB1_0968_4B5B_9F6A_3DEF0F6CB1ED
#include "keyMap.h"
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
    ~move() noexcept {}
    move() = default;
    void operator==(const move &) = delete;
    virtual void carry(keyType key)
    {
        static keyMap map;
        if (key == map.getKey("Forward"))
        {
            forward();
        }
        if (key == map.getKey("Left"))
        {
            left();
        }
        if (key == map.getKey("Back"))
        {
            back();
        }
        if (key == map.getKey("Right"))
        {
            right();
        }
    };
};

#endif /* A068DCB1_0968_4B5B_9F6A_3DEF0F6CB1ED */
