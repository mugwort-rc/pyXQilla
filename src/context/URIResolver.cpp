/*
 * URIResolver.cpp
 *
 *  Created on: 2013/08/03
 *      Author: mugwort_rc
 */

#include "URIResolver.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/optimizer/QueryPathNode.hpp>

#include <xqilla/context/URIResolver.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

template <typename STR>
class URIResolverDefVisitor
: public boost::python::def_visitor<URIResolverDefVisitor<STR> >
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def("resolveDocument", &resolveDocument)
	.def("resolveCollection", &resolveCollection)
	.def("putDocument", &putDocument)
	;
}

static bool resolveDocument(URIResolver& self, Sequence &result, const STR uri, DynamicContext *context, const QueryPathNode *projection)
{
	pyxerces::XMLString buff(uri);
	return self.resolveDocument(result, buff.ptr(), context, projection);
}

static bool resolveCollection(URIResolver& self, Sequence &result, const STR uri, DynamicContext *context, const QueryPathNode *projection)
{
	pyxerces::XMLString buff(uri);
	return self.resolveCollection(result, buff.ptr(), context, projection);
}

static bool putDocument(URIResolver& self, const Node::Ptr &document, const STR uri, DynamicContext *context)
{
	pyxerces::XMLString buff(uri);
	return self.putDocument(document, buff.ptr(), context);
}

};

class URIResolverWrapper
: public URIResolver, public boost::python::wrapper<URIResolver>
{
public:
URIResolverWrapper(void)
{}
virtual ~URIResolverWrapper(void)
{}

bool resolveDocument(Sequence &result, const XMLCh* uri, DynamicContext *context, const QueryPathNode *projection)
{
	boost::python::object obj = this->get_override("resolveDocument")(pyxerces::XMLString(uri), boost::python::ptr(context), boost::python::ptr(projection));
	if ( obj.is_none() || ! boost::python::extract<boost::python::tuple>(obj).check() ) {
		return false;
	}
	boost::python::tuple tup = boost::python::extract<boost::python::tuple>(obj);
	if ( boost::python::len(tup) != 2 ) {
		return false;
	}
	if ( ! boost::python::extract<bool>(tup[0]).check() || ! boost::python::extract<Node::Ptr>(tup[1]).check() ) {
		return false;
	}
	bool rflag = boost::python::extract<bool>(tup[0]);
	Node::Ptr ptr = boost::python::extract<Node::Ptr>(tup[1]);
	if ( ptr.isNull() ) {
		return false;
	}
	result = Sequence(ptr);
	return rflag;
}

bool resolveCollection(Sequence &result, const XMLCh* uri, DynamicContext *context, const QueryPathNode *projection)
{
	boost::python::object obj = this->get_override("resolveCollection")(pyxerces::XMLString(uri), boost::python::ptr(context), boost::python::ptr(projection));
	if ( obj.is_none() || ! boost::python::extract<boost::python::tuple>(obj).check() ) {
		return false;
	}
	boost::python::tuple tup = boost::python::extract<boost::python::tuple>(obj);
	if ( boost::python::len(tup) != 2 ) {
		return false;
	}
	if ( ! boost::python::extract<bool>(tup[0]).check() || ! boost::python::extract<Node::Ptr>(tup[1]).check() ) {
		return false;
	}
	bool rflag = boost::python::extract<bool>(tup[0]);
	Node::Ptr ptr = boost::python::extract<Node::Ptr>(tup[1]);
	if ( ptr.isNull() ) {
		return false;
	}
	result = Sequence(ptr);
	return rflag;
}

bool resolveDefaultCollection(Sequence &result, DynamicContext *context, const QueryPathNode *projection)
{
	boost::python::object obj = this->get_override("resolveDefaultCollection")(boost::python::ptr(context), boost::python::ptr(projection));
	if ( obj.is_none() || ! boost::python::extract<boost::python::tuple>(obj).check() ) {
		return false;
	}
	boost::python::tuple tup = boost::python::extract<boost::python::tuple>(obj);
	if ( boost::python::len(tup) != 2 ) {
		return false;
	}
	if ( ! boost::python::extract<bool>(tup[0]).check() || ! boost::python::extract<Node::Ptr>(tup[1]).check() ) {
		return false;
	}
	bool rflag = boost::python::extract<bool>(tup[0]);
	Node::Ptr ptr = boost::python::extract<Node::Ptr>(tup[1]);
	if ( ptr.isNull() ) {
		return false;
	}
	result = Sequence(ptr);
	return rflag;
}

bool putDocument(const Node::Ptr &document, const XMLCh *uri, DynamicContext *context)
{
	return this->get_override("putDocument")(boost::ref(document), pyxerces::XMLString(uri), boost::python::ptr(context));
}

};

void URIResolver_init(void) {
	//! URIResolver
	boost::python::class_<URIResolverWrapper, boost::noncopyable>("URIResolver")
			.def(URIResolverDefVisitor<char*>())
			.def("resolveDocument", boost::python::pure_virtual(&URIResolver::resolveDocument))
			.def("resolveCollection", boost::python::pure_virtual(&URIResolver::resolveCollection))
			.def("resolveDefaultCollection", boost::python::pure_virtual(&URIResolver::resolveDefaultCollection))
			.def("putDocument", boost::python::pure_virtual(&URIResolver::putDocument))
			;
}

} /* namespace pyxqilla */
