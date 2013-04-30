/*
 * EmptyResult.cpp
 *
 *  Created on: 2013/04/29
 *      Author: mugwort_rc
 */

#include "EmptyResult.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/runtime/Result.hpp>
#include <xqilla/runtime/ResultBuffer.hpp>

#include <xqilla/runtime/EmptyResult.hpp>

namespace pyxqilla {

class EmptyResultWrapper
: public EmptyResult, public boost::python::wrapper<EmptyResult>
{
public:
EmptyResultWrapper(const LocationInfo* o)
 : EmptyResult(o)
{}

Sequence toSequence(DynamicContext *context) {
	if(boost::python::override toSequence = this->get_override("toSequence")){
		return toSequence(boost::python::ptr(context));
	}else{
		return EmptyResult::toSequence(context);
	}
}

void toResultBuffer(unsigned int readCount, ResultBuffer &buffer) {
	if(boost::python::override toResultBuffer = this->get_override("toResultBuffer")){
		toResultBuffer(readCount, boost::ref(buffer));
	}else{
		EmptyResult::toResultBuffer(readCount, buffer);
	}
}

void skip(unsigned count, DynamicContext *context) {
	if (boost::python::override skip = this->get_override("skip")) {
		skip(count, boost::python::ptr(context));
	}else{
		EmptyResult::skip(count, context);
	}
}

};

void EmptyResult_init(void) {
	//! EmptyResult
	boost::python::class_<EmptyResultWrapper, boost::noncopyable, boost::python::bases<ResultImpl> >("EmptyResult", boost::python::init<const LocationInfo*>())
				.def("next", &EmptyResult::next)
				.def("toSequence", &EmptyResult::toSequence)
				.def("toResultBuffer", &EmptyResult::toResultBuffer)
				.def("skip", &EmptyResult::skip)
				;
}

} /* namespace pyxqilla */
