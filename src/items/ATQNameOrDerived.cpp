/*
 * ATQNameOrDerived.cpp
 *
 *  Created on: 2013/02/27
 *      Author: mugwort_rc
 */

#include "ATQNameOrDerived.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>

#include <xqilla/items/ATQNameOrDerived.hpp>

namespace pyxqilla {

void ATQNameOrDerived_init(void) {
	//! ATQNameOrDerived
	boost::python::class_<ATQNameOrDerived, boost::noncopyable, boost::python::bases<AnyAtomicType> >("ATQNameOrDerived", boost::python::no_init)
			.def("getPrimitiveTypeName", &ATQNameOrDerived::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeURI", &ATQNameOrDerived::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", &ATQNameOrDerived::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getURI", &ATQNameOrDerived::getURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getPrefix", &ATQNameOrDerived::getPrefix, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getName", &ATQNameOrDerived::getName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("asString", &ATQNameOrDerived::asString, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("equals", &ATQNameOrDerived::equals)
			.def("compare", &ATQNameOrDerived::compare)
			.def("getPrimitiveTypeIndex", &ATQNameOrDerived::getPrimitiveTypeIndex)
			;
}

} /* namespace pyxqilla */
