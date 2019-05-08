#pragma once

#include "route.hpp"

namespace Optimize
{
Route nearestNeighbors(const ProblemInstance&);

}

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "config.hpp"
#    include "doctest.h"
TEST_CASE("Nearest neighbors")
{
    auto  instance = readDataFile(DATA_FOLDER "/size50.txt");
    Route route    = Optimize::nearestNeighbors(instance);
    CHECK(satisfiesConstraints(route, instance) == true);

    // Length recorded, keeping test to detect regressions.
    CHECK(totalLength(route, instance) == 16312);
}
#endif
