/*
 * DebugListener.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "DebugListener.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/debug/StackFrame.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/exceptions/XQException.hpp>

#include <xqilla/debug/DebugListener.hpp>

namespace pyxqilla {

void DebugListener_init(void) {
	//! DebugListener
	boost::python::class_<DebugListener, boost::noncopyable>("DebugListener", boost::python::no_init)
			.def("start", &DebugListener::start)
			.def("end", &DebugListener::end)
			.def("enter", &DebugListener::enter)
			.def("exit", &DebugListener::exit)
			.def("error", &DebugListener::error)
			.def("doLazyEvaluation", &DebugListener::doLazyEvaluation)
			.def("doFocusOptimizations", &DebugListener::doFocusOptimizations)
			;
}

} /* namespace pyxqilla */
