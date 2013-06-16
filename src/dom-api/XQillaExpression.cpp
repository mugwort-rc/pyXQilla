/*
 * XQillaExpression.cpp
 *
 *  Created on: 2013/06/17
 *      Author: mugwort_rc
 */

#include "XQillaExpression.h"

#include <boost/python.hpp>

#include <xqilla/dom-api/XQillaExpression.hpp>

namespace pyxqilla {

void XQillaExpression_init(void) {
	//! XQillaExpression
	boost::python::class_<XQillaExpression, boost::noncopyable, boost::python::bases<xercesc::DOMXPathExpression> >("XQillaExpression", boost::python::no_init)
			.def("release", boost::python::pure_virtual(&XQillaExpression::release))
			;
}

} /* namespace pyxqilla */
