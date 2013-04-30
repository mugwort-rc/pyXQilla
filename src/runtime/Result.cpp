/*
 * Result.cpp
 *
 *  Created on: 2013/04/29
 *      Author: mugwort_rc
 */

#include "Result.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/schema/SequenceType.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/ast/StaticType.hpp>
#include <xqilla/runtime/ResultBuffer.hpp>

#include <xqilla/runtime/Result.hpp>

namespace pyxqilla {

class ResultDefVisitor
 : public boost::python::def_visitor<ResultDefVisitor>
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	//! ResultImpl
	.def("getResultPointer", &ResultDefVisitor::getResultPointer, boost::python::return_value_policy<boost::python::reference_existing_object>())
	.def("setResultPointer", &ResultDefVisitor::setResultPointer)
	.def("next", &ResultDefVisitor::next)
	.def("nextOrTail", &ResultDefVisitor::nextOrTail)
	.def("toSequence", &ResultDefVisitor::toSequence)
	.def("toResultBuffer", &ResultDefVisitor::toResultBuffer)
	.def("skip", &ResultDefVisitor::skip)
	//! LocationInfo
	.def("getFile", &ResultDefVisitor::getFile, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getLine", &ResultDefVisitor::getLine)
	.def("getColumn", &ResultDefVisitor::getColumn)
	;
}

//! ----- ResultImpl -----

static Result* getResultPointer(Result& self) {
	return self->getResultPointer();
}

static void setResultPointer(Result& self, Result* p) {
	self->setResultPointer(p);
}

static Item::Ptr next(Result& self, DynamicContext* context) {
	return self->next(context);
}

static Item::Ptr nextOrTail(Result& self, Result& tail, DynamicContext* context) {
	return self->nextOrTail(tail, context);
}

static Sequence toSequence(Result& self, DynamicContext* context) {
	return self->toSequence(context);
}

static void toResultBuffer(Result& self, unsigned int readCount, ResultBuffer& buffer) {
	self->toResultBuffer(readCount, buffer);
}

static void skip(Result& self, unsigned count, DynamicContext* context) {
	self->skip(count, context);
}

//! ----- LocationInfo -----
static const XMLCh* getFile(Result& self) {
	return self->getFile();
}

static unsigned int getLine(Result& self) {
	return self->getLine();
}

static unsigned int getColumn(Result& self) {
	return self->getColumn();
}

};

void Result_init(void) {
	//! Result
	boost::python::class_<Result>("Result", boost::python::init<const Item::Ptr&>())
			.def(boost::python::init<const Sequence&>())
			.def(boost::python::init<ResultImpl*>())
			.def(ResultDefVisitor())
			.def("get", static_cast<ResultImpl*(Result::*)()>(&Result::get), boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("isNull", &Result::isNull)
			.def("getEmpty", &Result::getEmpty, boost::python::return_value_policy<boost::python::reference_existing_object>())
			;
}

} /* namespace pyxqilla */
