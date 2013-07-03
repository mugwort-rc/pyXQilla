/*
 * XPath2MemoryManager.cpp
 *
 *  Created on: 2013/07/03
 *      Author: mugwort_rc
 */

#include "XPath2MemoryManager.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xqilla/context/VariableStore.hpp>
#include <xqilla/context/VariableTypeStore.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/Collation.hpp>
#include <xqilla/context/impl/CollationImpl.hpp>
#include <xqilla/dom-api/XQillaNSResolver.hpp>
#include <xqilla/items/ATDecimalOrDerived.hpp>
#include <xqilla/framework/StringPool.hpp>

#include <xqilla/framework/XPath2MemoryManager.hpp>

namespace pyxqilla {

void XPath2MemoryManager_init(void) {
	//! XPath2MemoryManager
	boost::python::class_<XPath2MemoryManager, boost::noncopyable, boost::python::bases<xercesc::MemoryManager> >("XPath2MemoryManager", boost::python::no_init)
			.def("reset", &XPath2MemoryManager::reset)
			.def("getPooledString", static_cast<const XMLCh*(XPath2MemoryManager::*)(const XMLCh*)>(&XPath2MemoryManager::getPooledString), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getPooledString", static_cast<const XMLCh*(XPath2MemoryManager::*)(const XMLCh*, unsigned int)>(&XPath2MemoryManager::getPooledString), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getPooledString", static_cast<const XMLCh*(XPath2MemoryManager::*)(const char*)>(&XPath2MemoryManager::getPooledString), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("allocate", &XPath2MemoryManager::allocate, boost::python::return_value_policy<boost::python::return_opaque_pointer>()) //!< void*
			.def("deallocate", &XPath2MemoryManager::deallocate)
			.def("createCollation", &XPath2MemoryManager::createCollation, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("createNSResolver", &XPath2MemoryManager::createNSResolver, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("createVariableTypeStore", &XPath2MemoryManager::createVariableTypeStore, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("createInteger", &XPath2MemoryManager::createInteger, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("dumpStatistics", &XPath2MemoryManager::dumpStatistics)
			.def("getAllocatedObjectCount", &XPath2MemoryManager::getAllocatedObjectCount)
			.def("getTotalAllocatedMemory", &XPath2MemoryManager::getTotalAllocatedMemory)
			.def("getStringPool", &XPath2MemoryManager::getStringPool, boost::python::return_value_policy<boost::python::reference_existing_object>())
			;
}

} /* namespace pyxqilla */
