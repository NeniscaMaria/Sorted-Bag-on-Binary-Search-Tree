//ADT SortedBag – using a BST with linked representation with dynamic allocation.If an
//element appears multiple times, it will be stored multiple times in the BST.

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "sortedBag.h"
#include <assert.h>

bool relation(TComp e1, TComp e2) {
	return e1 <= e2;
}
int main() {
	testAll();
	testAllExtended();

	SortedBag sb(relation);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);
	sb.addOccurences(3, 5);
	assert(sb.size() == 9);
	assert(sb.nrOccurrences(5) == 5);
	return 0;
}