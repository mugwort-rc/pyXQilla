/*
 * ReferenceCounted.cpp
 *
 *  Created on: 2013/04/29
 *      Author: mugwort_rc
 */

#include "ReferenceCounted.h"

#include <string>
#include <boost/mpl/string.hpp>
#include <boost/python.hpp>

//! for forward declaration
#include <xqilla/framework/XPath2MemoryManager.hpp>
#include <xqilla/context/DynamicContext.hpp>
#include <xqilla/events/EventHandler.hpp>
#include <xercesc/framework/XMLBuffer.hpp>
#include <xqilla/context/StaticContext.hpp>
#include <xqilla/runtime/Sequence.hpp>
#include <xqilla/runtime/Result.hpp>
#include <xqilla/axis/NodeTest.hpp>

#include <xqilla/items/AnyAtomicType.hpp>
#include <xqilla/items/ATBooleanOrDerived.hpp>
#include <xqilla/items/ATQNameOrDerived.hpp>
#include <xqilla/items/Item.hpp>
#include <xqilla/items/Node.hpp>

#include <xqilla/framework/ReferenceCounted.hpp>

#include "../common/XMLString.h"

//! for Node special case
#include <xqilla/xerces/XercesConfiguration.hpp>
#include <xercesc/dom/DOMNode.hpp>

namespace pyxqilla {

template <typename NAME, class T, class D>
void makeRefCountPointer() {
	char pyName[15 + BOOST_MPL_LIMIT_STRING_SIZE + 1] = "RefCountPointer";
	//! RefCountPointer
	boost::python::class_<RefCountPointer<T> >(strcat(pyName, boost::mpl::c_str<NAME>::value), boost::python::init<boost::python::optional<T*> >())
			.def(D())
			.def("get", &RefCountPointer<T>::get, boost::python::return_value_policy<boost::python::reference_existing_object>())
			.def("isNull", &RefCountPointer<T>::isNull)
			.def("notNull", &RefCountPointer<T>::notNull)
			;
}

template <class X>
class RefCountPointerItemBasedCastDefVisitor
: public boost::python::def_visitor<RefCountPointerItemBasedCastDefVisitor<X> >
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def("toItem", &RefCountPointerItemBasedCastDefVisitor::toItem)
	.def("toAtomicValue", &RefCountPointerItemBasedCastDefVisitor::toAtomicValue)
	.def("toFunction", &RefCountPointerItemBasedCastDefVisitor::toFunction)
	.def("toNode", &RefCountPointerItemBasedCastDefVisitor::toNode)
	;
}

static Item::Ptr toItem(RefCountPointer<const X>& self) {
	return Item::Ptr(self);
}

static AnyAtomicType::Ptr toAtomicValue(RefCountPointer<const X>& self) {
	if ( ! self->isAtomicValue() ) {
		return AnyAtomicType::Ptr(nullptr);
	}
	return AnyAtomicType::Ptr(self);
}

static FunctionRef::Ptr toFunction(RefCountPointer<const X>& self) {
	if ( ! self->isFunction() ) {
		return FunctionRef::Ptr(nullptr);
	}
	return FunctionRef::Ptr(self);
}

static Node::Ptr toNode(RefCountPointer<const X>& self) {
	if ( ! self->isNode() ) {
		return Node::Ptr(nullptr);
	}
	return Node::Ptr(self);
}

};

// =================================================
// const Item
class RefCountPointerConstItemDefVisitor
 : public boost::python::def_visitor<RefCountPointerConstItemDefVisitor>
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def(RefCountPointerItemBasedCastDefVisitor<Item>())
	.def("isNode", &RefCountPointerConstItemDefVisitor::isNode)
	.def("isAtomicValue", &RefCountPointerConstItemDefVisitor::isAtomicValue)
	.def("isFunction", &RefCountPointerConstItemDefVisitor::isFunction)
	.def("asString", &RefCountPointerConstItemDefVisitor::asString, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeURI", &RefCountPointerConstItemDefVisitor::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeName", &RefCountPointerConstItemDefVisitor::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const Item>&, EventHandler* events, const DynamicContext*, bool, bool)>(&RefCountPointerConstItemDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const Item>&, EventHandler* events, const DynamicContext*, bool)>(&RefCountPointerConstItemDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const Item>&, EventHandler* events, const DynamicContext*)>(&RefCountPointerConstItemDefVisitor::generateEvents))
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const Item>&, const XMLCh*)>(&RefCountPointerConstItemDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const Item>&, const char*)>(&RefCountPointerConstItemDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	.def("typeToBuffer", &RefCountPointerConstItemDefVisitor::typeToBuffer)
	;
}

static bool isNode(RefCountPointer<const Item>& self) {
	return self->isNode();
}

static bool isAtomicValue(RefCountPointer<const Item>& self) {
	return self->isAtomicValue();
}

static bool isFunction(RefCountPointer<const Item>& self) {
	return self->isFunction();
}

static const XMLCh* asString(RefCountPointer<const Item>& self, const DynamicContext* context) {
	return self->asString(context);
}

static const XMLCh* getTypeURI(RefCountPointer<const Item>& self) {
	return self->getTypeURI();
}

