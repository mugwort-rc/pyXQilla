/*
 * RegexGroupStore.cpp
 *
 *  Created on: 2013/02/27
 *      Author: mugwort_rc
 */

#include "RegexGroupStore.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/runtime/Result.hpp>

#include <xqilla/context/RegexGroupStore.hpp>

namespace pyxqilla {

void RegexGroupStore_init(void) {
	//! RegexGroupStore
	boost::python::class_<RegexGroupStore, boost::noncopyable>("RegexGroupStore", boost::python::no_init)
			.def("getGroup", &RegexGroupStore::getGroup, boost::python::return_value_policy<boost::python::return_by_value>())
			;
}

} /* namespace pyxqilla */
