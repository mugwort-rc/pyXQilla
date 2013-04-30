/*
 * Item.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "Item.h"

//! for forward declaration
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/events/EventHandler.hpp>
#include <xercesc/framework/XMLBuffer.hpp>

#include <xqilla/items/Item.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

//! Item
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ItemGenerateEventsOverloads, generateEvents, 2, 4)

void Item_init(void) {
	//! Item
	boost::python::class_<Item, boost::noncopyable>("Item", boost::python::no_init)
			.setattr("gXQilla", pyxerces::XMLChPtr(Item::gXQilla))
			.def("isNode", &Item::isNode)
			.def("isAtomicValue", &Item::isAtomicValue)
			.def("isFunction", &Item::isFunction)
			.def("asString", &Item::asString, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeURI", &Item::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", &Item::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("generateEvents", &Item::generateEvents, ItemGenerateEventsOverloads())
			.def("getInterface", &Item::getInterface, boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
			.def("typeToBuffer", &Item::typeToBuffer)
			;
}

} /* namespace pyxqilla */