static const XMLCh* getTypeName(RefCountPointer<const Item>& self) {
	return self->getTypeName();
}

static void generateEvents(RefCountPointer<const Item>& self, EventHandler *events, const DynamicContext *context, bool preserveNS, bool preserveType) {
	self->generateEvents(events, context, preserveNS, preserveType);
}

static void generateEvents(RefCountPointer<const Item>& self, EventHandler *events, const DynamicContext *context, bool preserveNS) {
	self->generateEvents(events, context, preserveNS, true);
}

static void generateEvents(RefCountPointer<const Item>& self, EventHandler *events, const DynamicContext *context) {
	self->generateEvents(events, context, true);
}

static void* getInterface(RefCountPointer<const Item>& self, const XMLCh* name) {
	return self->getInterface(name);
}

static void* getInterface(RefCountPointer<const Item>& self, const char* name) {
	pyxerces::XMLString buff(name);
	return self->getInterface(buff.ptr());
}

static void typeToBuffer(RefCountPointer<const Item>& self, DynamicContext *context, xercesc::XMLBuffer &buffer) {
	self->typeToBuffer(context, buffer);
}

};

// =================================================
// const AnyAtomicType
class RefCountPointerConstAnyAtomicTypeDefVisitor
 : public boost::python::def_visitor<RefCountPointerConstAnyAtomicTypeDefVisitor>
{
friend class def_visitor_access;
public:
template<class T>
void visit(T& class_) const {
	class_
	//! AnyAtomicType
	.def(RefCountPointerItemBasedCastDefVisitor<AnyAtomicType>())
	.def("isAtomicValue", &RefCountPointerConstAnyAtomicTypeDefVisitor::isAtomicValue)
	.def("isNode", &RefCountPointerConstAnyAtomicTypeDefVisitor::isNode)
	.def("isFunction", &RefCountPointerConstAnyAtomicTypeDefVisitor::isFunction)
	.def("isNumericValue", &RefCountPointerConstAnyAtomicTypeDefVisitor::isNumericValue)
	.def("isDateOrTimeTypeValue", &RefCountPointerConstAnyAtomicTypeDefVisitor::isDateOrTimeTypeValue)
	.def("getPrimitiveTypeURI", &RefCountPointerConstAnyAtomicTypeDefVisitor::getPrimitiveTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getPrimitiveTypeName", &RefCountPointerConstAnyAtomicTypeDefVisitor::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeURI", &RefCountPointerConstAnyAtomicTypeDefVisitor::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeName", &RefCountPointerConstAnyAtomicTypeDefVisitor::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const AnyAtomicType>&, EventHandler* events, const DynamicContext*, bool, bool)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const AnyAtomicType>&, EventHandler* events, const DynamicContext*, bool)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const AnyAtomicType>&, EventHandler* events, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::generateEvents))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const AnyAtomicType>&, AnyAtomicType::AtomicObjectType, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::castAs))
	.def("castAsNoCheck", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const AnyAtomicType>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::castAsNoCheck))
	.def("castAsNoCheck", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const AnyAtomicType>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::castAsNoCheck))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const AnyAtomicType>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::castAs))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const AnyAtomicType>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::castAs))
	.def("castable", static_cast<bool(*)(RefCountPointer<const AnyAtomicType>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::castable))
	.def("castable", static_cast<bool(*)(RefCountPointer<const AnyAtomicType>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::castable))
	.def("asString", &RefCountPointerConstAnyAtomicTypeDefVisitor::asString, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("equals", &RefCountPointerConstAnyAtomicTypeDefVisitor::equals)
	.def("isOfType", static_cast<bool(*)(RefCountPointer<const AnyAtomicType>&, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::isOfType))
	.def("isOfType", static_cast<bool(*)(RefCountPointer<const AnyAtomicType>&, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::isOfType))
	.def("isInstanceOfType", static_cast<bool(*)(RefCountPointer<const AnyAtomicType>&, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::isInstanceOfType))
	.def("isInstanceOfType", static_cast<bool(*)(RefCountPointer<const AnyAtomicType>&, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::isInstanceOfType))
	.def("typeToBuffer", &RefCountPointerConstAnyAtomicTypeDefVisitor::typeToBuffer)
	.def("castIsSupported", &RefCountPointerConstAnyAtomicTypeDefVisitor::castIsSupported)
	.def("getPrimitiveTypeIndex", &RefCountPointerConstAnyAtomicTypeDefVisitor::getPrimitiveTypeIndex)
	//! Item
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const AnyAtomicType>&, const XMLCh*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const AnyAtomicType>&, const char*)>(&RefCountPointerConstAnyAtomicTypeDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	;
}

//! AnyAtomicType
static bool isAtomicValue(RefCountPointer<const AnyAtomicType>& self) {
	return self->isAtomicValue();
}

static bool isNode(RefCountPointer<const AnyAtomicType>& self) {
	return self->isNode();
}

static bool isFunction(RefCountPointer<const AnyAtomicType>& self) {
	return self->isFunction();
}

static bool isNumericValue(RefCountPointer<const AnyAtomicType>& self) {
	return self->isNumericValue();
}

