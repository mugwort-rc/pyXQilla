# -*- coding: utf-8 -*-
import sys
import XQilla

def main():
	# Initialise Xerces-C and XQilla by creating the factory object
	xqilla = XQilla.XQilla()

	# Parse an XQuery expression
	# (AutoDelete deletes the object at the end of the scope)
	query = xqilla.parse('1 to 100')

	# Create a context object
	context = query.createDynamicContext()

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

