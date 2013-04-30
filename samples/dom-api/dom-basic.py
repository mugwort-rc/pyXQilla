# -*- coding: utf-8 -*-
import sys
import Xerces, XQilla

def main():
	# Get the XQilla DOMImplementation object
	xqillaImplementation = Xerces.DOMImplementationRegistry.getDOMImplementation('XPath2 3.0')

	# Create a DOMDocument
	document = xqillaImplementation.createDocument()

	# Parse an XPath 2 expression
	expression = document.createExpression('1 to 100', None)

	# Execute the query
	result = expression.evaluate(None, Xerces.DOMXPathResult.ITERATOR_RESULT_TYPE, None)

	# Iterate over the results, printing them
	while result.iterateNext():
		print result.getIntegerValue()

	return sys.exit(0)

if __name__ == '__main__':
	main()

