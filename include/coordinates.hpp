#pragma once

struct Coordinates
{
    int x;
    int y;
};

constexpr double operator||(const Coordinates& a, const Coordinates& b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "doctest.h"

TEST_CASE("Coordinates can compute distance")
{
    Coordinates a {1, 4};
    Coordinates b {-5, 2};

    CHECK((a || b) == 40);
    CHECK((b || a) == 40);
    CHECK((a || a) == 0);
    CHECK((b || b) == 0);
}

#endif