static bool isDateOrTimeTypeValue(RefCountPointer<const AnyAtomicType>& self) {
	return self->isDateOrTimeTypeValue();
}

static const XMLCh* getPrimitiveTypeURI(RefCountPointer<const AnyAtomicType>& self) {
	return self->getPrimitiveTypeURI();
}

static const XMLCh* getPrimitiveTypeName(RefCountPointer<const AnyAtomicType>& self) {
	return self->getPrimitiveTypeName();
}

static const XMLCh* getTypeURI(RefCountPointer<const AnyAtomicType>& self) {
	return self->getTypeURI();
}

static const XMLCh* getTypeName(RefCountPointer<const AnyAtomicType>& self) {
	return self->getTypeName();
}

static void generateEvents(RefCountPointer<const AnyAtomicType>& self, EventHandler *events, const DynamicContext *context, bool preserveNS, bool preserveType) {
	self->generateEvents(events, context, preserveNS, preserveType);
}

static void generateEvents(RefCountPointer<const AnyAtomicType>& self, EventHandler *events, const DynamicContext *context, bool preserveNS) {
	self->generateEvents(events, context, preserveNS, true);
}

static void generateEvents(RefCountPointer<const AnyAtomicType>& self, EventHandler *events, const DynamicContext *context) {
	self->generateEvents(events, context, true);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const DynamicContext* context) {
	return self->castAs(targetIndex, context);
}

static AnyAtomicType::Ptr castAsNoCheck(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castAsNoCheck(targetIndex, targetURI, targetType, context);
}

static AnyAtomicType::Ptr castAsNoCheck(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castAsNoCheck(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castAs(targetIndex, targetURI, targetType, context);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castAs(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static bool castable(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castable(targetIndex, targetURI, targetType, context);
}

static bool castable(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castable(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static const XMLCh* asString(RefCountPointer<const AnyAtomicType>& self, const DynamicContext* context) {
	return self->asString(context);
}

static bool equals(RefCountPointer<const AnyAtomicType>& self, const AnyAtomicType::Ptr &target, const DynamicContext* context) {
	return self->equals(target, context);
}

static bool isOfType(RefCountPointer<const AnyAtomicType>& self, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->isOfType(targetURI, targetType, context);
}

static bool isOfType(RefCountPointer<const AnyAtomicType>& self, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return isOfType(self, buff1.ptr(), buff2.ptr(), context);
}

static bool isInstanceOfType(RefCountPointer<const AnyAtomicType>& self, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->isInstanceOfType(targetURI, targetType, context);
}

static bool isInstanceOfType(RefCountPointer<const AnyAtomicType>& self, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return isInstanceOfType(self, buff1.ptr(), buff2.ptr(), context);
}

static void typeToBuffer(RefCountPointer<const AnyAtomicType>& self, DynamicContext *context, xercesc::XMLBuffer &buffer) {
	self->typeToBuffer(context, buffer);
}

static bool castIsSupported(RefCountPointer<const AnyAtomicType>& self, AnyAtomicType::AtomicObjectType targetIndex, const DynamicContext* context) {
	return self->castIsSupported(targetIndex, context);
}

static AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex(RefCountPointer<const AnyAtomicType>& self) {
	return self->getPrimitiveTypeIndex();
}

//! Item
static void* getInterface(RefCountPointer<const AnyAtomicType>& self, const XMLCh* name) {
	return self->getInterface(name);
}

static void* getInterface(RefCountPointer<const AnyAtomicType>& self, const char* name) {
	pyxerces::XMLString buff(name);
	return getInterface(self, buff.ptr());
}

};

// =================================================
// const ATBooleanOrDerived
class RefCountPointerConstATBooleanOrDerivedDefVisitor
 : public boost::python::def_visitor<RefCountPointerConstATBooleanOrDerivedDefVisitor>
{
friend class def_visitor_access;
public:
template<class T>
void visit(T& class_) const {
	class_
	//! ATBooleanOrDerived
	.def(RefCountPointerItemBasedCastDefVisitor<ATBooleanOrDerived>())
	.def("getPrimitiveTypeName", &RefCountPointerConstATBooleanOrDerivedDefVisitor::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeURI", &RefCountPointerConstATBooleanOrDerivedDefVisitor::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeName", &RefCountPointerConstATBooleanOrDerivedDefVisitor::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("asString", &RefCountPointerConstATBooleanOrDerivedDefVisitor::asString, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("equals", &RefCountPointerConstATBooleanOrDerivedDefVisitor::equals)
	.def("compare", &RefCountPointerConstATBooleanOrDerivedDefVisitor::compare)
	.def("isTrue", &RefCountPointerConstATBooleanOrDerivedDefVisitor::isTrue)
	.def("isFalse", &RefCountPointerConstATBooleanOrDerivedDefVisitor::isFalse)
	.def("getPrimitiveTypeIndex", &RefCountPointerConstATBooleanOrDerivedDefVisitor::getPrimitiveTypeIndex)
	//! AnyAtomicType
	.def("isAtomicValue", &RefCountPointerConstATBooleanOrDerivedDefVisitor::isAtomicValue)
	.def("isNode", &RefCountPointerConstATBooleanOrDerivedDefVisitor::isNode)
	.def("isFunction", &RefCountPointerConstATBooleanOrDerivedDefVisitor::isFunction)
	.def("isNumericValue", &RefCountPointerConstATBooleanOrDerivedDefVisitor::isNumericValue)
	.def("isDateOrTimeTypeValue", &RefCountPointerConstATBooleanOrDerivedDefVisitor::isDateOrTimeTypeValue)
	.def("getPrimitiveTypeURI", &RefCountPointerConstATBooleanOrDerivedDefVisitor::getPrimitiveTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const ATBooleanOrDerived>&, EventHandler* events, const DynamicContext*, bool, bool)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const ATBooleanOrDerived>&, EventHandler* events, const DynamicContext*, bool)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const ATBooleanOrDerived>&, EventHandler* events, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::generateEvents))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATBooleanOrDerived>&, AnyAtomicType::AtomicObjectType, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::castAs))
	.def("castAsNoCheck", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATBooleanOrDerived>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::castAsNoCheck))
	.def("castAsNoCheck", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATBooleanOrDerived>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::castAsNoCheck))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATBooleanOrDerived>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::castAs))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATBooleanOrDerived>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::castAs))
	.def("castable", static_cast<bool(*)(RefCountPointer<const ATBooleanOrDerived>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::castable))
	.def("castable", static_cast<bool(*)(RefCountPointer<const ATBooleanOrDerived>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::castable))
	.def("isOfType", static_cast<bool(*)(RefCountPointer<const ATBooleanOrDerived>&, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::isOfType))
	.def("isOfType", static_cast<bool(*)(RefCountPointer<const ATBooleanOrDerived>&, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::isOfType))
	.def("isInstanceOfType", static_cast<bool(*)(RefCountPointer<const ATBooleanOrDerived>&, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::isInstanceOfType))
	.def("isInstanceOfType", static_cast<bool(*)(RefCountPointer<const ATBooleanOrDerived>&, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::isInstanceOfType))
	.def("typeToBuffer", &RefCountPointerConstATBooleanOrDerivedDefVisitor::typeToBuffer)
	.def("castIsSupported", &RefCountPointerConstATBooleanOrDerivedDefVisitor::castIsSupported)
	//! Item
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const ATBooleanOrDerived>&, const XMLCh*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const ATBooleanOrDerived>&, const char*)>(&RefCountPointerConstATBooleanOrDerivedDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	;
}

