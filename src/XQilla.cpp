/*
 * XQilla.cpp
 *
 *  Created on: 2013/02/18
 *      Author: mugwort_rc
 */

#include <Python.h>
#include <boost/python.hpp>
#define BOOST_PYTHON_STATIC_LIB

// exceptions
#include "exceptions/XQillaException.h"

// utils
#include "utils/XQillaPlatformUtils.h"

BOOST_PYTHON_MODULE(__XQilla)
{
	// ==================================================
	// exceptions
	// --------------------------------------------------
	pyxqilla::XQillaException_init();

	// ==================================================
	// utils
	// --------------------------------------------------
	pyxqilla::XQillaPlatformUtils_init();
}


