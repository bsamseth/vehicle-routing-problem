#pragma once

#include "route.hpp"

class Generator
{
protected:
    Route&                 route_;
    const ProblemInstance& instance_;

public:
    Generator(Route& r, const ProblemInstance& p) : route_(r), instance_(p) {}

    virtual bool next() = 0;
};

class SwapGenerator : public Generator
{
private:
    unsigned i = 0;
    unsigned j = 0;

public:
    using Generator::Generator;

    bool next() override;
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    include "config.hpp"
#    include "doctest.h"

TEST_CASE("Swap correct number of times")
{
    ProblemInstance instance;
    instance.customers.push_back({{0, 0}, 1, 1});  // coord, demand, id
    instance.customers.push_back({{0, 0}, 2, 2});
    instance.customers.push_back({{0, 0}, 3, 3});
    instance.truck = {{0, 0}, 4, 1};

    Route         route = randomRoute(instance);
    SwapGenerator gen(route, instance);

    int count = 1;
    for (; gen.next(); ++count)
        ;

    // There are 3 valid routes reachable by a single swap.
    CHECK(count == 3);
}

#endif
