/*
 * XercesConfiguration.cpp
 *
 *  Created on: 2013/05/31
 *      Author: mugwort_rc
 */

#include "XercesConfiguration.h"

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
#include <xercesc/dom/DOMNode.hpp>

#include <xqilla/xerces/XercesConfiguration.hpp>

namespace pyxqilla {

void XercesConfiguration_init(void) {
	//! XercesConfiguration
	boost::python::class_<XercesConfiguration, boost::noncopyable, boost::python::bases<XQillaConfiguration> >("XercesConfiguration")
			//! TODO: DocumentCache
			.def("createDocumentCache", &XercesConfiguration::createDocumentCache, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("createSequenceBuilder", &XercesConfiguration::createSequenceBuilder, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: ItemFactory
			.def("createItemFactory", &XercesConfiguration::createItemFactory, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: UpdateFactory
			.def("createUpdateFactory", &XercesConfiguration::createUpdateFactory, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: URIResolver
			.def("createDefaultURIResolver", &XercesConfiguration::createDefaultURIResolver, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: ASTToXML
			.def("createASTToXML", &XercesConfiguration::createASTToXML, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("createNode", &XercesConfiguration::createNode)
			;
}

} /* namespace pyxqilla */
