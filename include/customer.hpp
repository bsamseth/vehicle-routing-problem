#pragma once

using CustomerId = unsigned;

struct Customer
{
    int        x;
    int        y;
    unsigned   demand;
    CustomerId id;
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "doctest.h"

#endif
