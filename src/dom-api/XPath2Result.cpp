/*
 * XPath2Result.cpp
 *
 *  Created on: 2013/06/16
 *      Author: mugwort_rc
 */

#include "XPath2Result.h"

#include <boost/python.hpp>

#include <xqilla/dom-api/XPath2Result.hpp>

namespace pyxqilla {

void XPath2Result_init(void) {
	//! XPath2Result
	auto PyXPath2Result = boost::python::class_<XPath2Result, boost::noncopyable>("XPath2Result", boost::python::no_init)
			.def("getResultType", boost::python::pure_virtual(&XPath2Result::getResultType))
			.def("isNode", boost::python::pure_virtual(&XPath2Result::isNode))
			.def("getTypeInfo", boost::python::pure_virtual(&XPath2Result::getTypeInfo), boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getNumberValue", boost::python::pure_virtual(&XPath2Result::getNumberValue))
			.def("getIntegerValue", boost::python::pure_virtual(&XPath2Result::getIntegerValue))
			.def("getStringValue", boost::python::pure_virtual(&XPath2Result::getStringValue), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getBooleanValue", boost::python::pure_virtual(&XPath2Result::getBooleanValue))
			.def("getNodeValue", boost::python::pure_virtual(&XPath2Result::getNodeValue), boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getInvalidIteratorState", boost::python::pure_virtual(&XPath2Result::getInvalidIteratorState))
			.def("getSnapshotLength", boost::python::pure_virtual(&XPath2Result::getSnapshotLength))
			.def("iterateNext", boost::python::pure_virtual(&XPath2Result::iterateNext))
			.def("snapshotItem", boost::python::pure_virtual(&XPath2Result::snapshotItem))
			.def("release", boost::python::pure_virtual(&XPath2Result::release))
			;
	boost::python::scope XPath2ResultScope = PyXPath2Result;
	//! XPath2Result::ResultType
	boost::python::enum_<XPath2Result::ResultType>("ResultType")
			.value("FIRST_RESULT", XPath2Result::FIRST_RESULT)
			.value("ITERATOR_RESULT", XPath2Result::ITERATOR_RESULT)
			.value("SNAPSHOT_RESULT", XPath2Result::SNAPSHOT_RESULT)
			.export_values()
			;
}

} /* namespace pyxqilla */
