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
#    include "doctest.h"

TEST_CASE("Read input file")
{
    ProblemInstance instance = readDataFile("../data/size50.txt");

    CHECK(instance.customers.size() == 50);

    CHECK(instance.customers[0].id == 1);
    CHECK(instance.customers[0].x == 37);
    CHECK(instance.customers[0].y == 52);
    CHECK(instance.customers[0].demand == 7);

    CHECK(instance.truck.capacity == 160);
    CHECK(instance.truck.depotX == 30);
    CHECK(instance.truck.depotY == 40);
}

#endif
