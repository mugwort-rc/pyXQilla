/*
 * XQillaPlatformUtils.cpp
 *
 *  Created on: 2013/02/24
 *      Author: mugwort_rc
 */

#include "XQillaPlatformUtils.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xercesc/framework/MemoryManager.hpp>

#include <xqilla/utils/XQillaPlatformUtils.hpp>

namespace pyxqilla {

// XQillaPlatformUtils
BOOST_PYTHON_FUNCTION_OVERLOADS(XQillaPlatformUtilsInitializeOverloads, XQillaPlatformUtils::initialize, 0, 1)

void XQillaPlatformUtils_init(void) {
	//! XQillaPlatformUtils
	boost::python::class_<XQillaPlatformUtils, boost::noncopyable>("XQillaPlatformUtils", boost::python::no_init)
			.def("initialize", &XQillaPlatformUtils::initialize, XQillaPlatformUtilsInitializeOverloads())
			.def("terminate", &XQillaPlatformUtils::terminate)
			.def("enableExtendedPrecision", &XQillaPlatformUtils::enableExtendedPrecision)
			.staticmethod("initialize")
			.staticmethod("terminate")
			.staticmethod("enableExtendedPrecision")
			;
}

} /* namespace pyxqilla */
