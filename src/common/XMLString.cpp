/*
 * XMLString.cpp
 *
 *  Created on: 2013/02/17
 *      Author: mugwort_rc
 */

#include "XMLString.h"

#include <math.h>
#include <boost/scoped_ptr.hpp>

#include <xercesc/util/XMLUniDefs.hpp>

#include <xercesc/util/XMLString.hpp>

namespace pyxerces {

class XMLChManager {
public:
	/*!
	 * Constructor
	 */
	XMLChManager(XMLCh* ptr)
		: _ptr(ptr)
	{}
	/*!
	 * Constructor
	 */
	XMLChManager(const XMLCh* ptr)
		: _ptr(const_cast<XMLCh*>(ptr))
	{}
	/*!
	 * Destructor
	 */
	~XMLChManager(void)
	{
		if(this->_ptr != nullptr) {
			xercesc::XMLString::release(&this->_ptr);
		}
	}

	/*!
	 * Get raw pointer
	 * @return XMLCh*
	 */
	XMLCh* ptr(void) const {
		return this->_ptr;
	}

	/*!
	 * Transcode string
	 */
	static boost::shared_ptr<XMLChManager> transcode(const std::string& str) {
		return boost::shared_ptr<XMLChManager>(new XMLChManager(xercesc::XMLString::transcode(str.c_str())));
	}

