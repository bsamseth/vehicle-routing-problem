// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#    define DOCTEST_CONFIG_IMPLEMENT
#    include "doctest.h"
#endif

#include "config.hpp"
#include "nearestneighbors.hpp"
#include "route.hpp"

#include <iostream>

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main()
{
    auto  instance = readDataFile(DATA_FOLDER "/size50.txt");
    Route route    = Optimize::nearestNeighbors(instance);
    exportPlotData(std::cout, route, instance);
    std::cout << std::endl;
}
