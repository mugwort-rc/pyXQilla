/*
 * Numeric.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "Numeric.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/StaticContext.hpp>
#include <xqilla/mapm/m_apm.h>

#include <xqilla/items/Numeric.hpp>

#include "util/XMLString.h"

namespace pyxqilla {

void Numeric_init(void) {
	//! Numeric
	auto PyNumeric = boost::python::class_<Numeric, boost::noncopyable, boost::python::bases<AnyAtomicType> >("Numeric", boost::python::no_init)
			.def("isNumericValue", &Numeric::isNumericValue)
			.def("getPrimitiveTypeName", &Numeric::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeURI", &Numeric::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", &Numeric::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("asString", &Numeric::asString, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("promoteTypeIfApplicable", &Numeric::promoteTypeIfApplicable)
			.def("equals", &Numeric::equals)
			.def("lessThan", &Numeric::lessThan)
			.def("greaterThan", &Numeric::greaterThan)
			.def("compare", &Numeric::compare)
			.def("add", &Numeric::add)
			.def("subtract", &Numeric::subtract)
			.def("multiply", &Numeric::multiply)
			.def("divide", &Numeric::divide)
			.def("mod", &Numeric::mod)
			.def("floor", &Numeric::floor)
			.def("ceiling", &Numeric::ceiling)
			.def("round", &Numeric::round)
			.def("roundHalfToEven", &Numeric::roundHalfToEven)
			.def("invert", &Numeric::invert)
			.def("abs", &Numeric::abs)
			.def("sqrt", &Numeric::sqrt)
			.def("sin", &Numeric::sin)
			.def("cos", &Numeric::cos)
			.def("tan", &Numeric::tan)
			.def("asin", &Numeric::asin)
			.def("acos", &Numeric::acos)
			.def("atan", &Numeric::atan)
			.def("log", &Numeric::log)
			.def("exp", &Numeric::exp)
			.def("power", &Numeric::power)
			.def("isZero", &Numeric::isZero)
			.def("isPositive", &Numeric::isPositive)
			.def("isNegative", &Numeric::isNegative)
			.def("isNaN", &Numeric::isNaN)
			.def("isInfinite", &Numeric::isInfinite)
			.def("isInteger", &Numeric::isInteger)
			.def("getPrimitiveTypeIndex", &Numeric::getPrimitiveTypeIndex)
			.def("asMAPM", &Numeric::asMAPM, boost::python::return_internal_reference<>())
			.def("asDouble", &Numeric::asDouble)
			.def("asInt", &Numeric::asInt)
			.def("getState", &Numeric::getState)
			.def("checkFloatLimits", &Numeric::checkFloatLimits)
			.def("checkDoubleLimits", &Numeric::checkDoubleLimits)
			.def("asDecimalString", static_cast<const XMLCh*(*)(const MAPM &, int, const StaticContext*)>(&Numeric::asDecimalString), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("asDoubleString", static_cast<const XMLCh*(*)(Numeric::State, const MAPM &, int, const StaticContext*)>(&Numeric::asDoubleString), boost::python::return_value_policy<boost::python::return_by_value>())
			.staticmethod("checkFloatLimits")
			.staticmethod("checkDoubleLimits")
			.staticmethod("asDecimalString")
			.staticmethod("asDoubleString")
			.setattr("NaN_string", pyxerces::XMLChPtr(Numeric::NaN_string))
			.setattr("NAN_string", pyxerces::XMLChPtr(Numeric::NAN_string))
			.setattr("INF_string", pyxerces::XMLChPtr(Numeric::INF_string))
			.setattr("NegINF_string", pyxerces::XMLChPtr(Numeric::NegINF_string))
			.setattr("NegZero_string", pyxerces::XMLChPtr(Numeric::NegZero_string))
			.setattr("PosZero_string", pyxerces::XMLChPtr(Numeric::PosZero_string))
			;
	boost::python::scope NumericScope = PyNumeric;
	//! Numeric::State
	boost::python::enum_<Numeric::State>("State")
			.value("NEG_INF", Numeric::NEG_INF)
			.value("NEG_NUM", Numeric::NEG_NUM)
			.value("NUM", Numeric::NUM)
			.value("INF", Numeric::INF)
			.value("NaN", Numeric::NaN)
			.export_values()
			;
}

} /* namespace pyxqilla */
