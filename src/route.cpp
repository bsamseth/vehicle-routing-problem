#include "route.hpp"

#include <algorithm>
#include <numeric>

Route randomRoute(const ProblemInstance& instance)
{
    Route route;

    // Fill route with all customers in a random order.
    route.ids.resize(instance.customers.size());
    std::iota(route.ids.begin(), route.ids.end(), 0);
    std::random_shuffle(route.ids.begin(), route.ids.end());

    // Work out where to place sub route partitions.
    unsigned capacity = instance.truck.capacity;
    for (unsigned i = 0; i < route.ids.size(); ++i)
    {
        auto demand = instance.customers[route.ids[i]].demand;
        if (capacity < demand)
        {
            route.partitions.push_back(i);
            capacity = instance.truck.capacity;
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
