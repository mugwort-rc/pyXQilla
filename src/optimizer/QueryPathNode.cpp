/*
 * QueryPathNode.cpp
 *
 *  Created on: 2013/08/03
 *      Author: mugwort_rc
 */

#include "QueryPathNode.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/axis/NodeTest.hpp>

#include <xqilla/optimizer/QueryPathNode.hpp>

namespace pyxqilla {

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(QueryPathNodeRemoveChild, removeChild, 1, 2)

void QueryPathNode_init(void) {
	//! QueryPathNode
	auto PyQueryPathNode = boost::python::class_<QueryPathNode, boost::noncopyable>("QueryPathNode", boost::python::init<const NodeTest*, QueryPathNode::Type, xercesc::MemoryManager*>())
		.def("getType", &QueryPathNode::getType)
		.def("setType", &QueryPathNode::setType)
		.def("isWildcardURI", &QueryPathNode::isWildcardURI)
		.def("isWildcardName", &QueryPathNode::isWildcardName)
		.def("isWildcardNodeType", &QueryPathNode::isWildcardNodeType)
		.def("isWildcard", &QueryPathNode::isWildcard)
		.def("getURI", &QueryPathNode::getURI, boost::python::return_value_policy<boost::python::return_by_value>())
		.def("getName", &QueryPathNode::getName, boost::python::return_value_policy<boost::python::return_by_value>())
		.def("getNodeTest", &QueryPathNode::getNodeTest, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("getParent", &QueryPathNode::getParent, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("getNextSibling", &QueryPathNode::getNextSibling, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("getPreviousSibling", &QueryPathNode::getPreviousSibling, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("getFirstChild", &QueryPathNode::getFirstChild, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("getLastChild", &QueryPathNode::getLastChild, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("getRoot", &QueryPathNode::getRoot, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("appendChild", &QueryPathNode::appendChild, boost::python::return_value_policy<boost::python::reference_existing_object>())
		.def("removeChild", &QueryPathNode::removeChild, QueryPathNodeRemoveChild())
		.def("stealChildren", &QueryPathNode::stealChildren)
		.def("markSubtreeValue", &QueryPathNode::markSubtreeValue)
		.def("markSubtreeResult", &QueryPathNode::markSubtreeResult)
		.def("toString", &QueryPathNode::toString)
		.def("equals", &QueryPathNode::equals)
		.def("isSubsetOf", &QueryPathNode::isSubsetOf)
		;
	boost::python::scope QueryPathNodeScope = PyQueryPathNode;
	//! QueryPathNode::Type
	boost::python::enum_<QueryPathNode::Type>("Type")
			.value("ATTRIBUTE", QueryPathNode::ATTRIBUTE)
			.value("CHILD", QueryPathNode::CHILD)
			.value("DESCENDANT", QueryPathNode::DESCENDANT)
			.value("DESCENDANT_ATTR", QueryPathNode::DESCENDANT_ATTR)
			.value("ROOT", QueryPathNode::ROOT)
			.export_values()
			;

}

} /* namespace pyxqilla */
