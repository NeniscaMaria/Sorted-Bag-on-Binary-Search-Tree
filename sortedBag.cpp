#include "sortedBag.h"
#include <iostream>
#include <stack>
#include "sortedBagIterator.h"
SortedBag::SortedBag(Relation r)
{
	this->root = NULL;
	this->relation = r;
	this->s = 0;
	//theta(1)
}

void SortedBag::add(TComp e)
{
	
	BSTNode* newNode = new BSTNode;
	newNode->info = e;
	newNode->left = NULL;
	newNode->right = NULL;
	BSTNode* current = this->root;
	BSTNode* previous = NULL;

	while (current != NULL) {
		previous = current;
		if (this->relation(current->info,e))
			current = current->right;
		else
			current = current->left;
	}
	if (previous == NULL)
		this->root = newNode;
	else
		if (this->relation(previous->info,e))
			previous->right = newNode;
		else
			previous->left = newNode;
	this->s += 1;

}//O(n)

BSTNode* SortedBag::insert(BSTNode * node,TComp e)
{
	
	if (node == NULL) {
		BSTNode* nodeToAdd = new BSTNode;
		nodeToAdd->info = e;
		nodeToAdd->left = NULL;
		nodeToAdd->right = NULL;
		node = nodeToAdd;
	}
	else
		if (!this->relation(node->info, e))
			node->left = this->insert(node->left, e);
		else
			node->right = this->insert(node->right, e);
	return node;
}//O(n);

BSTNode * SortedBag::successor(BSTNode * node)
{
	if (this->relation(this->root->info, node->info)) {
		if (node->right != NULL) {
			auto c = node->right;
			while (c->left != NULL)
				c = c->left;
			return c;
		}
		else {
			auto c = node;
			auto p = this->parent(c);
			while (p != NULL and p->left != c) {
				c = p;
				p = this->parent(p);
			}
			return p;
		}
	}
	else {
		if (node->left != NULL) {
			auto c = node->left;
			while (c->right != NULL)
				c = c->right;
			return c;
		}
		else {
			auto c = node;
			auto p = this->parent(c);
			while (p != NULL and p->right != c) {
				c = p;
				p = this->parent(p);
			}
			return p;
		}
	}
}//O(n^2)


BSTNode * SortedBag::parent(BSTNode * node)
{
	BSTNode* c = this->root;
	if (c == node)
		return NULL;
	else {
		while (c != NULL and c->left != node and c->right != node) {
			if (!this->relation(c->info, node->info))
				c = c->left;
			else
				c = c->right;
		}
		return c;
	}
}//O(n)

bool SortedBag::remove(TComp e)
{
	//we search for the node with this value
	auto currentNode = this->root;
	bool found = false;
	while (currentNode != NULL and found == false) {
		if (currentNode->info == e)
			found = true;
		else
			if (this->relation(currentNode->info, e))
				currentNode = currentNode->right;
			else
				currentNode = currentNode->left;
	}
	if (found == false) {//this means that the element does not exist
		return false;
	}
	//in currentNode we have the node with value e
	//the case when the node has no descendants
	if (currentNode->right == NULL and currentNode->left == NULL) {
		BSTNode* parent = this->parent(currentNode);
		if (parent == NULL) {
			this->root = NULL;
		}
		else
			if (parent->right == currentNode)
				parent->right = NULL;
			else
				parent->left = NULL;
		this->s -= 1;
		return true;
	}
	else {//the case when the node has one descendant
		if (currentNode->right == NULL) {
			BSTNode* child = currentNode->left;
			BSTNode* parent = this->parent(currentNode);
			if (parent == NULL){//this means that the node we want to delete is the root
				this->root = child;
				}
			else
				if (parent->right == currentNode)
					parent->right = child;
				else
					parent->left = child;
			this->s -= 1;
			return true;
		}
		else {
			if (currentNode->left == NULL) {
				BSTNode* child = currentNode->right;
				BSTNode* parent = this->parent(currentNode);
				if (parent == NULL){//this means that the node we want to delete is the root
					this->root = child;
					}
				else
					if (parent->right == currentNode)
						parent->right = child;
					else
						parent->left = child;
				this->s -= 1;
				return true;
			}
		}
	}
	//the case when the node has two descendants
	//find the successor of the node, move it to the node to be deleted and delete the successor
	BSTNode* nodeToDelete = currentNode;
	BSTNode* successor = this->successor(currentNode);
	//we remove the successor
	BSTNode* parent = this->parent(successor);
	if(parent!=NULL)
		if (parent->right == successor)
			if (successor->right != NULL)
				parent->right = successor->right;
			else
				parent->right = NULL;
		else
			if (successor->left != NULL)
				parent->left = successor->left;
			else
			parent->left = NULL;
	nodeToDelete->info = successor->info;
	this->s -= 1;
	return true;
}//O(n^2)

