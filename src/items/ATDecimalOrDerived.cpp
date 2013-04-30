/*
 * ATDecimalOrDerived.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "ATDecimalOrDerived.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/mapm/m_apm.h>

#include <xqilla/items/ATDecimalOrDerived.hpp>

namespace pyxqilla {

void ATDecimalOrDerived_init(void) {
	//! ATDecimalOrDerived
	boost::python::class_<ATDecimalOrDerived, boost::noncopyable, boost::python::bases<Numeric> >("ATDecimalOrDerived", boost::python::no_init)
			.def("getPrimitiveTypeName", &ATDecimalOrDerived::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeURI", &ATDecimalOrDerived::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", &ATDecimalOrDerived::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("asString", &ATDecimalOrDerived::asString, boost::python::return_value_policy<boost::python::return_by_value>())
			// TODO: Numeric::Ptr
			.def("promoteTypeIfApplicable", &ATDecimalOrDerived::promoteTypeIfApplicable)
			// TODO: Numeric::Ptr
			.def("add", &ATDecimalOrDerived::add)
			// TODO: Numeric::Ptr
			.def("subtract", &ATDecimalOrDerived::subtract)
			// TODO: Numeric::Ptr
			.def("multiply", &ATDecimalOrDerived::multiply)
			// TODO: Numeric::Ptr
			.def("divide", &ATDecimalOrDerived::divide)
			// TODO: Numeric::Ptr
			.def("mod", &ATDecimalOrDerived::mod)
			// TODO: Numeric::Ptr
			.def("floor", &ATDecimalOrDerived::floor)
			// TODO: Numeric::Ptr
			.def("ceiling", &ATDecimalOrDerived::ceiling)
			// TODO: Numeric::Ptr
			.def("round", &ATDecimalOrDerived::round)
			// TODO: Numeric::Ptr
			.def("roundHalfToEven", &ATDecimalOrDerived::roundHalfToEven)
			// TODO: Numeric::Ptr
			.def("invert", &ATDecimalOrDerived::invert)
			// TODO: Numeric::Ptr
			.def("abs", &ATDecimalOrDerived::abs)
			// TODO: Numeric::Ptr
			.def("sqrt", &ATDecimalOrDerived::sqrt)
			// TODO: Numeric::Ptr
			.def("sin", &ATDecimalOrDerived::sin)
			// TODO: Numeric::Ptr
			.def("con", &ATDecimalOrDerived::cos)
			// TODO: Numeric::Ptr
			.def("tan", &ATDecimalOrDerived::tan)
			// TODO: Numeric::Ptr
			.def("asin", &ATDecimalOrDerived::asin)
			// TODO: Numeric::Ptr
			.def("acos", &ATDecimalOrDerived::acos)
			// TODO: Numeric::Ptr
			.def("atan", &ATDecimalOrDerived::atan)
			// TODO: Numeric::Ptr
			.def("log", &ATDecimalOrDerived::log)
			// TODO: Numeric::Ptr
			.def("exp", &ATDecimalOrDerived::exp)
			.def("isZero", &ATDecimalOrDerived::isZero)
			.def("isNegative", &ATDecimalOrDerived::isNegative)
			.def("isPositive", &ATDecimalOrDerived::isPositive)
			.def("isNaN", &ATDecimalOrDerived::isNaN)
			.def("isInfinite", &ATDecimalOrDerived::isInfinite)
			.def("treatAsCodepoint", &ATDecimalOrDerived::treatAsCodepoint)
			.def("getPrimitiveTypeIndex", &ATDecimalOrDerived::getPrimitiveTypeIndex)
			.def("asMAPM", &ATDecimalOrDerived::asMAPM, boost::python::return_internal_reference<>())
			.def("getState", &ATDecimalOrDerived::getState)
			;
}

} /* namespace pyxqilla */
