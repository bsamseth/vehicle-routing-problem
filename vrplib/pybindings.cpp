#include "route.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_vrplib_backend, m)
{
    py::class_<Coordinates>(m, "Coordinates");
    /* .def(py::init<int, int>(), py::arg("h") = NUMMERIC_DIFF_STEP); */

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
