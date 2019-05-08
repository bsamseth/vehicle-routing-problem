#pragma once

struct Truck
{
    int      depotX;
    int      depotY;
    unsigned capacity;
    unsigned id;
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "doctest.h"

#endif
