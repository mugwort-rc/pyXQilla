/*
 * StackFrame.cpp
 *
 *  Created on: 2013/02/27
 *      Author: mugwort_rc
 */

#include "StackFrame.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/ast/ASTNode.hpp>
#include <xqilla/ast/TupleNode.hpp>
#include <xqilla/ast/LocationInfo.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/events/EventHandler.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/context/VariableStore.hpp>

#include <xqilla/debug/StackFrame.hpp>

namespace pyxqilla {

void StackFrame_init(void) {
	//! StackFrame
	boost::python::class_<StackFrame, boost::noncopyable>("StackFrame", boost::python::no_init)
			.def("getLocationInfo", &StackFrame::getLocationInfo, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			.def("getPreviousFrame", &StackFrame::getPreviousFrame, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("query", static_cast<Sequence(StackFrame::*)(const XMLCh*) const>(&StackFrame::query))
			.def("query", static_cast<void(StackFrame::*)(const XMLCh*, EventHandler*) const>(&StackFrame::query))
			// TODO: ASTNode
			.def("getASTNode", &StackFrame::getASTNode, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			// TODO: TupleNode
			.def("getTupleNode", &StackFrame::getTupleNode, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
			.def("getQueryPlan", &StackFrame::getQueryPlan)
			;
}

} /* namespace pyxqilla */
