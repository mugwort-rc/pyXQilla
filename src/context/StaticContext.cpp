/*
 * StaticContext.cpp
 *
 *  Created on: 2013/07/03
 *      Author: mugwort_rc
 */

#include "StaticContext.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/functions/FuncFactory.hpp>
#include <xqilla/items/DatatypeFactory.hpp>
#include <xqilla/context/Collation.hpp>
#include <xqilla/context/VariableTypeStore.hpp>
#include <xqilla/context/ItemFactory.hpp>
#include <xqilla/ast/StaticType.hpp>
#include <xqilla/context/ModuleResolver.hpp>
#include <xqilla/context/ExternalFunctionResolver.hpp>
#include <xqilla/context/MessageListener.hpp>
#include <xqilla/functions/ExternalFunction.hpp>
#include <xqilla/simple-api/XQillaConfiguration.hpp>
#include <xqilla/functions/XQUserFunction.hpp>
#include <xqilla/dom-api/XQillaNSResolver.hpp>
#include <xqilla/context/VariableStore.hpp>
#include <xqilla/simple-api/XQQuery.hpp>
#include <xercesc/util/XMLEntityResolver.hpp>

#include <xqilla/context/StaticContext.hpp>

namespace pyxqilla {

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StaticContextCreateModuleContextOverloads, createModuleContext, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StaticContextCreateDynamicContextOverloads, createDynamicContext, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StaticContextCreateDebugQueryContextOverloads, createDebugQueryContext, 6, 7)

