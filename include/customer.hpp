#pragma once

#include "coordinates.hpp"

using CustomerId = unsigned;

struct Customer
{
    Coordinates coordinates;
    unsigned    demand;
    CustomerId  id;
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "doctest.h"

#endif
