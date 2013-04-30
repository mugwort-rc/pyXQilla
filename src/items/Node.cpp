/*
 * Node.cpp
 *
 *  Created on: 2013/02/27
 *      Author: mugwort_rc
 */

#include "Node.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/runtime/Result.hpp>
#include <xqilla/axis/NodeTest.hpp>

#include <xqilla/items/Node.hpp>

#include "util/XMLString.h"

namespace pyxqilla {

void Node_init(void) {
	//! Node
	boost::python::class_<Node, boost::noncopyable, boost::python::bases<Item> >("Node", boost::python::no_init)
			.def("isNode", &Node::isNode)
			.def("isAtomicValue", &Node::isAtomicValue)
			.def("isFunction", &Node::isFunction)
			.def("typeToBuffer", &Node::typeToBuffer)
			.def("asString", &Node::asString, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("hasInstanceOfType", &Node::hasInstanceOfType)
			.def("dmBaseURI", &Node::dmBaseURI)
			.def("dmNodeKind", &Node::dmNodeKind, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("dmNodeName", &Node::dmNodeName)
			.def("dmStringValue", &Node::dmStringValue, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("dmTypedValue", &Node::dmTypedValue)
			.def("dmDocumentURI", &Node::dmDocumentURI)
			.def("dmTypeName", &Node::dmTypeName)
			.def("dmNilled", &Node::dmNilled)
			.def("lessThan", &Node::lessThan)
			.def("equals", &Node::equals)
			.def("uniqueLessThan", &Node::uniqueLessThan)
			.def("root", &Node::root)
			.def("dmParent", &Node::dmParent)
			.def("dmAttributes", &Node::dmAttributes)
			.def("dmNamespaceNodes", &Node::dmNamespaceNodes)
			.def("dmChildren", &Node::dmChildren)
			.def("getAxisResult", &Node::getAxisResult)
			.def("dmIsId", &Node::dmIsId)
			.def("dmIsIdRefs", &Node::dmIsIdRefs)
			.def("getTypeURI", &Node::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", &Node::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.setattr("document_string", pyxerces::XMLChPtr(Node::document_string))
			.setattr("element_string", pyxerces::XMLChPtr(Node::element_string))
			.setattr("attribute_string", pyxerces::XMLChPtr(Node::attribute_string))
			.setattr("text_string", pyxerces::XMLChPtr(Node::text_string))
			.setattr("processing_instruction_string", pyxerces::XMLChPtr(Node::processing_instruction_string))
			.setattr("comment_string", pyxerces::XMLChPtr(Node::comment_string))
			.setattr("namespace_string", pyxerces::XMLChPtr(Node::namespace_string))
			;
}

} /* namespace pyxqilla */