//! ATBooleanOrDerived
static const XMLCh* getPrimitiveTypeName(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->getPrimitiveTypeName();
}

static const XMLCh* getTypeURI(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->getTypeURI();
}

static const XMLCh* getTypeName(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->getTypeName();
}

static const XMLCh* asString(RefCountPointer<const ATBooleanOrDerived>& self, const DynamicContext* context) {
	return self->asString(context);
}

static bool equals(RefCountPointer<const ATBooleanOrDerived>& self, const AnyAtomicType::Ptr &target, const DynamicContext* context) {
	return self->equals(target, context);
}

static int compare(RefCountPointer<const ATBooleanOrDerived>& self, const ATBooleanOrDerived::Ptr &other, const DynamicContext *context) {
	return self->compare(other, context);
}

static bool isTrue(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->isTrue();
}

static bool isFalse(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->isFalse();
}

static AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->getPrimitiveTypeIndex();
}

//! AnyAtomicType
static bool isAtomicValue(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->isAtomicValue();
}

static bool isNode(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->isNode();
}

static bool isFunction(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->isFunction();
}

static bool isNumericValue(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->isNumericValue();
}

static bool isDateOrTimeTypeValue(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->isDateOrTimeTypeValue();
}

static const XMLCh* getPrimitiveTypeURI(RefCountPointer<const ATBooleanOrDerived>& self) {
	return self->getPrimitiveTypeURI();
}

static void generateEvents(RefCountPointer<const ATBooleanOrDerived>& self, EventHandler *events, const DynamicContext *context, bool preserveNS, bool preserveType) {
	self->generateEvents(events, context, preserveNS, preserveType);
}

static void generateEvents(RefCountPointer<const ATBooleanOrDerived>& self, EventHandler *events, const DynamicContext *context, bool preserveNS) {
	self->generateEvents(events, context, preserveNS, true);
}

static void generateEvents(RefCountPointer<const ATBooleanOrDerived>& self, EventHandler *events, const DynamicContext *context) {
	self->generateEvents(events, context, true);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const DynamicContext* context) {
	return self->castAs(targetIndex, context);
}

static AnyAtomicType::Ptr castAsNoCheck(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castAsNoCheck(targetIndex, targetURI, targetType, context);
}

