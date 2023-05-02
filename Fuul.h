#pragma once
#include "Meteors.h"
class Fuul :
    public Meteors
{
public:
    Fuul(String name, int x, int y);
    ~Fuul();

    virtual void restart();

private:
    using Meteors::animation;
};

