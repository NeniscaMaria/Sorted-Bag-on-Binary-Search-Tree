
#include "sortedBagIterator.h"
#include <iostream>
#include <stdexcept>
SortedBagIterator::SortedBagIterator(const SortedBag & c) :sortedBag(c)
{
//we need to find the minimum element
	auto current = this->sortedBag.root;
	this->minimum = NULL;
	if (current == NULL)
		//empty tree,no minimum
		this->currentNode = NULL;
	else {
		if (!this->sortedBag.relation(this->sortedBag.root->info, current->info)) {
			while (current->left->left != NULL)
				current = current->left;
			this->currentNode = current;
			this->minimum = current;
		}
		else {
			if(current->right!=NULL)
				while (current->right->right != NULL)
					current = current->right;
			this->currentNode = current;
			this->minimum = current;
		}
	}

}//O(n)

void SortedBagIterator::first()
{
	this->currentNode = this->minimum;
}//theta(1)


void SortedBagIterator::next()
{
	if (!this->valid())
		throw std::exception("");
	if (this->currentNode->right != NULL) {
		auto c = this->currentNode->right;
		while (c->left != NULL)
			c = c->left;
		this->currentNode = c;
	}
	else {
		auto c = this->currentNode;
		auto p = this->parentOfNode(c);
		while (p != NULL and p->left != c) {
			c = p;
			p = this->parentOfNode(p);
		}
		this->currentNode = p;
	}
}//O(n)

bool SortedBagIterator::valid() const
{
	return this->currentNode!=NULL;
}//theta(1)

TComp SortedBagIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception("");
	return this->currentNode->info;
}//theta(1)

BSTNode * SortedBagIterator::parentOfNode(BSTNode* node)
{
	BSTNode* c = this->sortedBag.root;
	if (c == node)
		return NULL;
	else {
		while (c != NULL and c->left != node and c->right != node) {
			if (!this->sortedBag.relation(c->info, node->info))
				c = c->left;
			else
				c = c->right;
		}
		return c;
	}
}//O(n)

