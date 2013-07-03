/*
 * EventHandler.cpp
 *
 *  Created on: 2013/07/03
 *      Author: mugwort_rc
 */

#include "EventHandler.h"

#include <boost/python.hpp>

#include <xqilla/events/EventHandler.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

class EventHandlerWrapper
: public EventHandler, public boost::python::wrapper<EventHandler>
{
public:
EventHandlerWrapper()
{}

~EventHandlerWrapper()
{}

void setLocationInfo(const LocationInfo *location) {
	if ( boost::python::override setLocationInfo = this->get_override("setLocationInfo") ) {
		setLocationInfo(boost::python::ptr(location));
	} else {
		EventHandler::setLocationInfo(location);
	}
}

void startDocumentEvent(const XMLCh *documentURI, const XMLCh *encoding) {
	this->get_override("startDocumentEvent")(pyxerces::XMLString(documentURI), pyxerces::XMLString(encoding));
}

virtual void endDocumentEvent() {
	this->get_override("endDocumentEvent")();
}

void startElementEvent(const XMLCh *prefix, const XMLCh *uri, const XMLCh *localname) {
	this->get_override("startElementEvent")(pyxerces::XMLString(prefix), pyxerces::XMLString(uri), pyxerces::XMLString(localname));
}

void endElementEvent(const XMLCh *prefix, const XMLCh *uri, const XMLCh *localname, const XMLCh *typeURI, const XMLCh *typeName) {
	this->get_override("endElementEvent")(pyxerces::XMLString(prefix), pyxerces::XMLString(uri), pyxerces::XMLString(localname), pyxerces::XMLString(typeURI), pyxerces::XMLString(typeName));
}

void piEvent(const XMLCh *target, const XMLCh *value) {
	this->get_override("piEvent")(pyxerces::XMLString(target), pyxerces::XMLString(value));
}

void textEvent(const XMLCh *value) {
	this->get_override("textEvent")(pyxerces::XMLString(value));
}

void textEvent(const XMLCh *chars, unsigned int length) {
	this->get_override("textEvent")(pyxerces::XMLString(chars), length);
}

void commentEvent(const XMLCh *value) {
	this->get_override("commentEvent")(pyxerces::XMLString(value));
}

void attributeEvent(const XMLCh *prefix, const XMLCh *uri, const XMLCh *localname, const XMLCh *value, const XMLCh *typeURI, const XMLCh *typeName) {
	this->get_override("attributeEvent")(pyxerces::XMLString(prefix), pyxerces::XMLString(uri), pyxerces::XMLString(localname), pyxerces::XMLString(value), pyxerces::XMLString(typeURI), pyxerces::XMLString(typeName));
}

void namespaceEvent(const XMLCh *prefix, const XMLCh *uri) {
	this->get_override("namespaceEvent")(pyxerces::XMLString(prefix), pyxerces::XMLString(uri));
}

void atomicItemEvent(AnyAtomicType::AtomicObjectType type, const XMLCh *value, const XMLCh *typeURI, const XMLCh *typeName) {
	if ( boost::python::override atomicItemEvent = this->get_override("atomicItemEvent") ) {
		atomicItemEvent(type, pyxerces::XMLString(value), pyxerces::XMLString(typeURI), pyxerces::XMLString(typeName));
	} else {
		EventHandler::atomicItemEvent(type, value, typeURI, typeName);
	}
}

void endEvent() {
	this->get_override("endEvent")();
}

};

void EventHandler_init(void) {
	//! EventHandler
	boost::python::class_<EventHandlerWrapper, boost::noncopyable>("EventHandler")
			.def("setLocationInfo", &EventHandler::setLocationInfo)
			.def("startDocumentEvent", boost::python::pure_virtual(&EventHandler::startDocumentEvent))
			.def("endDocumentEvent", boost::python::pure_virtual(&EventHandler::endDocumentEvent))
			.def("startElementEvent", boost::python::pure_virtual(&EventHandler::startElementEvent))
			.def("endElementEvent", boost::python::pure_virtual(&EventHandler::endElementEvent))
			.def("piEvent", boost::python::pure_virtual(&EventHandler::piEvent))
			.def("textEvent", boost::python::pure_virtual(static_cast<void(EventHandler::*)(const XMLCh*)>(&EventHandler::textEvent)))
			.def("textEvent", boost::python::pure_virtual(static_cast<void(EventHandler::*)(const XMLCh*, unsigned int)>(&EventHandler::textEvent)))
			.def("commentEvent", boost::python::pure_virtual(&EventHandler::commentEvent))
			.def("attributeEvent", boost::python::pure_virtual(&EventHandler::attributeEvent))
			.def("namespaceEvent", boost::python::pure_virtual(&EventHandler::namespaceEvent))
			.def("atomicItemEvent", &EventHandler::atomicItemEvent)
			.def("endEvent", boost::python::pure_virtual(&EventHandler::endEvent))
			;
	//! EventFilter
	boost::python::class_<EventFilter, boost::noncopyable, boost::python::bases<EventHandler> >("EventFilter", boost::python::init<EventHandler*>())
			.def("setNextEventHandler", &EventFilter::setNextEventHandler)
			.def("setLocationInfo", &EventFilter::setLocationInfo)
			.def("startDocumentEvent", &EventFilter::startDocumentEvent)
			.def("endDocumentEvent", &EventFilter::endDocumentEvent)
			.def("startElementEvent", &EventFilter::startElementEvent)
			.def("endElementEvent", &EventFilter::endElementEvent)
			.def("piEvent", &EventFilter::piEvent)
			.def("textEvent", static_cast<void(EventFilter::*)(const XMLCh*)>(&EventFilter::textEvent))
			.def("textEvent", static_cast<void(EventFilter::*)(const XMLCh*, unsigned int)>(&EventFilter::textEvent))
			.def("commentEvent", &EventFilter::commentEvent)
			.def("attributeEvent", &EventFilter::attributeEvent)
			.def("namespaceEvent", &EventFilter::namespaceEvent)
			.def("atomicItemEvent", &EventFilter::atomicItemEvent)
			.def("endEvent", &EventFilter::endEvent)
			;
}


} /* namespace pyxqilla */