	/*!
	 * Replicate string
	 */
	static boost::shared_ptr<XMLChManager> replicate(const XMLCh* ptr) {
		return boost::shared_ptr<XMLChManager>(new XMLChManager(xercesc::XMLString::replicate(ptr)));
	}

private:
	XMLChManager(const XMLChManager&);
	XMLChManager& operator =(const XMLChManager&);

private:
	XMLCh* _ptr;

};

// ==================================================

boost::shared_ptr<XMLChManager> fromlist(const boost::python::list& li) {
	std::size_t len = boost::python::len(li);
	boost::scoped_ptr<XMLCh> buffer(new XMLCh[len+1]);
	std::size_t i = 0;
	for(i = 0; i < len; ++i){
		if( ! boost::python::extract<XMLCh>(li[i]).check()){
			return boost::shared_ptr<XMLChManager>();
		}
		buffer.get()[i] = boost::python::extract<XMLCh>(li[i]);
	}
	buffer.get()[i] = xercesc::chNull;
	return XMLChManager::replicate(buffer.get());
}

// ==================================================

XMLString::XMLString(void)
	: _ch()
{}

XMLString::XMLString(const std::string& str)
	: _ch(XMLChManager::transcode(str))
{}

XMLString::XMLString(const XMLCh* ptr)
	: _ch(XMLChManager::replicate(ptr))
{}

XMLString::XMLString(const boost::python::list& initializeList)
	: _ch(fromlist(initializeList))
{}

XMLString::XMLString(const XMLString& copy)
	: _ch(copy._ch)
{}

XMLString::~XMLString(void)
{}

XMLString& XMLString::operator =(const XMLString& rhs) {
	this->_ch = rhs._ch;
	return *this;
}

XMLCh* XMLString::ptr(void) const {
	if( ! this->_ch) {
		return nullptr;
	}
	return this->_ch->ptr();
}

XMLString XMLString::operator +(const XMLString& rhs) const {
	boost::scoped_ptr<XMLCh> buffer(new XMLCh[this->size() + rhs.size() + 1]);
	xercesc::XMLString::copyString(buffer.get(), this->ptr());
	xercesc::XMLString::catString(buffer.get(), rhs.ptr());
	return XMLString(buffer.get());
}

XMLString& XMLString::operator +=(const XMLString& rhs) {
	*this = *this + rhs;
	return *this;
}

XMLString::operator const XMLCh*(void) const {
	return this->ptr();
}

bool XMLString::operator <(const XMLString& rhs) const {
	return 0 > xercesc::XMLString::compareString(this->ptr(), rhs.ptr());
}

bool XMLString::operator <=(const XMLString& rhs) const {
	return 0 >= xercesc::XMLString::compareString(this->ptr(), rhs.ptr());
}

bool XMLString::operator >(const XMLString& rhs) const {
	return 0 < xercesc::XMLString::compareString(this->ptr(), rhs.ptr());
}

bool XMLString::operator >=(const XMLString& rhs) const {
	return 0 <= xercesc::XMLString::compareString(this->ptr(), rhs.ptr());
}

bool XMLString::operator ==(const XMLString& rhs) const {
	return xercesc::XMLString::equals(this->ptr(), rhs.ptr());
}

bool XMLString::operator !=(const XMLString& rhs) const {
	return ! this->operator ==(rhs);
}

XMLSize_t XMLString::hash(const XMLSize_t modulus) const {
	return xercesc::XMLString::hash(this->ptr(), modulus);
}

int XMLString::indexOf(const XMLCh ch) const {
	return xercesc::XMLString::indexOf(this->ptr(), ch);
}

int XMLString::lastIndexOf(const XMLCh ch) const {
	return xercesc::XMLString::lastIndexOf(this->ptr(), ch);
}

XMLString XMLString::subString(const XMLSize_t start, const XMLSize_t end) const {
	XMLSize_t size = this->size();
	if(start > end || start > size || end > size) {
		PyErr_SetString(PyExc_IndexError, "Index out of range");
		boost::python::throw_error_already_set();
	}
	XMLString result("");
	xercesc::XMLString::subString(result.ptr(), this->ptr(), start, end);
	return result;
}

bool XMLString::startsWith(const XMLString& prefix) const {
	return xercesc::XMLString::startsWith(this->ptr(), prefix.ptr());
}

bool XMLString::startsWith(const boost::python::tuple& prefixs) const {
	std::size_t size = boost::python::len(prefixs);
	for(std::size_t i = 0; i < size; ++i) {
		if( ! boost::python::extract<XMLString>(prefixs[i]).check()){
			continue;
		}
		if(this->startsWith(boost::python::extract<XMLString>(prefixs[i]))) {
			return true;
		}
	}
	return false;
}

bool XMLString::startsWithIn(const XMLString& prefix) const {
	return xercesc::XMLString::startsWithI(this->ptr(), prefix.ptr());
}

bool XMLString::startsWithIn(const boost::python::tuple& prefixs) const {
	std::size_t size = boost::python::len(prefixs);
	for(std::size_t i = 0; i < size; ++i) {
		if( ! boost::python::extract<XMLString>(prefixs[i]).check()){
			continue;
		}
		if(this->startsWithIn(boost::python::extract<XMLString>(prefixs[i]))) {
			return true;
		}
	}
	return false;
}

bool XMLString::endsWith(const XMLString& suffix) const {
	return xercesc::XMLString::endsWith(this->ptr(), suffix.ptr());
}

bool XMLString::endsWith(const boost::python::tuple& suffixs) const {
	std::size_t size = boost::python::len(suffixs);
	for(std::size_t i = 0; i < size; ++i) {
		if( ! boost::python::extract<XMLString>(suffixs[i]).check()){
			continue;
		}
		if(this->endsWith(boost::python::extract<XMLString>(suffixs[i]))) {
			return true;
		}
	}
	return false;
}

int XMLString::isMatch(const XMLString& pattern) const {
	return xercesc::XMLString::patternMatch(this->ptr(), pattern.ptr());
}

XMLSize_t XMLString::size(void) const {
	return xercesc::XMLString::stringLen(this->ptr());
}

bool XMLString::isValidNOTATION(void) const {
	return xercesc::XMLString::isValidNOTATION(this->ptr());
}

bool XMLString::isValidEncName(void) const {
	return xercesc::XMLString::isValidEncName(this->ptr());
}

bool XMLString::isAlpha(void) const {
	XMLCh*    ptr  = this->ptr();
	XMLSize_t size = this->size();
	for(XMLSize_t i = 0; i < size; ++i) {
		if( ! xercesc::XMLString::isAlpha(ptr[i])) {
			return false;
		}
	}
	return true;
}

bool XMLString::isDigit(void) const {
	XMLCh*    ptr  = this->ptr();
	XMLSize_t size = this->size();
	for(XMLSize_t i = 0; i < size; ++i) {
		if( ! xercesc::XMLString::isDigit(ptr[i])) {
			return false;
		}
	}
	return true;
}

bool XMLString::isAlphaNum(void) const {
	XMLCh*    ptr  = this->ptr();
	XMLSize_t size = this->size();
	for(XMLSize_t i = 0; i < size; ++i) {
		if( ! xercesc::XMLString::isAlphaNum(ptr[i])) {
			return false;
		}
	}
	return true;
}

bool XMLString::isHex(void) const {
	XMLCh*    ptr  = this->ptr();
	XMLSize_t size = this->size();
	for(XMLSize_t i = 0; i < size; ++i) {
		if( ! xercesc::XMLString::isHex(ptr[i])) {
			return false;
		}
	}
	return true;
}

bool XMLString::isLower(void) const {
	XMLString lower = this->lower();
	return this->operator ==(lower);
}

bool XMLString::isUpper(void) const {
	XMLString upper = this->upper();
	return this->operator ==(upper);
}

XMLString XMLString::strip(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::trim(result.ptr());
	return result;
}

XMLString XMLString::lower(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::lowerCase(result.ptr());
	return result;
}

XMLString XMLString::lowerASCII(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::lowerCaseASCII(result.ptr());
	return result;
}

XMLString XMLString::upper(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::upperCase(result.ptr());
	return result;
}

XMLString XMLString::upperASCII(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::upperCaseASCII(result.ptr());
	return result;
}

bool XMLString::isWSReplaced(void) const {
	return xercesc::XMLString::isWSReplaced(this->ptr());
}

bool XMLString::isWSCollapsed(void) const {
	return xercesc::XMLString::isWSCollapsed(this->ptr());
}

XMLString XMLString::replaceWS(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::replaceWS(result.ptr());
	return result;
}

XMLString XMLString::collapseWS(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::collapseWS(result.ptr());
	return result;
}

XMLString XMLString::removeWS(void) const {
	XMLString result = this->replicate();
	xercesc::XMLString::removeWS(result.ptr());
	return result;
}

XMLCh XMLString::at(const XMLSize_t i) const {
	if(i >= this->size()) {
		PyErr_SetString(PyExc_IndexError, "Index out of range");
		boost::python::throw_error_already_set();
		return 0;
	}
	return this->ptr()[i];
}

XMLString XMLString::makeUName(const XMLString& URI, const XMLString& name) {
	return XMLString(xercesc::XMLString::makeUName(URI.ptr(), name.ptr()));
}

XMLString XMLString::fixURI(const XMLString& str) {
	XMLString result("");
	xercesc::XMLString::fixURI(str.ptr(), result.ptr());
	return result;
}

XMLString XMLString::sizeToText(const unsigned int toFormat, const unsigned int radix, xercesc::MemoryManager* const manager) {
	unsigned int len = (log(toFormat) / log(radix)) + 1;
	boost::scoped_ptr<XMLCh> buffer(new XMLCh[len+1]);
	xercesc::XMLString::sizeToText(toFormat, buffer.get(), len, radix, manager);
	return XMLString(buffer.get());
}

XMLString XMLString::binToText(const unsigned int toFormat, const unsigned int radix, xercesc::MemoryManager* const manager) {
	unsigned int len = (log(toFormat) / log(radix)) + 1;
	boost::scoped_ptr<XMLCh> buffer(new XMLCh[len+1]);
	xercesc::XMLString::binToText(toFormat, buffer.get(), len, radix, manager);
	return XMLString(buffer.get());
}

std::string XMLString::toString(void) const {
	if( ! this->ptr()){
		return std::string();
	}
	return XMLString::transcode(this->ptr());
}

std::string XMLString::reprString(void) const {
	boost::python::object global_ns = boost::python::import("__main__").attr("__dict__");
	global_ns["obj"] = this->toString();
	// pprint
	boost::python::exec("import pprint\n"
						"pp  = pprint.PrettyPrinter()\n"
						"__res = 'X'+pp.pformat(obj)", global_ns, global_ns);
	return boost::python::extract<std::string>(global_ns["__res"]);
}

std::string XMLString::transcode(const XMLCh* ptr) {
	char* buff = xercesc::XMLString::transcode(ptr);
	if(buff == nullptr) {
		PyErr_SetString(PyExc_UnicodeTranslateError, "XMLString::transcode Error");
		boost::python::throw_error_already_set();
	}
	std::string result = buff;
	xercesc::XMLString::release(&buff);
	return result;
}

XMLString XMLString::replicate(void) const {
	if( ! this->ptr()){
		return XMLString(std::string());
	}
	return XMLString(this->ptr());
}

} /* namespace pyxerces */
