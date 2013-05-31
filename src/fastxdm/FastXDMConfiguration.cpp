/*
 * FastXDMConfiguration.cpp
 *
 *  Created on: 2013/05/31
 *      Author: mugwort_rc
 */

#include "FastXDMConfiguration.h"

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

#include <xqilla/fastxdm/FastXDMConfiguration.hpp>

namespace pyxqilla {

void FastXDMConfiguration_init(void) {
	//! FastXDMConfiguration
	boost::python::class_<FastXDMConfiguration, boost::noncopyable, boost::python::bases<XQillaConfiguration> >("FastXDMConfiguration")
			//! TODO: DocumentCache
			.def("createDocumentCache", &FastXDMConfiguration::createDocumentCache, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("createSequenceBuilder", &FastXDMConfiguration::createSequenceBuilder, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: ItemFactory
			.def("createItemFactory", &FastXDMConfiguration::createItemFactory, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: UpdateFactory
			.def("createUpdateFactory", &FastXDMConfiguration::createUpdateFactory, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: URIResolver
			.def("createDefaultURIResolver", &FastXDMConfiguration::createDefaultURIResolver, boost::python::return_value_policy<boost::python::reference_existing_object>())
			//! TODO: ASTToXML
			.def("createASTToXML", &FastXDMConfiguration::createASTToXML, boost::python::return_value_policy<boost::python::reference_existing_object>())
			;
}

} /* namespace pyxqilla */