bool SortedBag::search(TComp e) const
{
	return this->searchRec(this->root,e);
}//O(h) where h is the height of the BST

bool SortedBag::searchRec(BSTNode* node,TComp e) const
{
	if (node == NULL)
		return false;
	else {
		if (node->info == e)
			return true;
		else {
			if (this->relation(node->info,e))
				this->searchRec(node->right, e);
			else
				this->searchRec(node->left, e);
		}
	}
}//O(h)

int SortedBag::nrOccurrences(TComp e) const
{
	int n = 0;
	auto currentNode = this->root;
	bool found = false;
	while (currentNode != NULL and found == false) {
		if (currentNode->info == e){
			found = true;
			n += 1;
			}
		else
			if (this->relation(currentNode->info, e))
				currentNode = currentNode->right;
			else
				currentNode = currentNode->left;
	}
	if (found == false) {//this means that the element does not exist
		return 0;
	}
	//else, further occurrences of the element are below it
	currentNode = currentNode->right;
	while (currentNode != NULL) {
		if (currentNode->info == e) {
			n += 1;
		}
		if (this->relation(currentNode->info, e))
			currentNode = currentNode->right;
		else
			currentNode = currentNode->left;
	}
	return n;
}
//O(h) where h is the height of the BST



int SortedBag::size() const
{
	return this->s;
}//theta(1)

SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}//O(n)

bool SortedBag::isEmpty() const
{
	return this->s==0;
}//theta(1)

void SortedBag::addOccurences(int nr, TComp elem)
{
	if (nr < 0)
		throw std::exception("");
	if (nr == 1) {
		this->add(elem);
		return;
	}
	BSTNode** nodes = new BSTNode*[nr];
	int i;
	nodes[0] = new BSTNode();
	for ( i = 0; i < nr-1; i++) {
		nodes[i]->info = elem;
		nodes[i]->left = NULL;
		nodes[i + 1] = new BSTNode();
		nodes[i]->right = nodes[i + 1];
	}
	nodes[i]->info = elem;
	BSTNode* current = this->root;
	BSTNode* previous = NULL;

	while (current != NULL) {
		previous = current;
		if (this->relation(current->info, elem))
			current = current->right;
		else
			current = current->left;
	}
	if (previous == NULL)
		this->root = nodes[0];
	else
		if (this->relation(previous->info, elem))
			previous->right = nodes[0];
		else
			previous->left = nodes[0];
	this->s += nr;
}//O(h+nr)

SortedBag::~SortedBag()
{
	std::stack<BSTNode*> stack;
	BSTNode* currentNode = this->root;
	while (currentNode != NULL) {
		stack.push(currentNode);
		currentNode = currentNode->left;
	}
	while (stack.size() != 0) {
		currentNode = stack.top();
		stack.pop();
		currentNode = currentNode->right;
		while (currentNode != NULL) {
			stack.push(currentNode);
			currentNode = currentNode->left;
		}
		delete currentNode;
	}
}//theta(n)