static AnyAtomicType::Ptr castAsNoCheck(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castAsNoCheck(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castAs(targetIndex, targetURI, targetType, context);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castAs(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static bool castable(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castable(targetIndex, targetURI, targetType, context);
}

static bool castable(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castable(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static bool isOfType(RefCountPointer<const ATBooleanOrDerived>& self, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->isOfType(targetURI, targetType, context);
}

static bool isOfType(RefCountPointer<const ATBooleanOrDerived>& self, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return isOfType(self, buff1.ptr(), buff2.ptr(), context);
}

static bool isInstanceOfType(RefCountPointer<const ATBooleanOrDerived>& self, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->isInstanceOfType(targetURI, targetType, context);
}

static bool isInstanceOfType(RefCountPointer<const ATBooleanOrDerived>& self, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return isInstanceOfType(self, buff1.ptr(), buff2.ptr(), context);
}

static void typeToBuffer(RefCountPointer<const ATBooleanOrDerived>& self, DynamicContext *context, xercesc::XMLBuffer &buffer) {
	self->typeToBuffer(context, buffer);
}

static bool castIsSupported(RefCountPointer<const ATBooleanOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const DynamicContext* context) {
	return self->castIsSupported(targetIndex, context);
}

//! Item
static void* getInterface(RefCountPointer<const ATBooleanOrDerived>& self, const XMLCh* name) {
	return self->getInterface(name);
}

static void* getInterface(RefCountPointer<const ATBooleanOrDerived>& self, const char* name) {
	pyxerces::XMLString buff(name);
	return getInterface(self, buff.ptr());
}

};

// =================================================
// const ATQNameOrDerived
class RefCountPointerConstATQNameOrDerivedDefVisitor
 : public boost::python::def_visitor<RefCountPointerConstATQNameOrDerivedDefVisitor>
{
friend class def_visitor_access;
public:
template<class T>
void visit(T& class_) const {
	class_
	//! ATQNameOrDerived
	.def(RefCountPointerItemBasedCastDefVisitor<ATQNameOrDerived>())
	.def("getPrimitiveTypeName", &RefCountPointerConstATQNameOrDerivedDefVisitor::getPrimitiveTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeURI", &RefCountPointerConstATQNameOrDerivedDefVisitor::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeName", &RefCountPointerConstATQNameOrDerivedDefVisitor::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getURI", &RefCountPointerConstATQNameOrDerivedDefVisitor::getURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getPrefix", &RefCountPointerConstATQNameOrDerivedDefVisitor::getPrefix, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getName", &RefCountPointerConstATQNameOrDerivedDefVisitor::getName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("asString", &RefCountPointerConstATQNameOrDerivedDefVisitor::asString, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("equals", &RefCountPointerConstATQNameOrDerivedDefVisitor::equals)
	.def("compare", &RefCountPointerConstATQNameOrDerivedDefVisitor::compare)
	.def("getPrimitiveTypeIndex", &RefCountPointerConstATQNameOrDerivedDefVisitor::getPrimitiveTypeIndex)
	//! AnyAtomicType
	.def("isAtomicValue", &RefCountPointerConstATQNameOrDerivedDefVisitor::isAtomicValue)
	.def("isNode", &RefCountPointerConstATQNameOrDerivedDefVisitor::isNode)
	.def("isFunction", &RefCountPointerConstATQNameOrDerivedDefVisitor::isFunction)
	.def("isNumericValue", &RefCountPointerConstATQNameOrDerivedDefVisitor::isNumericValue)
	.def("isDateOrTimeTypeValue", &RefCountPointerConstATQNameOrDerivedDefVisitor::isDateOrTimeTypeValue)
	.def("getPrimitiveTypeURI", &RefCountPointerConstATQNameOrDerivedDefVisitor::getPrimitiveTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const ATQNameOrDerived>&, EventHandler* events, const DynamicContext*, bool, bool)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const ATQNameOrDerived>&, EventHandler* events, const DynamicContext*, bool)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const ATQNameOrDerived>&, EventHandler* events, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::generateEvents))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATQNameOrDerived>&, AnyAtomicType::AtomicObjectType, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::castAs))
	.def("castAsNoCheck", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATQNameOrDerived>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::castAsNoCheck))
	.def("castAsNoCheck", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATQNameOrDerived>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::castAsNoCheck))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATQNameOrDerived>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::castAs))
	.def("castAs", static_cast<AnyAtomicType::Ptr(*)(RefCountPointer<const ATQNameOrDerived>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::castAs))
	.def("castable", static_cast<bool(*)(RefCountPointer<const ATQNameOrDerived>&, AnyAtomicType::AtomicObjectType, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::castable))
	.def("castable", static_cast<bool(*)(RefCountPointer<const ATQNameOrDerived>&, AnyAtomicType::AtomicObjectType, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::castable))
	.def("isOfType", static_cast<bool(*)(RefCountPointer<const ATQNameOrDerived>&, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::isOfType))
	.def("isOfType", static_cast<bool(*)(RefCountPointer<const ATQNameOrDerived>&, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::isOfType))
	.def("isInstanceOfType", static_cast<bool(*)(RefCountPointer<const ATQNameOrDerived>&, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::isInstanceOfType))
	.def("isInstanceOfType", static_cast<bool(*)(RefCountPointer<const ATQNameOrDerived>&, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::isInstanceOfType))
	.def("typeToBuffer", &RefCountPointerConstATQNameOrDerivedDefVisitor::typeToBuffer)
	.def("castIsSupported", &RefCountPointerConstATQNameOrDerivedDefVisitor::castIsSupported)
	//! Item
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const ATQNameOrDerived>&, const XMLCh*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const ATQNameOrDerived>&, const char*)>(&RefCountPointerConstATQNameOrDerivedDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	;
}

