#pragma once

#include "coordinates.hpp"

struct Truck
{
    Coordinates depotCoordinates;
    unsigned    capacity;
    unsigned    id;
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "doctest.h"

#endif
