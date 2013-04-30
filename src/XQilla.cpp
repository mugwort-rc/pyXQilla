/*
 * XQilla.cpp
 *
 *  Created on: 2013/02/18
 *      Author: mugwort_rc
 */

#include <Python.h>
#include <boost/python.hpp>
#define BOOST_PYTHON_STATIC_LIB

// ast
#include "ast/LocationInfo.h"

// context
#include "context/DynamicContext.h"
#include "context/RegexGroupStore.h"

// debug
#include "debug/DebugListener.h"
#include "debug/StackFrame.h"

// events
#include "events/SequenceBuilder.h"

// exceptions
#include "exceptions/XQillaException.h"

// framework
#include "framework/ReferenceCounted.h"

// items
#include "items/AnyAtomicType.h"
#include "items/ATBooleanOrDerived.h"
#include "items/ATDecimalOrDerived.h"
#include "items/ATDurationOrDerived.h"
#include "items/ATQNameOrDerived.h"
#include "items/Item.h"
#include "items/Node.h"
#include "items/Numeric.h"

// runtime
#include "runtime/EmptyResult.h"
#include "runtime/Result.h"
#include "runtime/ResultImpl.h"
#include "runtime/Sequence.h"

// simple-api
#include "simple-api/XQilla.h"
#include "simple-api/XQQuery.h"

// utils
#include "utils/XQillaPlatformUtils.h"

BOOST_PYTHON_MODULE(__XQilla)
{
	// ==================================================
	// bases
	// --------------------------------------------------
	// ast
	pyxqilla::LocationInfo_init();
	// items
	pyxqilla::Item_init();

	// inherited (depth:2) classes
	// items
	pyxqilla::AnyAtomicType_init();
	// runtime
	pyxqilla::ResultImpl_init();

	// inherited (depth:3) classes
	// items
	pyxqilla::Numeric_init();

	// ==================================================
	// context
	// --------------------------------------------------
	pyxqilla::DynamicContext_init();
	pyxqilla::RegexGroupStore_init();

	// ==================================================
	// debug
	// --------------------------------------------------
	pyxqilla::DebugListener_init();
	pyxqilla::StackFrame_init();

	// ==================================================
	// events
	// --------------------------------------------------
	pyxqilla::SequenceBuilder_init();

	// ==================================================
	// exceptions
	// --------------------------------------------------
	pyxqilla::XQillaException_init();

	// ==================================================
	// framework
	// --------------------------------------------------
	pyxqilla::ReferenceCounted_init();

	// ==================================================
	// items
	// --------------------------------------------------
	pyxqilla::ATBooleanOrDerived_init();
	pyxqilla::ATDecimalOrDerived_init();
	pyxqilla::ATDurationOrDerived_init();
	pyxqilla::ATQNameOrDerived_init();
	pyxqilla::Node_init();

	// ==================================================
	// runtime
	// --------------------------------------------------
	pyxqilla::EmptyResult_init();
	pyxqilla::Result_init();
	pyxqilla::Sequence_init();

	// ==================================================
	// simple-api
	// --------------------------------------------------
	pyxqilla::XQilla_init();
	pyxqilla::XQQuery_init();

	// ==================================================
	// utils
	// --------------------------------------------------
	pyxqilla::XQillaPlatformUtils_init();
}

