/*
 * Sequence.cpp
 *
 *  Created on: 2013/02/27
 *      Author: mugwort_rc
 */

#include "Sequence.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/Collation.hpp>

#include <xqilla/runtime/Sequence.hpp>

namespace pyxqilla {

void Sequence_init(void) {
	//! Sequence
	boost::python::class_<Sequence>("Sequence", boost::python::init<const Item::Ptr&, boost::python::optional<xercesc::MemoryManager*> >())
			.def(boost::python::init<boost::python::optional<xercesc::MemoryManager*> >())
			.def(boost::python::init<size_t, boost::python::optional<xercesc::MemoryManager*> >())
			.def(boost::python::init<const Sequence&, size_t, boost::python::optional<xercesc::MemoryManager*> >())
			.def(boost::python::init<const Sequence&, xercesc::MemoryManager*>())
			.def("clear", &Sequence::clear)
			.def("first", &Sequence::first, boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("second", &Sequence::second, boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("__iter__", boost::python::iterator<VectorOfItems>())
			.def("getLength", &Sequence::getLength)
			.def("item", static_cast<const Item::Ptr&(Sequence::*)(size_t) const>(&Sequence::item), boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("item", static_cast<const Item::Ptr&(Sequence::*)(const ATDecimalOrDerived::Ptr&) const>(&Sequence::item), boost::python::return_value_policy<boost::python::copy_const_reference>())
			.def("addItem", &Sequence::addItem)
			.def("addItemFront", &Sequence::addItemFront)
			.def("joinSequence", &Sequence::joinSequence)
			.def("isEmpty", &Sequence::isEmpty)
			.def("sortIntoDocumentOrder", &Sequence::sortIntoDocumentOrder)
			.def("sortWithCollation", &Sequence::sortWithCollation)
			;
}

} /* namespace pyxqilla */
