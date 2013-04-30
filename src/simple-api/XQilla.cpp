/*
 * XQilla.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "XQilla.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/simple-api/XQillaConfiguration.hpp>
#include <xqilla/optimizer/Optimizer.hpp>
#include <xqilla/functions/XQUserFunction.hpp>
#include <xqilla/simple-api/XQQuery.hpp>

#include <xqilla/simple-api/XQilla.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

template <class STR>
class XQillaDefVisitor
: public boost::python::def_visitor<XQillaDefVisitor<STR> >
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def("parse", static_cast<XQQuery*(*)(const STR&, DynamicContext*, const STR&, unsigned int, xercesc::MemoryManager*, XQQuery*)>(&XQillaDefVisitor::parse), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parse", static_cast<XQQuery*(*)(const STR&, DynamicContext*, const STR&, unsigned int, xercesc::MemoryManager*)>(&XQillaDefVisitor::parse), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parse", static_cast<XQQuery*(*)(const STR&, DynamicContext*, const STR&, unsigned int)>(&XQillaDefVisitor::parse), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parse", static_cast<XQQuery*(*)(const STR&, DynamicContext*, const STR&)>(&XQillaDefVisitor::parse), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parse", static_cast<XQQuery*(*)(const STR&, DynamicContext*)>(&XQillaDefVisitor::parse), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parse", static_cast<XQQuery*(*)(const STR&)>(&XQillaDefVisitor::parse), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parseFromURI", static_cast<XQQuery*(*)(const STR&, DynamicContext*, unsigned int, xercesc::MemoryManager*, XQQuery*)>(&XQillaDefVisitor::parseFromURI), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parseFromURI", static_cast<XQQuery*(*)(const STR&, DynamicContext*, unsigned int, xercesc::MemoryManager*)>(&XQillaDefVisitor::parseFromURI), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parseFromURI", static_cast<XQQuery*(*)(const STR&, DynamicContext*, unsigned int)>(&XQillaDefVisitor::parseFromURI), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parseFromURI", static_cast<XQQuery*(*)(const STR&, DynamicContext*)>(&XQillaDefVisitor::parseFromURI), boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("parseFromURI", static_cast<XQQuery*(*)(const STR&)>(&XQillaDefVisitor::parseFromURI), boost::python::return_value_policy<boost::python::reference_existing_object>())
	;
}

static XQQuery* parse(const STR& query, DynamicContext* context, const STR& queryFile, unsigned int flags, xercesc::MemoryManager* memMgr, XQQuery *result) {
	pyxerces::XMLString buff1(query), buff2(queryFile);
	return XQilla::parse(buff1.ptr(), context, buff2.ptr(), flags, memMgr, result);
}

static XQQuery* parse(const STR& query, DynamicContext* context, const STR& queryFile, unsigned int flags, xercesc::MemoryManager* memMgr) {
	return parse(query, context, queryFile, flags, memMgr, nullptr);
}

static XQQuery* parse(const STR& query, DynamicContext* context, const STR& queryFile, unsigned int flags) {
	return parse(query, context, queryFile, flags, xercesc::XMLPlatformUtils::fgMemoryManager);
}

static XQQuery* parse(const STR& query, DynamicContext* context, const STR& queryFile) {
	return parse(query, context, queryFile, 0);
}

static XQQuery* parse(const STR& query, DynamicContext* context) {
	return parse(query, context, STR());
}

static XQQuery* parse(const STR& query) {
	return parse(query, nullptr);
}

static XQQuery* parseFromURI(const STR& queryFile, DynamicContext* context, unsigned int flags, xercesc::MemoryManager *memMgr, XQQuery *result) {
	pyxerces::XMLString buff(queryFile);
	return XQilla::parseFromURI(buff.ptr(), context, flags, memMgr, result);
}

static XQQuery* parseFromURI(const STR& queryFile, DynamicContext* context, unsigned int flags, xercesc::MemoryManager *memMgr) {
	return parseFromURI(queryFile, context, flags, memMgr, nullptr);
}

static XQQuery* parseFromURI(const STR& queryFile, DynamicContext* context, unsigned int flags) {
	return parseFromURI(queryFile, context, flags, xercesc::XMLPlatformUtils::fgMemoryManager);
}

static XQQuery* parseFromURI(const STR& queryFile, DynamicContext* context) {
	return parseFromURI(queryFile, context, 0);
}

static XQQuery* parseFromURI(const STR& queryFile) {
	return parseFromURI(queryFile, nullptr);
}

};

//! XQilla
BOOST_PYTHON_FUNCTION_OVERLOADS(XQillaParseOverloads, XQilla::parse, 1, 6)
BOOST_PYTHON_FUNCTION_OVERLOADS(XQillaParseFromInputSourceOverloads, XQilla::parse, 1, 5)
BOOST_PYTHON_FUNCTION_OVERLOADS(XQillaParseFromURIOverloads, XQilla::parseFromURI, 1, 5)
BOOST_PYTHON_FUNCTION_OVERLOADS(XQillaCreateContextOverloads, XQilla::createContext, 0, 3)

void XQilla_init(void) {
	//! XQilla
	auto PyXQilla = boost::python::class_<XQilla, boost::noncopyable>("XQilla", boost::python::init<boost::python::optional<xercesc::MemoryManager*> >())
			.def(XQillaDefVisitor<std::string>())
			.def("parse", static_cast<XQQuery*(*)(const XMLCh*, DynamicContext*, const XMLCh*, unsigned int, xercesc::MemoryManager*, XQQuery*)>(&XQilla::parse), XQillaParseOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("parse", static_cast<XQQuery*(*)(const xercesc::InputSource&, DynamicContext*, unsigned int, xercesc::MemoryManager*, XQQuery*)>(&XQilla::parse), XQillaParseFromInputSourceOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("parseFromURI", &XQilla::parseFromURI, XQillaParseFromURIOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.def("createContext", &XQilla::createContext, XQillaCreateContextOverloads()[boost::python::return_value_policy<boost::python::reference_existing_object>()])
			.staticmethod("parse")
			.staticmethod("parseFromURI")
			.staticmethod("createContext")
			;
	boost::python::scope XQillaScope = PyXQilla;
	//! XQilla::Flags
	boost::python::enum_<XQilla::Flags>("Flags")
			.value("NO_STATIC_RESOLUTION", XQilla::NO_STATIC_RESOLUTION)
			.value("NO_ADOPT_CONTEXT", XQilla::NO_ADOPT_CONTEXT)
			.value("DEBUG_QUERY", XQilla::DEBUG_QUERY)
			.value("NO_OPTIMIZATION", XQilla::NO_OPTIMIZATION)
			.value("NO_DEFAULT_MODULES", XQilla::NO_DEFAULT_MODULES)
			.export_values()
			;
	//! XQilla::Language
	boost::python::enum_<XQilla::Language>("Language")
			.value("XQUERY", XQilla::XQUERY)
			.value("XPATH2", XQilla::XPATH2)
			.value("FULLTEXT", XQilla::FULLTEXT)
			.value("UPDATE", XQilla::UPDATE)
			.value("EXTENSIONS", XQilla::EXTENSIONS)
			.value("XSLT2", XQilla::XSLT2)
			.value("VERSION3", XQilla::VERSION3)
			.value("XQUERY_FULLTEXT", XQilla::XQUERY_FULLTEXT)
			.value("XQUERY_UPDATE", XQilla::XQUERY_UPDATE)
			.value("XQUERY_FULLTEXT_UPDATE", XQilla::XQUERY_FULLTEXT_UPDATE)
			.value("XPATH2_FULLTEXT", XQilla::XPATH2_FULLTEXT)
			.value("XSLT2_FULLTEXT", XQilla::XSLT2_FULLTEXT)
			.value("XQUERY3", XQilla::XQUERY3)
			.value("XQUERY3_FULLTEXT", XQilla::XQUERY3_FULLTEXT)
			.value("XQUERY3_UPDATE", XQilla::XQUERY3_UPDATE)
			.value("XQUERY3_FULLTEXT_UPDATE", XQilla::XQUERY3_FULLTEXT_UPDATE)
			.value("XPATH3", XQilla::XPATH3)
			.value("XPATH3_FULLTEXT", XQilla::XPATH3_FULLTEXT)
			.value("XSLT3", XQilla::XSLT3)
			.value("XSLT3_FULLTEXT", XQilla::XSLT3_FULLTEXT)
			.export_values()
			;
}

} /* namespace pyxqilla */
