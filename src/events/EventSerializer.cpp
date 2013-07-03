/*
 * EventSerializer.cpp
 *
 *  Created on: 2013/07/03
 *      Author: mugwort_rc
 */

#include "EventSerializer.h"

#include <boost/python.hpp>

#include <xqilla/events/EventSerializer.hpp>

namespace pyxqilla {

void EventSerializer_init(void) {
	//! EventSerializer
	boost::python::class_<EventSerializer, boost::noncopyable, boost::python::bases<EventHandler> >("EventSerializer", boost::python::init<const char*, const char*, xercesc::XMLFormatTarget*, boost::python::optional<xercesc::MemoryManager*> >())
			.def(boost::python::init<xercesc::XMLFormatTarget*, boost::python::optional<xercesc::MemoryManager*> >())
			.def("setLocationInfo", &EventSerializer::setLocationInfo)
			.def("startDocumentEvent", &EventSerializer::startDocumentEvent)
			.def("endDocumentEvent", &EventSerializer::endDocumentEvent)
			.def("startElementEvent", &EventSerializer::startElementEvent)
			.def("endElementEvent", &EventSerializer::endElementEvent)
			.def("piEvent", &EventSerializer::piEvent)
			.def("textEvent", static_cast<void(EventSerializer::*)(const XMLCh*)>(&EventSerializer::textEvent))
			.def("textEvent", static_cast<void(EventSerializer::*)(const XMLCh*, unsigned int)>(&EventSerializer::textEvent))
			.def("commentEvent", &EventSerializer::commentEvent)
			.def("attributeEvent", &EventSerializer::attributeEvent)
			.def("namespaceEvent", &EventSerializer::namespaceEvent)
			.def("atomicItemEvent", &EventSerializer::atomicItemEvent)
			.def("endEvent", &EventSerializer::endEvent)
			.def("addNewlines", &EventSerializer::addNewlines)
			.def("useSelfClosingElement", &EventSerializer::useSelfClosingElement)
			.def("addXMLDeclarations", &EventSerializer::addXMLDeclarations)
			;
}

} /* namespace pyxqilla */
