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
bool          satisfiesConstraints(const Route&, const ProblemInstance&);
double        totalLength(const Route&, const ProblemInstance&);

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "config.hpp"
#    include "doctest.h"

#    include <iostream>
#    include <random>

TEST_CASE("Random route")
{
    auto  instance = readDataFile(DATA_FOLDER "/size50.txt");
    Route route    = randomRoute(instance);

    // Route is random, so just check the obvious:
    CHECK(route.ids.size() == instance.customers.size());
    CHECK(route.partitions.size() > 0);  // Truck can't make just one run for this data.

    CHECK(satisfiesConstraints(route, instance) == true);
}

TEST_CASE("Constraint check")
{
    auto  instance = readDataFile(DATA_FOLDER "/size50.txt");
    Route route;
    // clang-format off
    route.ids = {
         13, 24, 12, 40, 39, 18, 41, 16,
         26, 47, 7, 25, 6, 42, 23, 22, 5,
         37, 8, 29, 33, 49, 20, 28, 15, 10, 31,
         1, 19, 34, 35, 2, 27, 30, 21, 0,
         4, 48, 9, 38, 32, 44, 14, 43, 36, 11,
         45, 46, 3, 17
    };
    // clang-format on
    route.partitions = {8, 17, 27, 36, 46};
    CHECK(satisfiesConstraints(route, instance) == true);

    // Length calculated by hand for this case:
    CHECK(totalLength(route, instance) == 6180);

    // Failing example: Second tour is to large.
    route.partitions = {8, 25, 27, 36, 46};
    CHECK(satisfiesConstraints(route, instance) == false);
}

#endif
