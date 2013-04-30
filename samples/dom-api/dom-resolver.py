# -*- coding: utf-8 -*-
import sys
import Xerces, XQilla

def main():
	if len(sys.argv) != 2:
		print 'Data file not specified.'
		return sys.exit(1)

	#####################
	# Initialise XQilla #
	#####################

	try:
		# 1. Obtain a DOM3 XPath2 implementation.  This is a XQilla-specific 
		#    implementation that overrides the standard DOMDocument, the standard 
		#    DOMWriter and the standard DOMBuilder
		xqillaImplementation = Xerces.DOMImplementationRegistry.getDOMImplementation('XPath2 3.0')

		# 2. Obtain a parser and set 'do namespaces', 'use schema' and 'validate' to 
		#    true.
		# Create a DOMLSParser object
		parser = xqillaImplementation.createLSParser(Xerces.DOMImplementationLS.MODE_SYNCHRONOUS, '')
		parser.getDomConfig().setParameter(Xerces.XMLUni.fgDOMNamespaces, True)
		parser.getDomConfig().setParameter(Xerces.XMLUni.fgXercesSchema, True)
		parser.getDomConfig().setParameter(Xerces.XMLUni.fgDOMValidateIfSchema, True)

		##########################
		# Parse our XML document #
		##########################
		document = parser.parseURI(sys.argv[1])
		if document is None:
			print 'Document not found:', sys.argv[1]
			return sys.exit(1)

		##############################
		# Create a parsed expression #
		# (compiled) and evaluate it #
		##############################

		# 1. Create a Namespace Resolver.  This holds a map of namespace prefixes 
		#    to namespace URIs.
		resolver = document.createNSResolver(document.getDocumentElement())
		resolver.addNamespaceBinding('my', 'http://example.com/myURI')

		# **************** Example 1: max() function ****************** #

		# 2. Create a parsed expression
		expression = 'max(/Catalogue/Book/Price)'
		parsedExpression = document.createExpression(expression, resolver)

		# 3. Evaluate the expression. We choose to have a first result, since we
		#    know the answer will have only one item. Could also choose
		#    XPath2Result.SNAPSHOT_RESULT and XPath2Result.ITERATOR_RESULT
		firstResult = parsedExpression.evaluate(document.getDocumentElement(), Xerces.DOMXPathResult.FIRST_RESULT_TYPE, None)

		# 4. Work with the result: output it to the screen in this case
		print 'The answer for expression "%s" is:'%(expression), firstResult.getNumberValue()

		# **************** Example 2: output of nodes ****************** #

		# 2. Create a parsed expression
		expression2 = '//Magazine'
		parsedExpression = document.createExpression(expression2, resolver)

		# 3. Evaluate the expression. We choose to have an iterator result
		iteratorResult = parsedExpression.evaluate(document.getDocumentElement(), Xerces.DOMXPathResult.ITERATOR_RESULT_TYPE, None)

		# 4. Work with the result: output it to the screen in this case

		# Create a DOMLSSerializer to output the nodes
		serializer = xqillaImplementation.createLSSerializer()
		output = xqillaImplementation.createLSOutput()
		target = Xerces.StdOutFormatTarget()
		output.setByteStream(target)

		print 'The answer for expression "%s" is:'%(expression2)

		i = 0
		while iteratorResult.iterateNext():
			if iteratorResult.isNode():
				print 'Node %d:'%i
				serializer.write(iteratorResult.getNodeValue(), output)
				print ''
				i += 1
			else:
				print 'Expected a node but received an atomic value!'
	except Xerces.DOMException, e:
		print 'DOMException:', e.getMessage()
		return sys.exit(1)

	return sys.exit(0)

if __name__ == '__main__':
	main()