void StaticContext_init(void) {
	//! StaticContext
	auto PyStaticContext = boost::python::class_<StaticContext, boost::noncopyable>("StaticContext", boost::python::no_init)
			.def("createModuleContext", &StaticContext::createModuleContext, StaticContextCreateModuleContextOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("createDynamicContext", &StaticContext::createDynamicContext, StaticContextCreateDynamicContextOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("createDebugQueryContext", &StaticContext::createDebugQueryContext, StaticContextCreateDebugQueryContextOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("getConfiguration", &StaticContext::getConfiguration, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getLanguage", &StaticContext::getLanguage)
			.def("getItemFactory", &StaticContext::getItemFactory, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setItemFactory", &StaticContext::setItemFactory)
			.def("getContextItemType", &StaticContext::getContextItemType, boost::python::return_internal_reference<>())
			.def("setContextItemType", &StaticContext::setContextItemType)
			.def("getXPath1CompatibilityMode", &StaticContext::getXPath1CompatibilityMode)
			.def("setXPath1CompatibilityMode", &StaticContext::setXPath1CompatibilityMode)
			.def("getNSResolver", &StaticContext::getNSResolver, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getUriBoundToPrefix", &StaticContext::getUriBoundToPrefix, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getPrefixBoundToUri", &StaticContext::getPrefixBoundToUri, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("setNSResolver", &StaticContext::setNSResolver)
			.def("setNamespaceBinding", &StaticContext::setNamespaceBinding)
			.def("getDefaultElementAndTypeNS", &StaticContext::getDefaultElementAndTypeNS, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("setDefaultElementAndTypeNS", &StaticContext::setDefaultElementAndTypeNS)
			.def("getDefaultFuncNS", &StaticContext::getDefaultFuncNS, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("setDefaultFuncNS", &StaticContext::setDefaultFuncNS)
			.def("getDocumentCache", &StaticContext::getDocumentCache, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setDocumentCache", &StaticContext::setDocumentCache)
			.def("isTypeOrDerivedFromType", &StaticContext::isTypeOrDerivedFromType)
			.def("setXMLEntityResolver", &StaticContext::setXMLEntityResolver)
			.def("getXMLEntityResolver", &StaticContext::getXMLEntityResolver, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setModuleResolver", &StaticContext::setModuleResolver)
			.def("getModuleResolver", &StaticContext::getModuleResolver, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("resolveModuleURI", &StaticContext::resolveModuleURI, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("addSchemaLocation", &StaticContext::addSchemaLocation)
			.def("getVariableTypeStore", &StaticContext::getVariableTypeStore, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("addTemplate", &StaticContext::addTemplate)
			.def("lookUpNamedTemplate", &StaticContext::lookUpNamedTemplate, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getTemplateRules", &StaticContext::getTemplateRules, boost::python::return_internal_reference<>())
			.def("addCustomFunction", &StaticContext::addCustomFunction)
			.def("removeCustomFunction", &StaticContext::removeCustomFunction)
			.def("lookUpFunction", &StaticContext::lookUpFunction, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setExternalFunctionResolver", &StaticContext::setExternalFunctionResolver)
			.def("getExternalFunctionResolver", &StaticContext::getExternalFunctionResolver, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("addExternalFunction", &StaticContext::addExternalFunction)
			.def("lookUpExternalFunction", &StaticContext::lookUpExternalFunction, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getCollation", &StaticContext::getCollation, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("addCollation", &StaticContext::addCollation)
			.def("getDefaultCollation", &StaticContext::getDefaultCollation, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setDefaultCollation", &StaticContext::setDefaultCollation)
			.def("getBaseURI", &StaticContext::getBaseURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("setBaseURI", &StaticContext::setBaseURI)
			.def("getNodeSetOrdering", &StaticContext::getNodeSetOrdering)
			.def("setNodeSetOrdering", &StaticContext::setNodeSetOrdering)
			.def("getConstructionMode", &StaticContext::getConstructionMode)
			.def("setConstructionMode", &StaticContext::setConstructionMode)
			.def("setPreserveBoundarySpace", &StaticContext::setPreserveBoundarySpace)
			.def("getPreserveBoundarySpace", &StaticContext::getPreserveBoundarySpace)
			.def("getDefaultFLWOROrderingMode", &StaticContext::getDefaultFLWOROrderingMode)
			.def("setDefaultFLWOROrderingMode", &StaticContext::setDefaultFLWOROrderingMode)
			.def("setInheritNamespaces", &StaticContext::setInheritNamespaces)
			.def("getInheritNamespaces", &StaticContext::getInheritNamespaces)
			.def("setPreserveNamespaces", &StaticContext::setPreserveNamespaces)
			.def("getPreserveNamespaces", &StaticContext::getPreserveNamespaces)
			.def("setRevalidationMode", &StaticContext::setRevalidationMode)
			.def("getRevalidationMode", &StaticContext::getRevalidationMode)
			.def("setMessageListener", &StaticContext::setMessageListener)
			.def("getMessageListener", &StaticContext::getMessageListener, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setModule", &StaticContext::setModule)
			.def("getModule", &StaticContext::getModule, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getProjection", &StaticContext::getProjection)
			.def("setProjection", &StaticContext::setProjection)
			.def("getDoLintWarnings", &StaticContext::getDoLintWarnings)
			.def("setDoLintWarnings", &StaticContext::setDoLintWarnings)
			.def("allocateTempVarName", &StaticContext::allocateTempVarName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getMemoryManager", &StaticContext::getMemoryManager, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setMemoryManager", &StaticContext::setMemoryManager)
			.def("setFTCase", &StaticContext::setFTCase)
			.def("getFTCase", &StaticContext::getFTCase)
			;
	boost::python::scope StaticContextScope = PyStaticContext;
	//! StaticContext::NodeSetOrdering
	boost::python::enum_<StaticContext::NodeSetOrdering>("NodeSetOrdering")
			.value("ORDERING_ORDERED", StaticContext::ORDERING_ORDERED)
			.value("ORDERING_UNORDERED", StaticContext::ORDERING_UNORDERED)
			.export_values()
			;
	//! StaticContext::ConstructionMode
	boost::python::enum_<StaticContext::ConstructionMode>("ConstructionMode")
			.value("CONSTRUCTION_MODE_PRESERVE", StaticContext::CONSTRUCTION_MODE_PRESERVE)
			.value("CONSTRUCTION_MODE_STRIP", StaticContext::CONSTRUCTION_MODE_STRIP)
			.export_values()
			;
	//! StaticContext::FLWOROrderingMode
	boost::python::enum_<StaticContext::FLWOROrderingMode>("FLWOROrderingMode")
			.value("FLWOR_ORDER_EMPTY_GREATEST", StaticContext::FLWOR_ORDER_EMPTY_GREATEST)
			.value("FLWOR_ORDER_EMPTY_LEAST", StaticContext::FLWOR_ORDER_EMPTY_LEAST)
			.export_values()
			;
	//! StaticContext::FTCaseOption
	boost::python::enum_<StaticContext::FTCaseOption>("FTCaseOption")
			.value("NONE", StaticContext::NONE)
			.value("CASE_INSENSITIVE", StaticContext::CASE_INSENSITIVE)
			.value("CASE_SENSITIVE", StaticContext::CASE_SENSITIVE)
			.value("UPPERCASE", StaticContext::UPPERCASE)
			.value("LOWERCASE", StaticContext::LOWERCASE)
			.export_values()
			;
}

} /* namespace pyxqilla */
