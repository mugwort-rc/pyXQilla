/*
 * NSFixupFilter.cpp
 *
 *  Created on: 2013/07/03
 *      Author: mugwort_rc
 */

#include "NSFixupFilter.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/framework/XPath2MemoryManager.hpp>

#include <xqilla/events/NSFixupFilter.hpp>

namespace pyxqilla {

void NSFixupFilter_init(void) {
	//! NSFixupFilter
	boost::python::class_<NSFixupFilter, boost::noncopyable, boost::python::bases<EventFilter> >("NSFixupFilter", boost::python::init<EventHandler*, XPath2MemoryManager*>())
			.def("startDocumentEvent", &NSFixupFilter::startDocumentEvent)
			.def("endDocumentEvent", &NSFixupFilter::endDocumentEvent)
			.def("startElementEvent", &NSFixupFilter::startElementEvent)
			.def("endElementEvent", &NSFixupFilter::endElementEvent)
			.def("attributeEvent", &NSFixupFilter::attributeEvent)
			.def("namespaceEvent", &NSFixupFilter::namespaceEvent)
			;
}

} /* namespace pyxqilla */
