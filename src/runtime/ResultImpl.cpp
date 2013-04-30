/*
 * ResultImpl.cpp
 *
 *  Created on: 2013/04/29
 *      Author: mugwort_rc
 */

#include "ResultImpl.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/runtime/Result.hpp>
#include <xqilla/runtime/ResultBuffer.hpp>

#include <xqilla/runtime/ResultImpl.hpp>

namespace pyxqilla {

class ResultImplWrapper
: public ResultImpl, public boost::python::wrapper<ResultImpl>
{
public:
Item::Ptr next(DynamicContext *context) {
	if(boost::python::override next = this->get_override("next")){
		return next(boost::python::ptr(context));
	}else{
		return ResultImpl::next(context);
	}
}

Item::Ptr nextOrTail(Result &tail, DynamicContext *context) {
	if (boost::python::override nextOrTail = this->get_override("nextOrTail")) {
		return nextOrTail(boost::ref(tail), boost::python::ptr(context));
	}else{
		return ResultImpl::nextOrTail(tail, context);
	}
}

Sequence toSequence(DynamicContext *context) {
	if(boost::python::override toSequence = this->get_override("toSequence")){
		return toSequence(boost::python::ptr(context));
	}else{
		return ResultImpl::toSequence(context);
	}
}

void toResultBuffer(unsigned int readCount, ResultBuffer &buffer) {
	if(boost::python::override toResultBuffer = this->get_override("toResultBuffer")){
		toResultBuffer(readCount, boost::ref(buffer));
	}else{
		ResultImpl::toResultBuffer(readCount, buffer);
	}
}

void skip(unsigned count, DynamicContext *context) {
	if (boost::python::override skip = this->get_override("skip")) {
		skip(count, boost::python::ptr(context));
	}else{
		ResultImpl::skip(count, context);
	}
}

};

void ResultImpl_init(void) {
	//! ResultImpl
	boost::python::class_<ResultImplWrapper, boost::noncopyable, boost::python::bases<LocationInfo> >("ResultImpl", boost::python::no_init)
			.def("getResultPointer", &ResultImpl::getResultPointer, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("setResultPointer", &ResultImpl::setResultPointer)
			.def("next", &ResultImpl::next)
			.def("nextOrTail", &ResultImpl::nextOrTail)
			.def("toSequence", &ResultImpl::toSequence)
			.def("toResultBuffer", &ResultImpl::toResultBuffer)
			.def("skip", &ResultImpl::skip)
			;
}

} /* namespace pyxqilla */
