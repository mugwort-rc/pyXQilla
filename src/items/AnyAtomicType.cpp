/*
 * AnyAtomicType.cpp
 *
 *  Created on: 2013/02/26
 *      Author: mugwort_rc
 */

#include "AnyAtomicType.h"

#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/context/StaticContext.hpp>
#include <xqilla/events/EventHandler.hpp>
#include <xercesc/framework/XMLBuffer.hpp>

#include <xqilla/items/AnyAtomicType.hpp>

#include "util/XMLString.h"

namespace pyxqilla {

class AnyAtomicTypeWrapper
: public AnyAtomicType, public boost::python::wrapper<AnyAtomicType>
{
public:
bool isAtomicValue() const {
	if(boost::python::override isAtomicValue = this->get_override("isAtomicValue")){
		return isAtomicValue();
	}else{
		return AnyAtomicType::isAtomicValue();
	}
}

bool isNode() const {
	if(boost::python::override isNode = this->get_override("isNode")){
		return isNode();
	}else{
		return AnyAtomicType::isNode();
	}
}

bool isFunction() const {
	if(boost::python::override isFunction = this->get_override("isFunction")){
		return isFunction();
	}else{
		return AnyAtomicType::isFunction();
	}
}

bool isNumericValue() const {
	if(boost::python::override isNumericValue = this->get_override("isNumericValue")){
		return isNumericValue();
	}else{
		return AnyAtomicType::isNumericValue();
	}
}

bool isDateOrTimeTypeValue() const {
	if(boost::python::override isDateOrTimeTypeValue = this->get_override("isDateOrTimeTypeValue")){
		return isDateOrTimeTypeValue();
	}else{
		return AnyAtomicType::isDateOrTimeTypeValue();
	}
}

const XMLCh* getPrimitiveTypeURI() const {
	if(boost::python::override getPrimitiveTypeURI = this->get_override("getPrimitiveTypeURI")){
		return getPrimitiveTypeURI();
	}else{
		return AnyAtomicType::getPrimitiveTypeURI();
	}
}

const XMLCh* getPrimitiveTypeName() const {
	return this->get_override("getPrimitiveTypeName")();
}

const XMLCh* getTypeURI() const {
	return this->get_override("getTypeURI")();
}

const XMLCh* getTypeName() const {
	return this->get_override("getTypeName")();
}

void generateEvents(EventHandler *events, const DynamicContext *context, bool preserveNS = true, bool preserveType = true) const {
	if(boost::python::override generateEvents = this->get_override("generateEvents")){
		generateEvents(boost::python::ptr(events), boost::python::ptr(context), preserveNS, preserveType);
	}else{
		AnyAtomicType::generateEvents(events, context, preserveNS, preserveType);
	}
}

bool castable(AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) const {
	if(boost::python::override castable = this->get_override("castable")){
		return castable(targetIndex, pyxerces::XMLString(targetURI), pyxerces::XMLString(targetType), boost::python::ptr(context));
	}else{
		return AnyAtomicType::castable(targetIndex, targetURI, targetType, context);
	}
}

const XMLCh* asString(const DynamicContext* context) const {
	return this->get_override("asString")(boost::python::ptr(context));
}

bool equals(const AnyAtomicType::Ptr &target, const DynamicContext* context) const {
	return this->get_override("equals")(boost::ref(target), boost::python::ptr(context));
}

bool isOfType(const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) const {
	if(boost::python::override isOfType = this->get_override("isOfType")){
		return isOfType(pyxerces::XMLString(targetURI), pyxerces::XMLString(targetType), boost::python::ptr(context));
	}else{
		return AnyAtomicType::isOfType(targetURI, targetType, context);
	}
}

bool isInstanceOfType(const XMLCh* targetURI, const XMLCh* targetType, const StaticContext* context) const {
	if(boost::python::override isInstanceOfType = this->get_override("isInstanceOfType")){
		return isInstanceOfType(pyxerces::XMLString(targetURI), pyxerces::XMLString(targetType), boost::python::ptr(context));
	}else{
		return AnyAtomicType::isInstanceOfType(targetURI, targetType, context);
	}
}

void typeToBuffer(DynamicContext *context, XERCES_CPP_NAMESPACE_QUALIFIER XMLBuffer &buffer) const {
	if(boost::python::override typeToBuffer = this->get_override("typeToBuffer")){
		typeToBuffer(boost::python::ptr(context), boost::ref(buffer));
	}else{
		AnyAtomicType::typeToBuffer(context, buffer);
	}
}

AtomicObjectType getPrimitiveTypeIndex() const {
	return this->get_override("getPrimitiveTypeIndex")();
}

};

void AnyAtomicType_init(void) {
	//! AnyAtomicType
	auto PyAnyAtomicType = boost::python::class_<AnyAtomicTypeWrapper, boost::noncopyable, boost::python::bases<Item> >("AnyAtomicType", boost::python::no_init)
			.def("isAtomicValue", &AnyAtomicType::isAtomicValue)
			.def("isNode", &AnyAtomicType::isNode)
			.def("isFunction", &AnyAtomicType::isFunction)
			.def("isNumericValue", &AnyAtomicType::isNumericValue)
			.def("isDateOrTimeTypeValue", &AnyAtomicType::isDateOrTimeTypeValue)
			.def("getPrimitiveTypeURI", &AnyAtomicType::getPrimitiveTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getPrimitiveTypeName", boost::python::pure_virtual(&AnyAtomicType::getPrimitiveTypeName), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeURI", boost::python::pure_virtual(&AnyAtomicType::getTypeURI), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("getTypeName", boost::python::pure_virtual(&AnyAtomicType::getTypeName), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("generateEvents", &AnyAtomicType::generateEvents)
			.def("castAs", static_cast<AnyAtomicType::Ptr(AnyAtomicType::*)(AnyAtomicType::AtomicObjectType, const DynamicContext*) const>(&AnyAtomicType::castAs))
			.def("castAsNoCheck", &AnyAtomicType::castAsNoCheck)
			.def("castAs", static_cast<AnyAtomicType::Ptr(AnyAtomicType::*)(AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*) const>(&AnyAtomicType::castAs))
			.def("castable", &AnyAtomicType::castable)
			.def("asString", boost::python::pure_virtual(&AnyAtomicType::asString), boost::python::return_value_policy<boost::python::return_by_value>())
			.def("equals", boost::python::pure_virtual(&AnyAtomicType::equals))
			.def("isOfType", &AnyAtomicType::isOfType)
			.def("isInstanceOfType", &AnyAtomicType::isInstanceOfType)
			.def("typeToBuffer", &AnyAtomicType::typeToBuffer)
			.def("castIsSupported", &AnyAtomicType::castIsSupported)
			.def("getPrimitiveTypeIndex", boost::python::pure_virtual(&AnyAtomicType::getPrimitiveTypeIndex))
			.setattr("fgDT_ANYATOMICTYPE", pyxerces::XMLChPtr(AnyAtomicType::fgDT_ANYATOMICTYPE))
			;
	boost::python::scope AnyAtomicTypeScope = PyAnyAtomicType;
	//! AnyAtomicType::AtomicObjectType
	boost::python::enum_<AnyAtomicType::AtomicObjectType>("AtomicObjectType")
			.value("ANY_SIMPLE_TYPE", AnyAtomicType::ANY_SIMPLE_TYPE)
			.value("ANY_URI", AnyAtomicType::ANY_URI)
			.value("BASE_64_BINARY", AnyAtomicType::BASE_64_BINARY)
			.value("BOOLEAN", AnyAtomicType::BOOLEAN)
			.value("DATE", AnyAtomicType::DATE)
			.value("DATE_TIME", AnyAtomicType::DATE_TIME)
			.value("DAY_TIME_DURATION", AnyAtomicType::DAY_TIME_DURATION)
			.value("DECIMAL", AnyAtomicType::DECIMAL)
			.value("DOUBLE", AnyAtomicType::DOUBLE)
			.value("DURATION", AnyAtomicType::DURATION)
			.value("FLOAT", AnyAtomicType::FLOAT)
			.value("G_DAY", AnyAtomicType::G_DAY)
			.value("G_MONTH", AnyAtomicType::G_MONTH)
			.value("G_MONTH_DAY", AnyAtomicType::G_MONTH_DAY)
			.value("G_YEAR", AnyAtomicType::G_YEAR)
			.value("G_YEAR_MONTH", AnyAtomicType::G_YEAR_MONTH)
			.value("HEX_BINARY", AnyAtomicType::HEX_BINARY)
			.value("NOTATION", AnyAtomicType::NOTATION)
			.value("QNAME", AnyAtomicType::QNAME)
			.value("STRING", AnyAtomicType::STRING)
			.value("TIME", AnyAtomicType::TIME)
			.value("UNTYPED_ATOMIC", AnyAtomicType::UNTYPED_ATOMIC)
			.value("YEAR_MONTH_DURATION", AnyAtomicType::YEAR_MONTH_DURATION)
			.value("NumAtomicObjectTypes", AnyAtomicType::NumAtomicObjectTypes)
			.export_values()
			;
}

} /* namespace pyxqilla */
