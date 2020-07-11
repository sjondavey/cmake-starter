
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "../src/formula/Black76Formula.h"

using namespace pybind11::literals; // shorthand for py::args

namespace py = pybind11;

double call_value(double forward, double strike, double sd, double df)
{
    std::unique_ptr<sjd::Black76Option> call = std::make_unique<sjd::Black76Call>(forward, strike, sd, df);
    return call->value();
}

double put_value(double forward, double strike, double sd, double df)
{
    std::unique_ptr<sjd::Black76Option> put = std::make_unique<sjd::Black76Put>(forward, strike, sd, df);
    return put->value();
}

PYBIND11_MODULE(montecarlo, m)
{
  m.doc() = "pybind11 example plugin";
  m.def("call_value", 
        &call_value, 
        "Black76 Call Option Premium", 
        "forward"_a, 
        "strike"_a,
        "sd"_a,
        "df"_a);

  m.def("put_value", 
        &put_value, 
        "Black76 Put Option Premium", 
        py::arg("forward"), 
        py::arg("strike"),
        py::arg("sd"),
        py::arg("df"));

  auto pyBlack76Call = py::class_<sjd::Black76Call>(
			m,
			"Black76Call",
			R"pbdoc(Class for Black76 Call Options.)pbdoc");
	pyBlack76Call
		.def(py::init<double, double, double, double>(),
			"forward"_a, 
      "strike"_a,
      "sd"_a,
      "df"_a)             // Bind class constructor 
		.def("value",			&sjd::Black76Call::value)
		.def("delta",	    &sjd::Black76Call::delta)
    .def("payoff",    &sjd::Black76Call::payoff);        

  auto pyBlack76Put = py::class_<sjd::Black76Put>(
			m,
			"Black76Put",
			R"pbdoc(Class for Black76 Call Options.)pbdoc");
	pyBlack76Put
		.def(py::init<double, double, double, double>(),
			py::arg("forward"), 
      py::arg("strike"),
      py::arg("sd"),
      py::arg("df"))             // Bind class constructor 
		.def("value",			&sjd::Black76Put::value)
		.def("delta",	    &sjd::Black76Put::delta)
    .def("payoff",    &sjd::Black76Put::payoff);        
}