#include "route.hpp"

#include <algorithm>
#include <numeric>

Route randomRoute(const ProblemInstance& instance)
{
    Route route;

    // Fill route with all customers in a random order.
    route.ids.resize(instance.customers.size());
    std::iota(route.ids.begin(), route.ids.end(), 1);
    std::random_shuffle(route.ids.begin(), route.ids.end());

    // Work out where to place sub route partitions.
    int capacity = instance.truck.capacity;
    for (unsigned i = 0; i < route.ids.size(); ++i)
    {
        int demand = instance.customers[route.ids[i]].demand;
        if (capacity < demand)
        {
            route.partitions.push_back(i);
            capacity = instance.truck.capacity - demand;
        }
        else
            capacity -= demand;
    }

    return route;
}

std::ostream& operator<<(std::ostream& stm, const Route& route)
{
    std::cout << "[\n\t[ ";
    auto part = route.partitions.begin();
    for (unsigned i = 0; i < route.ids.size(); ++i)
    {
        if (part != route.partitions.end() && *part == i)
        {
            ++part;
            stm << "]\n\t[ ";
        }
        stm << route.ids[i] << " ";
    }
    return stm << "]\n]";
}

bool satisfiesConstraints(const Route& route, const ProblemInstance& instance)
{
    int  capacity       = instance.truck.capacity;
    auto next_partition = route.partitions.begin();
    for (unsigned i = 0; i < route.ids.size(); ++i)
    {
        if (next_partition != route.partitions.end() && i == *next_partition)
        {
            capacity = instance.truck.capacity;
            ++next_partition;
        }

        capacity -= instance.customers[route.ids[i]].demand;

        if (capacity < 0)
            return false;
    }

    return true;
}

double totalLength(const Route& route, const ProblemInstance& instance)
{
    double length         = 0;
    auto   next_partition = route.partitions.begin();
    auto   depot          = instance.truck.depotCoordinates;
    auto   last_pos       = depot;
    for (unsigned i = 0; i < route.ids.size(); ++i)
    {
        auto pos = instance.customers[route.ids[i]].coordinates;
        if (next_partition != route.partitions.end() && i == *next_partition)
        {
            length += last_pos || depot;
            last_pos = depot;
            ++next_partition;
        }

        length += last_pos || pos;
        last_pos = pos;
    }
    return length + (last_pos || depot);
}
