#include <iostream>
#include <string>
#include <stdexcept>
#include "HybridList.h"
using namespace std;

HybridList::HybridList() {}

HybridList::HybridList(int blockSize) {
	if (blockSize <= 0)
		throw out_of_range("Invalid block size " + to_string(blockSize));
	this->blockSize = blockSize;
}

HybridList::HybridList(const HybridList &h)
{
    blockSize = h.blockSize;
    numElements = h.numElements;
    numBlocks = h.numBlocks;

    head = new HybridListNode(*h.head);

    HybridListNode* currNewNode = head;
    HybridListNode* currCopyNode = h.head;

    while (currCopyNode->next != nullptr)
    {
        currNewNode->next = new HybridListNode(*(currCopyNode->next));
        currNewNode = currNewNode->next;
        currCopyNode = currCopyNode->next;
    }
}

HybridList::~HybridList() {
	clear();
}

int HybridList::size() const {
	return numElements;
}

int HybridList::capacity() const {
	return numBlocks * blockSize;
}

int HybridList::block_size() const {
	return blockSize;
}

HybridListNode* HybridList::front() const {
	return head;
}

HybridListNode* HybridList::back() const {
	return tail;
}

double& HybridList::at(int index) const {
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			return curNode->at(index - elementsSearched);
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}

	// Iterator went beyond last block so something went horribly wrong
	abort();
}

HybridList &HybridList::operator=(const HybridList &h)
{
    clear();

    blockSize = h.blockSize;
    numElements = h.numElements;
    numBlocks = h.numBlocks;

    head = new HybridListNode(*h.head);

    HybridListNode* currNewNode = head;
    HybridListNode* currCopyNode = h.head;

    while (currCopyNode != nullptr)
    {
        currNewNode->next = new HybridListNode(*(currCopyNode->next));
        currNewNode = currNewNode->next;
        currCopyNode = currCopyNode->next;
    }

    return *this;
}

void HybridList::push_back(double value) {
	if (numBlocks == 0) {
		// Hybrid list is empty so creating a new node that will be both the head
		// and tail and append the element to it
		HybridListNode* newTail = new HybridListNode(blockSize);
		newTail->push_back(value);
		tail = newTail;
		head = newTail;
		numBlocks = 1;
	}
	else if (tail->size() == blockSize) {
		// Tail node is full so create a new tail node and copy the back half of
		// the old tail node to the new tail node
		HybridListNode* newTail = new HybridListNode(blockSize);

		// Copy just under half of elements from old tail to new tail
		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newTail->push_back(tail->at(i));
		tail->resize(blockSize / 2 + 1);
		//cout << tail->size() << endl;
		// Append new item to new tail
		newTail->push_back(value);
		tail->next = newTail;
		//cout << newTail->size() << endl;
		//cout << "Tail: " << tail << endl;
		//cout << "New tail: " << newTail << endl;
		tail = newTail;
		numBlocks++;
	}
	else
		tail->push_back(value);	// Tail isn't full so just append to tail
	
	numElements++;
}

void HybridList::pop_back()
{
    if (numElements == 0)
    {
        throw out_of_range("Incapable of executing pop_back() on empty list.");
    }

    tail->pop_back();

    if (tail->size() == 0)
    {
        if (numBlocks == 1)
        {
            delete head;
            head = tail = nullptr;
            numElements = numBlocks = 0;

            return;
        }

        HybridListNode *newTail = head;

        while (newTail->next->next != nullptr)
        {
            newTail = newTail->next;
        }

        delete newTail->next;
		newTail->next = nullptr;
        tail = newTail;
        numBlocks--;
    }

    numElements--;
}

void HybridList::insert(int index, double value)
{
    HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index <= elementsSearched + curNode->size()) {
			break;
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
    }

	if (curNode->size() == blockSize) {
		HybridListNode* newNode = new HybridListNode(blockSize);

		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newNode->push_back(curNode->at(i));
        
		curNode->resize(blockSize / 2 + 1);
		
		if (blockSize <= 2)
		{
			newNode->push_back(value);
		}
		else if (index - elementsSearched > curNode->size())
		{
			if (index - elementsSearched - curNode->size() == newNode->size())
			{
				newNode->push_back(value);
			}
			else
			{
				newNode->insert(index - elementsSearched - curNode->size(), value);
			}
		}
		else if (index - elementsSearched == curNode->size())
		{
			curNode->push_back(value);
		}
		else
		{
			curNode->insert(index - elementsSearched, value);
		}

        newNode->next = curNode->next;
		curNode->next = newNode;
		
		numBlocks++;
	}
	else
	{
		if (index - elementsSearched == curNode->size())
		{
			curNode->push_back(value);
		}
		else
		{
			curNode->insert(index - elementsSearched, value);
		}
	}
    
    numElements++;
}

void HybridList::erase(int index)
{
    HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			curNode->erase(index - elementsSearched);
            
            if (curNode->size() == 0)
            {
                if (numBlocks == 1)
                {
                    delete curNode;
                    head = tail = nullptr;
                    numElements = numBlocks = 0;

                    return;
                }

                if (curNode == head)
                {
                    head = curNode->next;
                    delete curNode;
                }
                else if (curNode == tail)
                {
                    HybridListNode* newTail = head;

                    while (newTail->next != tail)
                    {
                        newTail = newTail->next;
                    }

                    delete tail;
                    tail = newTail;
                }
                else
                {
                    HybridListNode* prevNode = head;

                    while (prevNode->next != curNode)
                    {
                        prevNode = prevNode->next;
                    }

                    prevNode->next = curNode->next;

                    delete curNode;
                }

                numBlocks--;
            }

            numElements--;

            return;
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}
}

void HybridList::clear()
{
    HybridListNode* curNode = head, * nextNode = nullptr;
	// Iterate through each node starting from the head and delete it
	while (curNode != nullptr) {
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	head = tail = nullptr;
	numElements = numBlocks = 0;
}
