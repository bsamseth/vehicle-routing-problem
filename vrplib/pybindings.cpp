#include "route.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>

namespace py = pybind11;

PYBIND11_MODULE(_vrplib_backend, m)
{
    py::class_<ProblemInstance>(m, "ProblemInstance");
    py::class_<Route>(m, "Route")
        .def(py::init<std::vector<CustomerId>, std::vector<unsigned>>(),
             py::arg("ids"),
             py::arg("partitions"))
        .def_readwrite("ids", &Route::ids)
        .def_readwrite("partitions", &Route::partitions)
        .def("__str__",
             [](const Route& r) {
                 std::stringstream ss;
                 ss << r;
                 return ss.str();
             })
        .def("asPlotData", [](const Route& r, const ProblemInstance& i) {

        });

    m.def("randomRoute", &randomRoute);
    m.def("readDataFile", &readDataFile);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
