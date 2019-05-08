#include "generator.hpp"

namespace
{
void incr(const Route& route, unsigned& i, unsigned& j)
{
    ++j;
    if (j >= route.ids.size())
    {
        ++i;
        j = i + 1;
        if (j >= route.ids.size())
            i = j = 0;
    }
}
}  // namespace

bool SwapGenerator::next()
{
next_start:
    // Undo last swap first.
    std::swap(route_.ids[i], route_.ids[j]);

    incr(route_, i, j);
    if (i == 0 && j == 0)
        return false;

    std::swap(route_.ids[i], route_.ids[j]);
    if (!satisfiesConstraints(route_, instance_))
        goto next_start;

    return true;
}
