# -*- coding: utf-8 -*-
import sys
import XQilla

def main():
	# Initialise Xerces-C and XQilla by creating the factory object
	xqilla = XQilla.XQilla()

	# Parse an XQuery expression
	query = xqilla.parse('foo/bar/@baz')

	# Create a context object
	context = query.createDynamicContext()

	# Parse a document, and set it as the context item
	seq = context.resolveDocument('foo.xml')
	if not seq.isEmpty() and seq.first().isNode():
		context.setContextItem(seq.first())
		context.setContextPosition(1)
		context.setContextSize(1)

	# Execute the query, using the context
	result = query.execute(context)

	# Iterate over the results, printing them
	while True:
		item = result.next(context)
		if item.isNull():
			break
		print item.asString(context)

	return sys.exit(0)

if __name__ == '__main__':
	main()

