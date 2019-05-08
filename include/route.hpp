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

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "config.hpp"
#    include "doctest.h"

#    include <iostream>
#    include <random>

TEST_CASE("Constraint check")
{
    auto  instance = readDataFile(DATA_FOLDER "/size50.txt");
    Route route;
    // clang-format off
    route.ids = {
        14, 25, 13, 41, 40, 19, 42, 17,
        27, 48, 8, 26, 7, 43, 24, 23, 6,
        38, 9, 30, 34, 50, 21, 29, 16, 11, 32,
        2, 20, 35, 36, 3, 28, 31, 22, 1,
        5, 49, 10, 39, 33, 45, 15, 44, 37, 12,
        46, 47, 4, 18
    };
    // clang-format on
    route.partitions = {8, 17, 27, 36, 46};
    CHECK(satisfiesConstraints(route, instance) == true);

    // Failing example:
    // clang-format off
    route.ids = {
        14, 25, 13, 41, 40, 19, 42, 17,
        27, 48, 8, 26, 7, 43, 24, 23, 6, 38,
        9, 30, 34, 50, 21, 29, 16, 11, 32,
        2, 20, 35, 36, 3, 28, 31, 22, 1,
        5, 49, 10, 39, 33, 45, 15, 44, 37, 12,
        46, 47, 4, 18
    };
    // clang-format on
    route.partitions = {8, 18, 27, 36, 46};
    CHECK(satisfiesConstraints(route, instance) == false);
}

TEST_CASE("Random route")
{
    auto  instance = readDataFile(DATA_FOLDER "/size50.txt");
    Route route    = randomRoute(instance);

    // Route is random, so just check the obvious:
    CHECK(route.ids.size() == instance.customers.size());
    CHECK(route.partitions.size() > 0);  // Truck can't make just one run for this data.

    CHECK(satisfiesConstraints(route, instance) == true);
}

#endif
