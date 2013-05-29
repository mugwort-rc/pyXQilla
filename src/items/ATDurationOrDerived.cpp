/*
 * ATDurationOrDerived.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "ATDurationOrDerived.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>

#include <xqilla/items/ATDurationOrDerived.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

void ATDurationOrDerived_init(void) {
	//! ATDurationOrDerived
	boost::python::class_<ATDurationOrDerived, boost::noncopyable, boost::python::bases<AnyAtomicType> >("ATDurationOrDerived", boost::python::no_init)
			.def("getPrimitiveTypeName", &ATDurationOrDerived::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeURI", &ATDurationOrDerived::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", &ATDurationOrDerived::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("asString", &ATDurationOrDerived::asString, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("isDayTimeDuration", &ATDurationOrDerived::isDayTimeDuration)
			.def("isYearMonthDuration", &ATDurationOrDerived::isYearMonthDuration)
			.def("equals", &ATDurationOrDerived::equals)
			.def("compare", &ATDurationOrDerived::compare)
			// TODO: ATDurationOrDerived::Ptr
			.def("divide", static_cast<ATDurationOrDerived::Ptr(ATDurationOrDerived::*)(const Numeric::Ptr&, const DynamicContext*) const>(&ATDurationOrDerived::divide))
			// TODO: ATDecimalOrDerived::Ptr
			.def("divide", static_cast<ATDecimalOrDerived::Ptr(ATDurationOrDerived::*)(const ATDurationOrDerived::Ptr&, const DynamicContext*) const>(&ATDurationOrDerived::divide))
			// TODO: ATDurationOrDerived::Ptr
			.def("multiply", &ATDurationOrDerived::multiply)
			// TODO: ATDurationOrDerived::Ptr
			.def("add", &ATDurationOrDerived::add)
			// TODO: ATDurationOrDerived::Ptr
			.def("subtract", &ATDurationOrDerived::subtract)
			// TODO: ATDecimalOrDerived::Ptr
			.def("getYears", &ATDurationOrDerived::getYears)
			// TODO: ATDecimalOrDerived::Ptr
			.def("getMonths", &ATDurationOrDerived::getMonths)
			// TODO: ATDecimalOrDerived::Ptr
			.def("getDays", &ATDurationOrDerived::getDays)
			// TODO: ATDecimalOrDerived::Ptr
			.def("getHours", &ATDurationOrDerived::getHours)
			// TODO: ATDecimalOrDerived::Ptr
			.def("getMinutes", &ATDurationOrDerived::getMinutes)
			// TODO: ATDecimalOrDerived::Ptr
			.def("getSeconds", &ATDurationOrDerived::getSeconds)
			// TODO: ATDecimalOrDerived::Ptr
			.def("asSeconds", &ATDurationOrDerived::asSeconds)
			// TODO: ATDecimalOrDerived::Ptr
			.def("asMonths", &ATDurationOrDerived::asMonths)
			.def("isNegative", &ATDurationOrDerived::isNegative)
			.def("getPrimitiveTypeIndex", &ATDurationOrDerived::getPrimitiveTypeIndex)
			.setattr("fgDT_DAYTIMEDURATION", pyxerces::XMLChPtr(ATDurationOrDerived::fgDT_DAYTIMEDURATION))
			.setattr("pattern_DT_DAYTIMEDURATION", pyxerces::XMLChPtr(ATDurationOrDerived::pattern_DT_DAYTIMEDURATION))
			.setattr("fgDT_YEARMONTHDURATION", pyxerces::XMLChPtr(ATDurationOrDerived::fgDT_YEARMONTHDURATION))
			.setattr("pattern_DT_YEARMONTHDURATION", pyxerces::XMLChPtr(ATDurationOrDerived::pattern_DT_YEARMONTHDURATION))
			;
}

} /* namespace pyxqilla */
