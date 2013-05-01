/*
 * XQQuery.cpp
 *
 *  Created on: 2013/04/29
 *      Author: mugwort_rc
 */

#include "XQQuery.h"

#include <boost/python.hpp>

//! for forward delcaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/functions/XQUserFunction.hpp>
#include <xqilla/ast/XQGlobalVariable.hpp>
#include <xqilla/utils/DelayedModule.hpp>
#include <xqilla/optimizer/StaticTyper.hpp>

#include <xqilla/simple-api/XQQuery.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

template <typename STR>
class ModuleCacheDefVisitor
 : public boost::python::def_visitor<ModuleCacheDefVisitor<STR> >
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def("getByURI", &ModuleCacheDefVisitor::getByURI, boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("getByNamespace", &ModuleCacheDefVisitor::getByNamespace, boost::python::return_value_policy<boost::python::reference_existing_object>())
	;
}

static XQQuery* getByURI(ModuleCache& self, const STR uri) {
	pyxerces::XMLString buff(uri);
	return self.getByURI(buff.ptr());
}

static XQQuery* getByNamespace(ModuleCache& self, const STR ns) {
	pyxerces::XMLString buff(ns);
	return self.getByNamespace(buff.ptr());
}

};

template <typename STR>
class XQQueryDefVisitor
 : public boost::python::def_visitor<XQQueryDefVisitor<STR> >
{
friend class def_visitor_access;
public:
template<class T>
void visit(T& class_) const {
	class_
	.def("execute", static_cast<Result(*)(XQQuery&, const STR, DynamicContext*)>(&XQQueryDefVisitor::execute))
	.def("execute", static_cast<void(*)(XQQuery&, EventHandler*, const STR, DynamicContext*)>(&XQQueryDefVisitor::execute))
	.def("setQueryText", &XQQueryDefVisitor::setQueryText)
	.def("addDelayedFunction", static_cast<void(*)(XQQuery&, const STR, const STR, size_t, const STR, bool, int, int)>(&XQQueryDefVisitor::addDelayedFunction))
	.def("addDelayedFunction", static_cast<void(*)(XQQuery&, const STR, const STR, size_t, const STR, bool, int)>(&XQQueryDefVisitor::addDelayedFunction))
	.def("addDelayedFunction", static_cast<void(*)(XQQuery&, const STR, const STR, size_t, const STR, bool)>(&XQQueryDefVisitor::addDelayedFunction))
	.def("addDelayedFunction", static_cast<void(*)(XQQuery&, const STR, const STR, size_t, const STR)>(&XQQueryDefVisitor::addDelayedFunction))
	.def("setFile", &XQQueryDefVisitor::setFile)
	.def("setModuleTargetNamespace", &XQQueryDefVisitor::setModuleTargetNamespace)
	.def("importModule", &XQQueryDefVisitor::importModule)
	.def("findModuleForVariable", &XQQueryDefVisitor::findModuleForVariable, boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("findModuleForFunction", &XQQueryDefVisitor::findModuleForFunction, boost::python::return_value_policy<boost::python::reference_existing_object>())
	;
}

static Result execute(XQQuery& self, const STR templateQName, DynamicContext* context) {
	pyxerces::XMLString buff(templateQName);
	return self.execute(buff.ptr(), context);
}

static void execute(XQQuery& self, EventHandler* events, const STR templateQName, DynamicContext* context) {
	pyxerces::XMLString buff(templateQName);
	self.execute(events, buff.ptr(), context);
}

static void setQueryText(XQQuery& self, const STR v) {
	pyxerces::XMLString buff(v);
	self.setQueryText(buff.ptr());
}

static void addDelayedFunction(XQQuery& self, const STR uri, const STR name, size_t numArgs, const STR functionDeclaration, bool isPrivate, int line, int column) {
	pyxerces::XMLString buff1(uri), buff2(name), buff3(functionDeclaration);
	self.addDelayedFunction(buff1.ptr(), buff2.ptr(), numArgs, buff3.ptr(), isPrivate, line, column);
}

static void addDelayedFunction(XQQuery& self, const STR uri, const STR name, size_t numArgs, const STR functionDeclaration, bool isPrivate, int line) {
	pyxerces::XMLString buff1(uri), buff2(name), buff3(functionDeclaration);
	self.addDelayedFunction(buff1.ptr(), buff2.ptr(), numArgs, buff3.ptr(), isPrivate, line, 1);
}

static void addDelayedFunction(XQQuery& self, const STR uri, const STR name, size_t numArgs, const STR functionDeclaration, bool isPrivate) {
	pyxerces::XMLString buff1(uri), buff2(name), buff3(functionDeclaration);
	self.addDelayedFunction(buff1.ptr(), buff2.ptr(), numArgs, buff3.ptr(), isPrivate, 1);
}

static void addDelayedFunction(XQQuery& self, const STR uri, const STR name, size_t numArgs, const STR functionDeclaration) {
	pyxerces::XMLString buff1(uri), buff2(name), buff3(functionDeclaration);
	self.addDelayedFunction(buff1.ptr(), buff2.ptr(), numArgs, buff3.ptr(), false);
}

static void setFile(XQQuery& self, const STR file) {
	pyxerces::XMLString buff(file);
	self.setFile(buff.ptr());
}

static void setModuleTargetNamespace(XQQuery& self, const STR uri) {
	pyxerces::XMLString buff(uri);
	self.setModuleTargetNamespace(buff.ptr());
}

static void importModule(XQQuery& self, const STR szUri, VectorOfStrings* locations, const LocationInfo* location) {
	pyxerces::XMLString buff(szUri);
	self.importModule(buff.ptr(), locations, location);
}

static XQQuery* findModuleForVariable(XQQuery& self, const STR uri, const STR name) {
	pyxerces::XMLString buff1(uri), buff2(name);
	return self.findModuleForVariable(buff1.ptr(), buff2.ptr());
}

static XQQuery* findModuleForFunction(XQQuery& self, const STR uri, const STR name, int numArgs) {
	pyxerces::XMLString buff1(uri), buff2(name);
	return self.findModuleForFunction(buff1.ptr(), buff2.ptr(), numArgs);
}

};

//! XQQuery
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(XQQueryCreateDynamicContextOverloads, createDynamicContext, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(XQQueryStaticTypingOverloads, staticTyping, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(XQQueryStaticTypingOnceOverloads, staticTypingOnce, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(XQQueryAddDelayedFunction, addDelayedFunction, 4, 7)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(XQQuerySetIsLibraryModule, setIsLibraryModule, 0, 1)

void XQQuery_init(void) {
	//! ModuleCache
	boost::python::class_<ModuleCache, boost::noncopyable>("ModuleCache", boost::python::init<xercesc::MemoryManager*>())
			.def(ModuleCacheDefVisitor<char*>())
			.def("put", &ModuleCache::put)
			.def("getByURI", &ModuleCache::getByURI, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getByNamespace", &ModuleCache::getByNamespace, boost::python::return_value_policy<boost::python::reference_existing_object>())
			;
	//! XQQuery
	boost::python::class_<XQQuery, boost::noncopyable>("XQQuery", boost::python::no_init)
			.def(XQQueryDefVisitor<char*>())
			.def("createDynamicContext", &XQQuery::createDynamicContext, XQQueryCreateDynamicContextOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("execute", static_cast<Result(XQQuery::*)(DynamicContext*) const>(&XQQuery::execute))
			.def("execute", static_cast<Result(XQQuery::*)(const Item::Ptr&, DynamicContext*) const>(&XQQuery::execute))
			.def("execute", static_cast<Result(XQQuery::*)(const XMLCh*, DynamicContext*) const>(&XQQuery::execute))
			.def("execute", static_cast<void(XQQuery::*)(EventHandler*, DynamicContext*) const>(&XQQuery::execute))
			.def("execute", static_cast<void(XQQuery::*)(EventHandler*, const Item::Ptr&, DynamicContext*) const>(&XQQuery::execute))
			.def("execute", static_cast<void(XQQuery::*)(EventHandler*, const XMLCh*, DynamicContext*) const>(&XQQuery::execute))
			.def("staticResolution", &XQQuery::staticResolution)
			.def("staticTyping", &XQQuery::staticTyping, XQQueryStaticTypingOverloads())
			.def("staticTypingOnce", &XQQuery::staticTypingOnce, XQQueryStaticTypingOnceOverloads())
			.def("getQueryText", &XQQuery::getQueryText, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("setQueryText", &XQQuery::setQueryText)
			.def("getQueryPlan", &XQQuery::getQueryPlan)
			//! TODO: ASTNode
			.def("getQueryBody", &XQQuery::getQueryBody, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			.def("setQueryBody", &XQQuery::setQueryBody)
			.def("addFunction", &XQQuery::addFunction)
			.def("getFunctions", &XQQuery::getFunctions, boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("addDelayedFunction", static_cast<void(XQQuery::*)(const XMLCh*, const XMLCh*, size_t, const XMLCh*, bool, int, int)>(&XQQuery::addDelayedFunction), XQQueryAddDelayedFunction())
			.def("getDelayedFunctions", &XQQuery::getDelayedFunctions, boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("addVariable", &XQQuery::addVariable)
			.def("getVariables", &XQQuery::getVariables, boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("getImportedModules", &XQQuery::getImportedModules, boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("getModuleCache", &XQQuery::getModuleCache, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("isModuleCacheOwned", &XQQuery::isModuleCacheOwned)
			.def("getFile", &XQQuery::getFile, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("setFile", &XQQuery::setFile)
			.def("getVersion3", &XQQuery::getVersion3)
			.def("setVersion3", &XQQuery::setVersion3)
			.def("getStaticContext", &XQQuery::getStaticContext, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("getNext", &XQQuery::getNext, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setNext", &XQQuery::setNext)
			.def("setIsLibraryModule", &XQQuery::setIsLibraryModule, XQQuerySetIsLibraryModule())
			.def("getIsLibraryModule", &XQQuery::getIsLibraryModule)
			.def("setModuleTargetNamespace", &XQQuery::setModuleTargetNamespace)
			.def("getModuleTargetNamespace", &XQQuery::getModuleTargetNamespace, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("importModule", static_cast<void(XQQuery::*)(const XMLCh*, VectorOfStrings*, const LocationInfo*)>(&XQQuery::importModule))
			.def("importModule", static_cast<void(XQQuery::*)(XQQuery*)>(&XQQuery::importModule))
			.def("findModuleForVariable", &XQQuery::findModuleForVariable, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("findModuleForFunction", &XQQuery::findModuleForFunction, boost::python::return_value_policy<boost::python::reference_existing_object>())
			;
}

} /* namespace pyxqilla */
