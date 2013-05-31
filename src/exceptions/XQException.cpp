/*
 * XQException.cpp
 *
 *  Created on: 2013/05/31
 *      Author: mugwort_rc
 */

#include "XQException.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/ast/LocationInfo.hpp>

#include <xqilla/exceptions/XQException.hpp>

namespace pyxqilla {

//! XQException
PyObject* pyXQExceptionType = nullptr;

void translateXQException(const XQException& e) {
	assert(pyXQExceptionType != nullptr);
	boost::python::object instance(e);
	PyErr_SetObject(pyXQExceptionType, instance.ptr());
}

void XQException_init(void) {
	//! XQException
	auto PyXQException = boost::python::class_<XQException>("XQException", boost::python::init<const XMLCh*, const XMLCh*, unsigned int, unsigned int, const char*, unsigned int>())
			.def("getType", &XQException::getType, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getError", &XQException::getError, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getXQueryFile", &XQException::getXQueryFile, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getXQueryLine", &XQException::getXQueryLine)
			.def("getXQueryColumn", &XQException::getXQueryColumn)
			.def("setXQueryPosition", static_cast<void(XQException::*)(const XMLCh*, unsigned int, unsigned int)>(&XQException::setXQueryPosition))
			.def("setXQueryPosition", static_cast<void(XQException::*)(const LocationInfo*)>(&XQException::setXQueryPosition))
			.def("getCppFunction", &XQException::getCppFunction, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getCppFile", &XQException::getCppFile)
			.def("getCppLine", &XQException::getCppLine)
			.def("printDebug", &XQException::printDebug)
			;
	pyXQExceptionType = PyXQException.ptr();
	boost::python::register_exception_translator<XQException>(&translateXQException);
}

} /* namespace pyxqilla */
