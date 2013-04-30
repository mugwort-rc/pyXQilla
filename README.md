pyXQilla
========

Build
=====

	$ python setup.py build

Usage
=====

Simple API
----------

	import XQilla
	xqilla  = XQilla.XQilla()
	query   = xqilla.parse('1 to 100')
	context = query.createDynamicContext()
	result  = query.execute(context)
	# output
	while True:
	    item = result.next(context)
	    if item.isNull():
	        break
	    print item.asString(context)

XPath2 3.0
----------

	import Xerces, XQilla
	impl = Xerces.DOMImplementationRegistry.getDOMImplementation(XQilla.gXPath2_3_0)

