
// COS30008, List, Problem Set 3, 2022

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>

using namespace std;

template<typename T>
class List
{
private:
    // auxiliary definition to simplify node usage
    using Node = DoublyLinkedList<T>;

    Node* fRoot;	// the first element in the list
    size_t fCount;	// number of elements in the list

public:
    // auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;

    ~List()                                                             // destructor - frees all nodes
    {
        while (fRoot != nullptr)
        {
            if (fRoot != &fRoot->getPrevious())                       // more than one element
            {
                Node* lTemp = const_cast<Node*>(&fRoot->getPrevious()); // select last

                lTemp->isolate();                                       // remove from list
                delete lTemp;                                           // free
            }
            else
            {
                delete fRoot;                                           // free last
                break;                                                  // stop loop
            }
        }
    }

    void remove(const T& aElement)	                                // remove first match from list
    {
        Node* lNode = fRoot;                                            // start at first

        while (lNode != nullptr)                                      // Are there still nodes available?
        {
            if (**lNode == aElement)                                  // Have we found the node?
            {
                break;                                                  // stop the search
            }

            if (lNode != &fRoot->getPrevious())                       // not reached last
            {
                lNode = const_cast<Node*>(&lNode->getNext());           // go to next
            }
            else
            {
                lNode = nullptr;                                        // stop search
            }
        }

        // At this point we have either reached the end or found the node.
        if (lNode != nullptr)                                         // We have found the node.
        {
            if (fCount != 1)                                          // not the last element
            {
                if (lNode == fRoot)
                {
                    fRoot = const_cast<Node*>(&fRoot->getNext());       // make next root
                }
            }
            else
            {
                fRoot = nullptr;                                        // list becomes empty
            }

            lNode->isolate();                                           // isolate node
            delete lNode;                                               // release node's memory
            fCount--;                                                   // decrement count
        }
    }

    //////////////////////////////////////////////////////////////////
    //// PS3
    //////////////////////////////////////////////////////////////////

    // P1

    List()                                      // default constructor
    {
        fRoot = nullptr;
        fCount = 0;
    }

    bool empty() const	                        // Is list empty?
    {
        if (fRoot == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    size_t size() const                		// list size
    {
        return fCount + 1;
    }

    void push_front(const T& aElement)	    // adds aElement at front
    {
        if (empty())
        {
            fRoot = new Node(aElement);
            return;
        }
        Node* insertNode = new Node(aElement);
        *fRoot->push_front(*insertNode);
        fRoot = insertNode;
        fCount++;
    }

    Iterator begin() const                     // return a forward iterator
    {
        Iterator iterate = fRoot;
        return iterate.begin();
    }

    Iterator end() const                       // return a forward end iterator
    {
        Iterator iterate = fRoot;
        return iterate.end();
    }

    Iterator rbegin() const                   // return a backwards iterator
    {
        Iterator iterate = fRoot;
        return iterate.rbegin();
    }

    Iterator rend() const                     // return a backwards end iterator
    {
        Iterator iterate = fRoot;
        return iterate.rend();
    }

    // P2

    void push_back(const T& aElement)        // adds aElement at back
    {
        if (empty())
        {
            fRoot = new Node(aElement);
            return;
        }
        Node* insNode = new Node(aElement);
        const_cast<Node*>(&fRoot->getPrevious())->push_back(*insNode);
        fCount++;
    }

    // P3

    const T& operator[](size_t aIndex) const	// list indexer
    {
        if (aIndex > fCount)
        {
            throw range_error("Invalid Index.");
        }

        Node* currNode = fRoot;
        int lCounter = 0;
        while (currNode != nullptr)
        {
            if (lCounter == aIndex)
            {
                return currNode->getPayload();
            }
            lCounter++;
            currNode = const_cast<Node*>(&currNode->getNext());
        }

    }

    // P4

    List(const List& aOtherList)             // copy constructor
    {
        fRoot = nullptr;
        fCount = 0;
        for (size_t i = 0; i < aOtherList.size(); i++)
        {
            push_back(aOtherList[i]);
        }
    }

    List& operator=(const List& aOtherList)	// assignment operator
    {
        for (size_t i = 0; i < size(); i++)
        {
            remove(operator[](i));
        }

        for (size_t i = 0; i < aOtherList.size(); i++)
        {
            push_back(aOtherList[i]);
        }
        return *this;
    }

    // P5

    List(List&& aOtherList)            		// move constructor
    {

    }
    List& operator=(List&& aOtherList)       // move assignment operator
    {

    }
    void push_front(T&& aElement)			// move push_front
    {

    }
    void push_back(T&& aElement)				// move push_back
    {

    }
};
