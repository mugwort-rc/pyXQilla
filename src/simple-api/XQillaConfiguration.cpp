/*
 * XQillaConfiguration.cpp
 *
 *  Created on: 2013/05/31
 *      Author: mugwort_rc
 */

#include "XQillaConfiguration.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/schema/DocumentCache.hpp>
#include <xqilla/events/SequenceBuilder.hpp>
#include <xqilla/context/ItemFactory.hpp>
#include <xqilla/context/UpdateFactory.hpp>
#include <xqilla/context/URIResolver.hpp>
#include <xqilla/optimizer/ASTToXML.hpp>
#include <xqilla/context/StaticContext.hpp>
#include <xqilla/context/DynamicContext.hpp>

#include <xqilla/simple-api/XQillaConfiguration.hpp>

namespace pyxqilla {

void XQillaConfiguration_init(void) {
	//! XQillaConfiguration
	boost::python::class_<XQillaConfiguration, boost::noncopyable>("XQillaConfiguration", boost::python::no_init)
			//! TODO: DocumentCache
			.def("createDocumentCache", boost::python::pure_virtual(&XQillaConfiguration::createDocumentCache), boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("createSequenceBuilder", boost::python::pure_virtual(&XQillaConfiguration::createSequenceBuilder), boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: ItemFactory
			.def("createItemFactory", boost::python::pure_virtual(&XQillaConfiguration::createItemFactory), boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: UpdateFactory
			.def("createUpdateFactory", boost::python::pure_virtual(&XQillaConfiguration::createUpdateFactory), boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: URIResolver
			.def("createDefaultURIResolver", boost::python::pure_virtual(&XQillaConfiguration::createDefaultURIResolver), boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: ASTToXML
			.def("createASTToXML", boost::python::pure_virtual(&XQillaConfiguration::createASTToXML), boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("populateStaticContext", &XQillaConfiguration::populateStaticContext)
			.def("populateDynamicContext", &XQillaConfiguration::populateDynamicContext)
			.def("testInterrupt", &XQillaConfiguration::testInterrupt)
			;
}

} /* namespace pyxqilla */
