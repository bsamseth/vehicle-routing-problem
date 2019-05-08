#include "nearestneighbors.hpp"

#include <limits>

namespace Optimize
{
Route nearestNeighbors(const ProblemInstance& instance)
{
    Route route;
    auto  curr_pos      = instance.truck.depotCoordinates;
    auto  curr_capacity = instance.truck.capacity;

    std::vector<CustomerId> remaining(instance.customers.size());
    std::iota(remaining.begin(), remaining.end(), 0);

    while (remaining.size() > 0)
    {
        auto   nearest_id   = remaining.end();
        double nearest_dist = std::numeric_limits<double>::max();
        for (auto it = remaining.begin(); it != remaining.end(); ++it)
        {
            auto dist = instance.customers[*it].coordinates || curr_pos;

            if (dist < nearest_dist && curr_capacity >= instance.customers[*it].demand)
            {
                nearest_dist = dist;
                nearest_id   = it;
            }
        }

        if (nearest_id != remaining.end())
        {
            route.ids.push_back(*nearest_id);
            curr_capacity -= instance.customers[*nearest_id].demand;
            curr_pos = instance.customers[*nearest_id].coordinates;
            remaining.erase(nearest_id);
        }
        else
        {
            // No next customer could be added, meaning we don't have enough capacity.
            route.partitions.push_back(route.ids.size());
            curr_pos      = instance.truck.depotCoordinates;
            curr_capacity = instance.truck.capacity;
        }
    }

    return route;
}

}  // namespace Optimize
