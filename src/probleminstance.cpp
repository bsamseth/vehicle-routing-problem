#include "probleminstance.hpp"

ProblemInstance readDataFile(std::string filename)
{
    std::ifstream data(filename);

    if (!data.is_open())
        throw std::invalid_argument("File could not be opened.");

    data >> std::skipws;

    ProblemInstance instance;
    int             nodes;

    data >> nodes >> instance.truck.capacity >> instance.truck.depotX
        >> instance.truck.depotY;

    for (int i = 0; i < nodes; ++i)
    {
        Customer c;
        data >> c.id >> c.x >> c.y >> c.demand;
        instance.customers.push_back(c);
    }

    data.close();
    return instance;
}
