/*
 * XQillaNSResolver.cpp
 *
 *  Created on: 2013/06/17
 *      Author: mugwort_rc
 */

#include "XQillaNSResolver.h"

#include <boost/python.hpp>

#include <xqilla/dom-api/XQillaNSResolver.hpp>

namespace pyxqilla {

void XQillaNSResolver_init(void) {
	//! XQillaNSResolver
	boost::python::class_<XQillaNSResolver, boost::noncopyable, boost::python::bases<xercesc::DOMXPathNSResolver> >("XQillaNSResolver", boost::python::no_init)
			.def("addNamespaceBinding", boost::python::pure_virtual(&XQillaNSResolver::addNamespaceBinding))
			.def("lookupNamespaceURI", boost::python::pure_virtual(&XQillaNSResolver::lookupNamespaceURI), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("lookupPrefix", boost::python::pure_virtual(&XQillaNSResolver::lookupPrefix), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("release", boost::python::pure_virtual(&XQillaNSResolver::release))
			;
}

} /* namespace pyxqilla */
