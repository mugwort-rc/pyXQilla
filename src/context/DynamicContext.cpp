/*
 * DynamicContext.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "DynamicContext.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/runtime/Result.hpp>
#include <xqilla/items/Item.hpp>
#include <xqilla/context/URIResolver.hpp>
#include <xqilla/context/VariableStore.hpp>
#include <xqilla/events/SequenceBuilder.hpp>
#include <xqilla/context/UpdateFactory.hpp>
#include <xqilla/context/RegexGroupStore.hpp>
#include <xqilla/debug/DebugListener.hpp>
#include <xqilla/debug/StackFrame.hpp>
#include <xqilla/optimizer/QueryPathNode.hpp>
#include <xercesc/sax/InputSource.hpp>

#include <xqilla/context/DynamicContext.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

template <class STR>
class DynamicContextDefVisitor
: public boost::python::def_visitor<DynamicContextDefVisitor<STR> >
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def("setExternalVariable", static_cast<void(*)(DynamicContext&, const STR&, const STR&, const Result&)>(&DynamicContextDefVisitor::setExternalVariable))
	.def("setExternalVariable", static_cast<void(*)(DynamicContext&, const STR&, const Result&)>(&DynamicContextDefVisitor::setExternalVariable))
	.def("resolveDocument", static_cast<Sequence(*)(DynamicContext&, const STR&, const LocationInfo*, const QueryPathNode*)>(&DynamicContextDefVisitor::resolveDocument))
	.def("resolveDocument", static_cast<Sequence(*)(DynamicContext&, const STR&, const LocationInfo*)>(&DynamicContextDefVisitor::resolveDocument))
	.def("resolveDocument", static_cast<Sequence(*)(DynamicContext&, const STR&)>(&DynamicContextDefVisitor::resolveDocument))
	.def("resolveCollection", static_cast<Sequence(*)(DynamicContext&, const STR&, const LocationInfo*, const QueryPathNode*)>(&DynamicContextDefVisitor::resolveCollection))
	.def("resolveCollection", static_cast<Sequence(*)(DynamicContext&, const STR&, const LocationInfo*)>(&DynamicContextDefVisitor::resolveCollection))
	.def("resolveCollection", static_cast<Sequence(*)(DynamicContext&, const STR&)>(&DynamicContextDefVisitor::resolveCollection))
	.def("putDocument", &DynamicContextDefVisitor::putDocument)
	;
}

static void setExternalVariable(DynamicContext& self, const STR& namespaceURI, const STR& name, const Result& value) {
	pyxerces::XMLString buff1(namespaceURI), buff2(name);
	return self.setExternalVariable(buff1.ptr(), buff2.ptr(), value);
}

static void setExternalVariable(DynamicContext& self, const STR& qname, const Result& value) {
	pyxerces::XMLString buff(qname);
	return self.setExternalVariable(buff.ptr(), value);
}

static Sequence resolveDocument(DynamicContext& self, const STR& uri, const LocationInfo *location, const QueryPathNode *projection) {
	pyxerces::XMLString buff(uri);
	return self.resolveDocument(buff.ptr(), location, projection);
}

static Sequence resolveDocument(DynamicContext& self, const STR& uri, const LocationInfo *location) {
	return resolveDocument(self, uri, location, nullptr);
}

static Sequence resolveDocument(DynamicContext& self, const STR& uri) {
	return resolveDocument(self, uri, nullptr);
}

static Sequence resolveCollection(DynamicContext& self, const STR& uri, const LocationInfo *location, const QueryPathNode *projection) {
	pyxerces::XMLString buff(uri);
	return self.resolveCollection(buff.ptr(), location, projection);
}

static Sequence resolveCollection(DynamicContext& self, const STR& uri, const LocationInfo *location) {
	return resolveCollection(self, uri, location, nullptr);
}

static Sequence resolveCollection(DynamicContext& self, const STR& uri) {
	return resolveCollection(self, uri, nullptr);
}

static bool putDocument(DynamicContext& self, Node::Ptr& document, const STR& uri) {
	pyxerces::XMLString buff(uri);
	return self.putDocument(document, buff.ptr());
}

};

//! DynamicContext
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(DynamicContextCreateModuleDynamicContextOverloads, createModuleDynamicContext, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(DynamicContextParseDocumentOverloads, parseDocument, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(DynamicContextResolveDocumentOverloads, resolveDocument, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(DynamicContextResolveCollectionOverloads, resolveCollection, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(DynamicCOntextResolveDefaultCollectionOverloads, resolveDefaultCollection, 0, 1)

void DynamicContext_init(void) {
	//! DynamicContext
	boost::python::class_<DynamicContext, boost::noncopyable>("DynamicContext", boost::python::no_init)
			.def(DynamicContextDefVisitor<std::string>())
			.def("createModuleDynamicContext", &DynamicContext::createModuleDynamicContext, DynamicContextCreateModuleDynamicContextOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("clearDynamicContext", &DynamicContext::clearDynamicContext)
			.def("getContextItem", &DynamicContext::getContextItem)
			.def("setContextItem", &DynamicContext::setContextItem)
			.def("getContextPosition", &DynamicContext::getContextPosition)
			.def("setContextPosition", &DynamicContext::setContextPosition)
			.def("getContextSize", &DynamicContext::getContextSize)
			.def("setContextSize", &DynamicContext::setContextSize)
			// TODO: VariableStore
			.def("getVariableStore", &DynamicContext::getVariableStore, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			.def("setVariableStore", &DynamicContext::setVariableStore)
			// TODO: VariableStore
			.def("getGlobalVariableStore", &DynamicContext::getGlobalVariableStore, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			.def("setGlobalVariableStore", &DynamicContext::setGlobalVariableStore)
			.def("setExternalVariable", static_cast<void(DynamicContext::*)(const XMLCh*, const XMLCh*, const Result&)>(&DynamicContext::setExternalVariable))
			.def("setExternalVariable", static_cast<void(DynamicContext::*)(const XMLCh*, const Result&)>(&DynamicContext::setExternalVariable))
			.def("getRegexGroupStore", &DynamicContext::getRegexGroupStore, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setRegexGroupStore", &DynamicContext::setRegexGroupStore)
			.def("getCurrentTime", &DynamicContext::getCurrentTime)
			.def("setCurrentTime", &DynamicContext::setCurrentTime)
			// TODO: ATDurationOrDerived::Ptr
			.def("getImplicitTimezone", &DynamicContext::getImplicitTimezone)
			.def("setImplicitTimezone", &DynamicContext::setImplicitTimezone)
			.def("registerURIResolver", &DynamicContext::registerURIResolver)
			// TODO: URIResolver
			.def("getDefaultURIResolver", &DynamicContext::getDefaultURIResolver, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			.def("setDefaultURIResolver", &DynamicContext::setDefaultURIResolver)
			.def("setDebugListener", &DynamicContext::setDebugListener)
			.def("getDebugListener", &DynamicContext::getDebugListener, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setStackFrame", &DynamicContext::setStackFrame)
			.def("getStackFrame", &DynamicContext::getStackFrame, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("parseDocument", &DynamicContext::parseDocument, DynamicContextParseDocumentOverloads())
			.def("resolveDocument", &DynamicContext::resolveDocument, DynamicContextResolveDocumentOverloads())
			.def("resolveCollection", &DynamicContext::resolveCollection, DynamicContextResolveCollectionOverloads())
			.def("resolveDefaultCollection", &DynamicContext::resolveDefaultCollection, DynamicCOntextResolveDefaultCollectionOverloads())
			.def("putDocument", &DynamicContext::putDocument)
			.def("createSequenceBuilder", &DynamicContext::createSequenceBuilder, boost::python::return_value_policy<boost::python::reference_existing_object>())
			// TODO: UpdateFactory
			.def("createUpdateFactory", &DynamicContext::createUpdateFactory, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			.def("testInterrupt", &DynamicContext::testInterrupt)
			;
}

} /* namespace pyxqilla */
