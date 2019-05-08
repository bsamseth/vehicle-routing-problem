#pragma once

#include "customer.hpp"
#include "probleminstance.hpp"

#include <vector>

struct Route
{
    std::vector<CustomerId> ids;
    std::vector<unsigned>   partitions;
};

std::ostream& operator<<(std::ostream&, const Route&);
Route         randomRoute(const ProblemInstance&);

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "doctest.h"

#    include <iostream>
#    include <random>

TEST_CASE("Random route")
{
    auto  instance = readDataFile("../data/size50.txt");
    Route route    = randomRoute(instance);

    // Route is random, so just check the obvious:
    CHECK(route.ids.size() == instance.customers.size());
    CHECK(route.partitions.size() > 0);  // Truck can't make just one run for this data.
}

#endif
