#pragma once

#include "customer.hpp"
#include "truck.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

struct ProblemInstance
{
    std::vector<Customer> customers;
    Truck                 truck;
};

ProblemInstance readDataFile(std::string filename);

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "config.hpp"
#    include "doctest.h"

TEST_CASE("Read input file")
{
    auto instance = readDataFile(DATA_FOLDER "/size50.txt");

    CHECK(instance.customers.size() == 50);

    CHECK(instance.customers[0].id == 1);
    CHECK(instance.customers[0].coordinates.x == 37);
    CHECK(instance.customers[0].coordinates.y == 52);
    CHECK(instance.customers[0].demand == 7);

    CHECK(instance.truck.capacity == 160);
    CHECK(instance.truck.depotCoordinates.x == 30);
    CHECK(instance.truck.depotCoordinates.y == 40);
}

#endif
