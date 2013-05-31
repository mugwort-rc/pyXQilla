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

XQuery Update Facility
-------------------------

	file('test.xml', 'wb').write('<test><c/></test>')

	import XQilla
	xqilla  = XQilla.XQilla()
	conf    = XQilla.XercesConfiguration()
	context = xqilla.createContext(XQilla.XQilla.XQUERY_UPDATE, conf)
	query   = xqilla.parse('insert node <a><b/></a> into doc("test.xml")//c', context)
	ctx     = query.createDynamicContext()
	query.execute(ctx)

