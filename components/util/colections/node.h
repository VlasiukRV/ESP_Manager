/*
 * node.h
 *
 *  Created on: May 27, 2024
 *      Author: vlasiuk
 */

#ifndef COMPONENTS_UTIL_COLECTIONS_NODE_H_
#define COMPONENTS_UTIL_COLECTIONS_NODE_H_

namespace esp_util {

/* This class provides basic functionality for node which used in LinkedList.
 It contains:
 - the node's data `data`,
 - a pointer to the next node `next`,
 - methods for accessing the data and setting the next node,
 */

template<typename Type>
class BaseNode {
protected:
	Type data;

public:
	// Constructor initializing the node's data and setting the next pointer to null
	BaseNode(const Type &data) :
			data(data) {
	}

	// Method to get the node's data
	Type getData() const {
		return data;
	}

	// Virtual destructor
	virtual ~BaseNode() {
	}
};

/*
 Class defines the basic structure of a singly linked list node.
 It contains a pointer to the next node and provides methods for getting and setting that pointer.
 */

template<typename Type>
class BaseLinkedListNode: public BaseNode<Type> {
protected:
	BaseNode<Type> *next; // Pointer to the next node

public:
	// Constructor initializing the node's data and setting the next pointer to null
	BaseLinkedListNode(const Type &data) :
			BaseNode<Type>(data), next(nullptr) {
	}

	// Method to get the pointer to the next node
	virtual BaseNode<Type>* getNext() {
		return next;
	}

	// Method to set the pointer to the next node
	void setNext(BaseNode<Type> *nextNode) {
		next = nextNode;
	}

	// Virtual destructor
	virtual ~BaseLinkedListNode() {
		this->next = nullptr;
	}
};

/*
 * This is a template class that inherits from BaseLinkedListNode<Type>.
 * It is used to store data of type Type.
 */

template<typename Type> class Node: public BaseLinkedListNode<Type> {

public:
	Node(const Type &data) :
			BaseLinkedListNode<Type>(data) {
	}

	virtual Node<Type>* getNext() override {
		return this->next;
	}

	virtual ~Node() {

	}
};

// end class Node

/*
 * This is a template class that inherits from BaseLinkedListNode<Type*>.
 * It is designed to store Type* pointers.
 */

template<typename Type> class Node<Type*> : public BaseLinkedListNode<Type*> {

public:
	Node(Type *data) :
			BaseLinkedListNode<Type*>(data) {
	}

	virtual Node<Type*>* getNext() override {
		return static_cast<Node<Type*>*>(this->next);
	}

	virtual ~Node() {
		if (this->data != nullptr) {
			delete this->data;
		}
	}

};

// end class Node

}

#endif /* COMPONENTS_UTIL_COLECTIONS_NODE_H_ */
