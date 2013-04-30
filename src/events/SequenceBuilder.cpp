/*
 * SequenceBuilder.cpp
 *
 *  Created on: 2013/02/27
 *      Author: mugwort_rc
 */

#include "SequenceBuilder.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/runtime/Sequence.hpp>

#include <xqilla/events/SequenceBuilder.hpp>

namespace pyxqilla {

void SequenceBuilder_init(void) {
	//! SequenceBuilder
	boost::python::class_<SequenceBuilder, boost::noncopyable>("SequenceBuilder", boost::python::no_init)
			.def("getSequence", &SequenceBuilder::getSequence)
			;
}

} /* namespace pyxqilla */
