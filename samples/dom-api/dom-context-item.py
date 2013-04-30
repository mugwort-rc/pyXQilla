# -*- coding: utf-8 -*-
import sys
import Xerces, XQilla

def main():
	xqillaImplementation = Xerces.DOMImplementationRegistry.getDOMImplementation('XPath2 3.0')

	try:
		# Create a DOMLSParser object
		parser = xqillaImplementation.createLSParser(Xerces.DOMImplementationLS.MODE_SYNCHRONOUS, '')
		parser.getDomConfig().setParameter(Xerces.XMLUni.fgDOMNamespaces, True)
		parser.getDomConfig().setParameter(Xerces.XMLUni.fgXercesSchema, True)
		parser.getDomConfig().setParameter(Xerces.XMLUni.fgDOMValidateIfSchema, True)

		# Parse a DOMDocument
		document = parser.parseURI('foo.xml')
		if document is None:
			print 'Document not found.'
			return sys.exit(1)

		# Parse an XPath 2 expression
		expression = document.createExpression('foo/bar/@baz', None)

		# Execute the query
		result = expression.evaluate(document, Xerces.DOMXPathResult.ITERATOR_RESULT_TYPE, None)

		# Create a DOMLSSerializer to output the nodes
		serializer = xqillaImplementation.createLSSerializer()
		output = xqillaImplementation.createLSOutput()
		target = Xerces.StdOutFormatTarget()
		output.setByteStream(target)

		# Iterate over the results, printing them
		while result.iterateNext():
			serializer.write(result.getNodeValue(), output)
			print ''

	except XQilla.XQillaException, e:
		print 'XQillaException:', e.getString()
		return sys.exit(1)

	return sys.exit(0)

if __name__ == '__main__':
	main()

