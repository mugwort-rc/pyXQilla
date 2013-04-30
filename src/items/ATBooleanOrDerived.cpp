/*
 * ATBooleanOrDerived.cpp
 *
 *  Created on: 2013/02/27
 *      Author: mugwort_rc
 */

#include "ATBooleanOrDerived.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>

#include <xqilla/items/ATBooleanOrDerived.hpp>

namespace pyxqilla {

void ATBooleanOrDerived_init(void) {
	//! BoolResult
	boost::python::class_<BoolResult>("BoolResult", boost::python::init<bool>())
			.def("__eq__", &BoolResult::operator ==)
			.def("__ne__", &BoolResult::operator !=)
			.setattr("True", BoolResult::True)
			.setattr("False", BoolResult::False)
			.setattr("Null", BoolResult::Null)
			;
	//! ATBooleanOrDerived
	boost::python::class_<ATBooleanOrDerived, boost::noncopyable, boost::python::bases<AnyAtomicType> >("ATBooleanOrDerived", boost::python::no_init)
			.def("getPrimitiveTypeName", &ATBooleanOrDerived::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeURI", &ATBooleanOrDerived::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", &ATBooleanOrDerived::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("asString", &ATBooleanOrDerived::asString, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("equals", &ATBooleanOrDerived::equals)
			.def("compare", &ATBooleanOrDerived::compare)
			.def("isTrue", &ATBooleanOrDerived::isTrue)
			.def("isFalse", &ATBooleanOrDerived::isFalse)
			.def("getPrimitiveTypeIndex", &ATBooleanOrDerived::getPrimitiveTypeIndex)
			;
}

} /* namespace pyxqilla */
