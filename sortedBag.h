#pragma once

typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
class SortedBagIterator;
typedef struct BSTNode {
	TComp info;
	BSTNode* left;
	BSTNode* right;
};

class SortedBag {

private:
	BSTNode* root;
	Relation relation;
	int s;

public:
	friend class SortedBagIterator;
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);
	BSTNode* insert(BSTNode*,TComp e);
	BSTNode* successor(BSTNode*);
	BSTNode* parent(BSTNode*);
	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	bool search(TComp e) const;
	//checks if an element is the sorted bag
	bool searchRec(BSTNode*,TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	void addOccurences(int nr, TComp elem);
	//destructor
	~SortedBag();

};