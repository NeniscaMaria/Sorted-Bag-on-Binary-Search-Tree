#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>
#include <exception>

using namespace std;

bool relation2(TComp r1, TComp r2) {
	return r1 <= r2;
}

bool relation3(TComp r1, TComp r2) {
	return r1 >= r2;
}

void testCreate() {
	SortedBag sb(relation2);
	assert(sb.isEmpty() == true);
	assert(sb.size() == 0);

	for (int i = -10; i < 30; i++) {
		assert(sb.remove(i) == false);
	}
	for (int i = -10; i < 30; i++) {
		assert(sb.search(i) == false);
	}
	for (int i = -10; i < 30; i++) {
		assert(sb.nrOccurrences(i) == 0);
	}
	SortedBagIterator it = sb.iterator();
	assert(it.valid() == false);
	try {
		it.getCurrent();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		it.next();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
}

void testIterator(SortedBag& sb, Relation rel) {
	SortedBagIterator it = sb.iterator();
	TComp e1;
	TComp e2;
	if (it.valid()) {
		e1 = it.getCurrent();
		it.next();
	}
	while (it.valid()) {
		e2 = e1;
		e1 = it.getCurrent();
		it.next();
		assert(sb.search(e1) == true);
		assert(sb.search(e2) == true);
		assert(sb.nrOccurrences(e1) > 0);
		assert(sb.nrOccurrences(e2) > 0);
		assert(rel(e2, e1));
	}
	try {
		it.getCurrent();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		it.next();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	it.first();
	assert(it.valid() == true);
}

void testAdd(Relation r) {
	SortedBag sb(r);
	for (int i = 0; i < 100; i++) {
		sb.add(i);
	}
	assert(sb.size() == 100);
	assert(sb.isEmpty() == false);
	testIterator(sb, r);

	for (int i = 200; i >= -200; i--) {
		sb.add(i);
	}
	assert(sb.size() == 501);
	testIterator(sb, r);

	for (int i = -300; i < 300; i++) {
		bool exista = sb.search(i);
		if (i == 1)
			std::cout << " ";
		int nrA = sb.nrOccurrences(i);

		if (i < -200 || i > 200) {
			assert(exista == false);
			assert(nrA == 0);
		}
		else if (i >= -200 && i < 0) {
			assert(exista == true);
			assert(nrA == 1);
		}
		else if (i >= 0 && i < 100) {
			assert(exista == true);
			assert(nrA == 2);
		}
		else if (i >= 100 && i <= 200) {
			assert(exista == true);
			assert(nrA == 1);
		}
	}

	for (int i = 0; i < 100; i++) {
		sb.add(0);
	}
	assert(sb.nrOccurrences(0) == 102);
	testIterator(sb, r);

	SortedBag sb2(r);
	for (int i = 0; i < 300; i = i + 2) {
		sb2.add(i);
		sb2.add(2 * i);
		sb2.add(-2 * i);
	}
	assert(sb2.size() == 450);
	testIterator(sb2, r);
}

void testRemove(Relation r) {
	SortedBag sb(r);
	for (int i = -100; i < 100; i++) {
		assert(sb.remove(i) == false);
		assert(sb.search(i) == false);
		assert(sb.nrOccurrences(i) == 0);
	}
	assert(sb.isEmpty() == true);

	for (int i = -100; i < 100; i++) {
		sb.add(i);
	}
	assert(sb.size() == 200);
	for (int i = -100; i < 100; i = i + 2) {
		assert(sb.remove(i) == true);
	}
	assert(sb.size() == 100);
	for (int i = -100; i < 100; i++) {
		if (i % 2 == 0) {
			assert(sb.nrOccurrences(i) == 0);
			assert(sb.search(i) == false);
			assert(sb.remove(i) == false);
		}
		else {
			assert(sb.nrOccurrences(i) == 1);
			assert(sb.search(i) == true);
		}
		sb.add(i);
		sb.add(i);
		sb.add(i);
	}
	assert(sb.size() == 700);
	for (int i = -200; i < 200; i++) {
		if (i < -100 || i >= 100) {
			assert(sb.search(i) == false);
			assert(sb.nrOccurrences(i) == 0);
			assert(sb.remove(i) == false);
		}
		else if (i % 2 == 0) {
			assert(sb.search(i) == true);
			assert(sb.nrOccurrences(i) == 3);
			assert(sb.remove(i) == true);
			assert(sb.remove(i) == true);
			assert(sb.remove(i) == true);
			assert(sb.remove(i) == false);
		}
		else {
			assert(sb.search(i) == true);
			assert(sb.nrOccurrences(i) == 4);
			assert(sb.remove(i) == true);
			assert(sb.remove(i) == true);
			assert(sb.remove(i) == true);
			assert(sb.remove(i) == true);
			assert(sb.remove(i) == false);
		}
	}
	SortedBag sb2(r);
	for (int i = 300; i >= -500; i--) {
		sb2.add(i);
		sb2.add(i * 2);
		sb2.add(-2 * i);
	}
	for (int i = -100; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			sb2.remove(i);
		}
	}
	for (int i = -100; i < 100; i++) {
		assert(sb2.nrOccurrences(i) == 0);
		assert(sb2.search(i) == false);
	}
}

void testQuantity(Relation r) {
	SortedBag sb(r);
	for (int j = 0; j < 5; j++) {
		cout << "Add " << j << endl;
		for (int i = -3000; i < 3000; i++) {
			sb.add(i);
		}
	}
	int count = 30000;
	assert(sb.size() == 30000);
	for (int i = 0; i < 10000; i++) {
		if (i % 1000 == 0) {
			cout << "Remove " << i << endl;
		}
		TComp nr = rand() % 8000 - 4000;
		if (sb.remove(nr) == true) {
			count--;
		}
		assert(sb.size() == count);
	}
	assert(sb.size() == count);
}



void testAllExtended() {
	testCreate();
	testAdd(relation2);
	testAdd(relation3);
	testRemove(relation2);
	testRemove(relation3);
	testQuantity(relation2);
	testQuantity(relation3);
}