//! ATQNameOrDerived
static const XMLCh* getPrimitiveTypeName(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getPrimitiveTypeName();
}

static const XMLCh* getTypeURI(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getTypeURI();
}

static const XMLCh* getTypeName(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getTypeName();
}

static const XMLCh* getURI(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getURI();
}

static const XMLCh* getPrefix(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getPrefix();
}

static const XMLCh* getName(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getName();
}

static const XMLCh* asString(RefCountPointer<const ATQNameOrDerived>& self, const DynamicContext* context) {
	return self->asString(context);
}

static bool equals(RefCountPointer<const ATQNameOrDerived>& self, const AnyAtomicType::Ptr &target, const DynamicContext* context) {
	return self->equals(target, context);
}

static int compare(RefCountPointer<const ATQNameOrDerived>& self, const ATBooleanOrDerived::Ptr &other, const DynamicContext *context) {
	return self->compare(other, context);
}

static AnyAtomicType::AtomicObjectType getPrimitiveTypeIndex(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getPrimitiveTypeIndex();
}

//! AnyAtomicType
static bool isAtomicValue(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->isAtomicValue();
}

static bool isNode(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->isNode();
}

static bool isFunction(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->isFunction();
}

static bool isNumericValue(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->isNumericValue();
}

static bool isDateOrTimeTypeValue(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->isDateOrTimeTypeValue();
}

static const XMLCh* getPrimitiveTypeURI(RefCountPointer<const ATQNameOrDerived>& self) {
	return self->getPrimitiveTypeURI();
}

static void generateEvents(RefCountPointer<const ATQNameOrDerived>& self, EventHandler *events, const DynamicContext *context, bool preserveNS, bool preserveType) {
	self->generateEvents(events, context, preserveNS, preserveType);
}

static void generateEvents(RefCountPointer<const ATQNameOrDerived>& self, EventHandler *events, const DynamicContext *context, bool preserveNS) {
	self->generateEvents(events, context, preserveNS, true);
}

static void generateEvents(RefCountPointer<const ATQNameOrDerived>& self, EventHandler *events, const DynamicContext *context) {
	self->generateEvents(events, context, true);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const DynamicContext* context) {
	return self->castAs(targetIndex, context);
}

static AnyAtomicType::Ptr castAsNoCheck(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castAsNoCheck(targetIndex, targetURI, targetType, context);
}

