/*
 * LocationInfo.cpp
 *
 *  Created on: 2013/04/29
 *      Author: mugwort_rc
 */

#include "LocationInfo.h"

#include <boost/python.hpp>

#include <xqilla/ast/LocationInfo.hpp>

#include "../common/XMLString.h"

namespace pyxqilla {

template <class STR>
class LocationInfoDefVisitor
 : public boost::python::def_visitor<LocationInfoDefVisitor<STR> >
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def("setLocationInfo", &LocationInfoDefVisitor::setLocationInfo)
	;
}

static void setLocationInfo(LocationInfo& self, const STR& file, unsigned int line, unsigned int column) {
	pyxerces::XMLString buff(file);
	self.setLocationInfo(buff.ptr(), line, column);
}

};

void LocationInfo_init(void) {
	//! LocationInfo
	boost::python::class_<LocationInfo, boost::noncopyable>("LocationInfo")
			.def(boost::python::init<const XMLCh*, unsigned int, unsigned int>())
			.def(LocationInfoDefVisitor<std::string>())
			.def("getFile", &LocationInfo::getFile, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getLine", &LocationInfo::getLine)
			.def("getColumn", &LocationInfo::getColumn)
			.def("setLocationInfo", static_cast<void(LocationInfo::*)(const XMLCh*, unsigned int, unsigned int)>(&LocationInfo::setLocationInfo))
			.def("setLocationInfo", static_cast<void(LocationInfo::*)(const LocationInfo*)>(&LocationInfo::setLocationInfo))
			;
}

} /* namespace pyxqilla */
