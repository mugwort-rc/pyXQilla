/*
 * XQillaException.cpp
 *
 *  Created on: 2013/02/24
 *      Author: mugwort_rc
 */

#include "XQillaException.h"

#include <boost/python.hpp>
#include <xqilla/exceptions/XQException.hpp>
#include <xqilla/exceptions/XQillaException.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

//! XQillaException
PyObject* pyXQillaExceptionType = nullptr;

void translateXQillaException(const XQillaException& e) {
	assert(pyXQillaExceptionType != nullptr);
	boost::python::object instance(e);

	boost::python::object exceptionType(boost::python::handle<>(boost::python::borrowed(pyXQillaExceptionType)));
	exceptionType.attr("cause") = instance;

	PyErr_SetString(pyXQillaExceptionType, pyxerces::XMLString(e.getString()).toString().c_str());
}

void XQillaException_init(void) {
	//! XQillaException
	auto PyXQillaException = boost::python::class_<XQillaException, boost::noncopyable, boost::python::bases<xercesc::DOMXPathException> >("XQillaException", boost::python::init<short, const XMLCh*>())
			.def(boost::python::init<const XQException&>())
			.def(boost::python::init<const XQillaException&>())
			.def("getCode", &XQillaException::getCode)
			.def("getString", &XQillaException::getString, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getDebug", &XQillaException::getDebug)
			.def("setDebug", &XQillaException::setDebug)
			.staticmethod("getDebug")
			.staticmethod("setDebug")
			;
	pyXQillaExceptionType = PyXQillaException.ptr();
	boost::python::register_exception_translator<XQillaException>(&translateXQillaException);
	boost::python::scope XQillaExceptionScope = PyXQillaException;
	//! XQillaException::valExtension
	boost::python::enum_<XQillaException::valExtension>("valExtension")
			.value("RUNTIME_ERR", XQillaException::RUNTIME_ERR)
			;
}

} /* namespace pyxqilla */