static AnyAtomicType::Ptr castAsNoCheck(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castAsNoCheck(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castAs(targetIndex, targetURI, targetType, context);
}

static AnyAtomicType::Ptr castAs(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castAs(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static bool castable(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->castable(targetIndex, targetURI, targetType, context);
}

static bool castable(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return castable(self, targetIndex, buff1.ptr(), buff2.ptr(), context);
}

static bool isOfType(RefCountPointer<const ATQNameOrDerived>& self, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->isOfType(targetURI, targetType, context);
}

static bool isOfType(RefCountPointer<const ATQNameOrDerived>& self, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return isOfType(self, buff1.ptr(), buff2.ptr(), context);
}

static bool isInstanceOfType(RefCountPointer<const ATQNameOrDerived>& self, const XMLCh* targetURI, const XMLCh* targetType, const DynamicContext* context) {
	return self->isInstanceOfType(targetURI, targetType, context);
}

static bool isInstanceOfType(RefCountPointer<const ATQNameOrDerived>& self, const char* targetURI, const char* targetType, const DynamicContext* context) {
	pyxerces::XMLString buff1(targetURI), buff2(targetType);
	return isInstanceOfType(self, buff1.ptr(), buff2.ptr(), context);
}

static void typeToBuffer(RefCountPointer<const ATQNameOrDerived>& self, DynamicContext *context, xercesc::XMLBuffer &buffer) {
	self->typeToBuffer(context, buffer);
}

static bool castIsSupported(RefCountPointer<const ATQNameOrDerived>& self, AnyAtomicType::AtomicObjectType targetIndex, const DynamicContext* context) {
	return self->castIsSupported(targetIndex, context);
}

//! Item
static void* getInterface(RefCountPointer<const ATQNameOrDerived>& self, const XMLCh* name) {
	return self->getInterface(name);
}

static void* getInterface(RefCountPointer<const ATQNameOrDerived>& self, const char* name) {
	pyxerces::XMLString buff(name);
	return getInterface(self, buff.ptr());
}

};

// =================================================
//! Node special def_visitor
class NodeSpecialDefVisitor
: public boost::python::def_visitor<NodeSpecialDefVisitor>
{
friend class def_visitor_access;
public:
template <class T>
void visit(T& class_) const {
	class_
	.def("getXercesNode", &getXercesNode, boost::python::return_value_policy<boost::python::reference_existing_object>())
	;
}

static xercesc::DOMNode* getXercesNode(Node::Ptr& self) {
	return static_cast<xercesc::DOMNode*>(self->getInterface(XercesConfiguration::gXerces));
}

};

// const Node
class RefCountPointerConstNodeDefVisitor
 : public boost::python::def_visitor<RefCountPointerConstNodeDefVisitor>
{
friend class def_visitor_access;
public:
template<class T>
void visit(T& class_) const {
	class_
	//! Node
	.def(RefCountPointerItemBasedCastDefVisitor<Node>())
	.def(NodeSpecialDefVisitor())
	.def("isNode", &RefCountPointerConstNodeDefVisitor::isNode)
	.def("isAtomicValue", &RefCountPointerConstNodeDefVisitor::isAtomicValue)
	.def("isFunction", &RefCountPointerConstNodeDefVisitor::isFunction)
	.def("typeToBuffer", &RefCountPointerConstNodeDefVisitor::typeToBuffer)
	.def("asString", &RefCountPointerConstNodeDefVisitor::asString, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("hasInstanceOfType", static_cast<bool(*)(RefCountPointer<const Node>&, const XMLCh*, const XMLCh*, const DynamicContext*)>(&RefCountPointerConstNodeDefVisitor::hasInstanceOfType))
	.def("hasInstanceOfType", static_cast<bool(*)(RefCountPointer<const Node>&, const char*, const char*, const DynamicContext*)>(&RefCountPointerConstNodeDefVisitor::hasInstanceOfType))
	.def("dmBaseURI", &RefCountPointerConstNodeDefVisitor::dmBaseURI)
	.def("dmNodeKind", &RefCountPointerConstNodeDefVisitor::dmNodeKind, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("dmNodeName", &RefCountPointerConstNodeDefVisitor::dmNodeName)
	.def("dmStringValue", &RefCountPointerConstNodeDefVisitor::dmStringValue, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("dmTypedValue", &RefCountPointerConstNodeDefVisitor::dmTypedValue)
	.def("dmDocumentURI", &RefCountPointerConstNodeDefVisitor::dmDocumentURI)
	.def("dmTypeName", &RefCountPointerConstNodeDefVisitor::dmTypeName)
	.def("dmNilled", &RefCountPointerConstNodeDefVisitor::dmNilled)
	.def("lessThan", &RefCountPointerConstNodeDefVisitor::lessThan)
	.def("equals", &RefCountPointerConstNodeDefVisitor::equals)
	.def("uniqueLessThan", &RefCountPointerConstNodeDefVisitor::uniqueLessThan)
	.def("root", &RefCountPointerConstNodeDefVisitor::root)
	.def("dmParent", &RefCountPointerConstNodeDefVisitor::dmParent)
	.def("dmAttributes", &RefCountPointerConstNodeDefVisitor::dmAttributes)
	.def("dmNamespaceNodes", &RefCountPointerConstNodeDefVisitor::dmNamespaceNodes)
	.def("dmChildren", &RefCountPointerConstNodeDefVisitor::dmChildren)
	.def("getAxisResult", &RefCountPointerConstNodeDefVisitor::getAxisResult)
	.def("dmIsId", &RefCountPointerConstNodeDefVisitor::dmIsId)
	.def("dmIsIdRefs", &RefCountPointerConstNodeDefVisitor::dmIsIdRefs)
	.def("getTypeURI", &RefCountPointerConstNodeDefVisitor::getTypeURI, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("getTypeName", &RefCountPointerConstNodeDefVisitor::getTypeName, boost::python::return_value_policy<boost::python::return_by_value>())
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const Node>&, EventHandler* events, const DynamicContext*, bool, bool)>(&RefCountPointerConstNodeDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const Node>&, EventHandler* events, const DynamicContext*, bool)>(&RefCountPointerConstNodeDefVisitor::generateEvents))
	.def("generateEvents", static_cast<void(*)(RefCountPointer<const Node>&, EventHandler* events, const DynamicContext*)>(&RefCountPointerConstNodeDefVisitor::generateEvents))
	//! Item
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const Node>&, const XMLCh*)>(&RefCountPointerConstNodeDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	.def("getInterface", static_cast<void*(*)(RefCountPointer<const Node>&, const char*)>(&RefCountPointerConstNodeDefVisitor::getInterface), boost::python::return_value_policy<boost::python::return_opaque_pointer>())  //!< void*
	;
}

//! Node
static bool isNode(RefCountPointer<const Node>& self) {
	return self->isNode();
}

static bool isAtomicValue(RefCountPointer<const Node>& self) {
	return self->isAtomicValue();
}

static bool isFunction(RefCountPointer<const Node>& self) {
	return self->isFunction();
}

static void typeToBuffer(RefCountPointer<const Node>& self, DynamicContext *context, xercesc::XMLBuffer &buffer) {
	self->typeToBuffer(context, buffer);
}

static const XMLCh* asString(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->asString(context);
}

static bool hasInstanceOfType(RefCountPointer<const Node>& self, const XMLCh* typeURI, const XMLCh* typeName, const DynamicContext* context) {
	return self->hasInstanceOfType(typeURI, typeName, context);
}

static bool hasInstanceOfType(RefCountPointer<const Node>& self, const char* typeURI, const char* typeName, const DynamicContext* context) {
	pyxerces::XMLString buff1(typeURI), buff2(typeName);
	return self->hasInstanceOfType(buff1.ptr(), buff2.ptr(), context);
}

static Sequence dmBaseURI(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmBaseURI(context);
}

static const XMLCh* dmNodeKind(RefCountPointer<const Node>& self) {
	return self->dmNodeKind();
}

static ATQNameOrDerived::Ptr dmNodeName(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmNodeName(context);
}

static const XMLCh* dmStringValue(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmStringValue(context);
}

static Sequence dmTypedValue(RefCountPointer<const Node>& self, DynamicContext* context) {
	return self->dmTypedValue(context);
}

static Sequence dmDocumentURI(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmDocumentURI(context);
}

static ATQNameOrDerived::Ptr dmTypeName(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmTypeName(context);
}

static ATBooleanOrDerived::Ptr dmNilled(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmNilled(context);
}

static bool lessThan(RefCountPointer<const Node>& self, const Node::Ptr &other, const DynamicContext *context) {
	return self->lessThan(other, context);
}

static bool equals(RefCountPointer<const Node>& self, const Node::Ptr& other) {
	return self->equals(other);
}

static bool uniqueLessThan(RefCountPointer<const Node>& self, const Node::Ptr &other, const DynamicContext *context) {
	return self->uniqueLessThan(other, context);
}

static Node::Ptr root(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->root(context);
}

static Node::Ptr dmParent(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmParent(context);
}

static Result dmAttributes(RefCountPointer<const Node>& self, const DynamicContext* context, const LocationInfo *info) {
	return self->dmAttributes(context, info);
}

static Result dmNamespaceNodes(RefCountPointer<const Node>& self, const DynamicContext* context, const LocationInfo *info) {
	return self->dmNamespaceNodes(context, info);
}

static Result dmChildren(RefCountPointer<const Node>& self, const DynamicContext *context, const LocationInfo *info) {
	return self->dmChildren(context, info);
}

static Result getAxisResult(RefCountPointer<const Node>& self, XQStep::Axis axis, const NodeTest *nodeTest, const DynamicContext *context, const LocationInfo *info) {
	return self->getAxisResult(axis, nodeTest, context, info);
}

static ATBooleanOrDerived::Ptr dmIsId(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmIsId(context);
}

static ATBooleanOrDerived::Ptr dmIsIdRefs(RefCountPointer<const Node>& self, const DynamicContext* context) {
	return self->dmIsIdRefs(context);
}

static const XMLCh* getTypeURI(RefCountPointer<const Node>& self) {
	return self->getTypeURI();
}

static const XMLCh* getTypeName(RefCountPointer<const Node>& self) {
	return self->getTypeName();
}

static void generateEvents(RefCountPointer<const Node>& self, EventHandler *events, const DynamicContext *context, bool preserveNS, bool preserveType) {
	self->generateEvents(events, context, preserveNS, preserveType);
}

static void generateEvents(RefCountPointer<const Node>& self, EventHandler *events, const DynamicContext *context, bool preserveNS) {
	self->generateEvents(events, context, preserveNS, true);
}

static void generateEvents(RefCountPointer<const Node>& self, EventHandler *events, const DynamicContext *context) {
	self->generateEvents(events, context, true);
}

//! Item
static void* getInterface(RefCountPointer<const Node>& self, const XMLCh* name) {
	return self->getInterface(name);
}

static void* getInterface(RefCountPointer<const Node>& self, const char* name) {
	pyxerces::XMLString buff(name);
	return getInterface(self, buff.ptr());
}

};

void ReferenceCounted_init(void) {
	typedef boost::mpl::string<'Cons', 'tIte', 'm'> ConstItemStr;
	typedef boost::mpl::string<'Cons', 'tAny', 'Atom', 'icTy', 'pe'> ConstAnyAtomicTypeStr;
	typedef boost::mpl::string<'Cons', 'tATB', 'oole', 'anOr', 'Deri', 'ved'> ConstATBooleanOrDerivedStr;
	typedef boost::mpl::string<'Cons', 'tATQ', 'Name', 'OrDe', 'rive', 'd'> ConstATQNameOrDerivedStr;
	typedef boost::mpl::string<'Cons', 'tNod', 'e'> ConstNodeStr;
	//! RefCountPointer
	makeRefCountPointer<ConstItemStr, const Item, RefCountPointerConstItemDefVisitor>();
	makeRefCountPointer<ConstAnyAtomicTypeStr, const AnyAtomicType, RefCountPointerConstAnyAtomicTypeDefVisitor>();
	makeRefCountPointer<ConstATBooleanOrDerivedStr, const ATBooleanOrDerived, RefCountPointerConstATBooleanOrDerivedDefVisitor>();
	makeRefCountPointer<ConstATQNameOrDerivedStr, const ATQNameOrDerived, RefCountPointerConstATQNameOrDerivedDefVisitor>();
	makeRefCountPointer<ConstNodeStr, const Node, RefCountPointerConstNodeDefVisitor>();
}

} /* namespace pyxqilla */
