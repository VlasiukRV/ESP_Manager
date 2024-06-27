#pragma once

#ifndef INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_LINKEDLIST_H_
#define INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_LINKEDLIST_H_

#include "collection.h"

namespace esp_util {

template<class Type> class IteratorLinkedList;

/*
 * Implements the structure of a singly linked list.
 */

template<class Type> class LinkedList: public Collection<Type> {
	friend class IteratorLinkedList<Type> ;

private:

	Node<Type> *head { nullptr };
	Node<Type> *tail { nullptr };

	void append(Node<Type> *newNode) {

		//when list empty
		if (this->length == 0) {
			head = newNode;
			tail = newNode;
			this->length = 1;
		} else {
			tail->setNext(newNode);
			tail = newNode;
			this->length++;
		}
	}
	void _push(Node<Type> *newNode) {

		//when list empty
		if (this->length == 0) {
			head = newNode;
			tail = newNode;
			this->length = 1;
		} else {
			newNode->setNext(head);
			head = newNode;
			this->length++;
		}

	}

public:
	LinkedList() :
			head(nullptr), tail(nullptr) {

	}

	LinkedList(const Type &val) {
		add(val);
	}

	bool add(const Type &val) override {

		auto *temp = new Node<Type> { val };
		this->append(temp);
		temp = nullptr;

		return true;

	}
	//inserts a new node with the data passed to the beginning of the list (new head)
	void push(const Type &val) {

		auto *temp = new Node<Type> { val };
		this->_push(temp);
		temp = nullptr;

	}

	//removes the first node of the list
	bool pop() {

		if (head == nullptr && tail == nullptr) {
			return true;
		} else {

			Node<Type> *trav { nullptr };
			trav = head;
			while (trav->next != tail) {
				trav = trav->next;
			}
			trav->next = nullptr;
			delete tail;
			tail = trav;
			this->length--;

		}

		return true;

	}

	//removes the last node of the list
	bool pull() {
		if (head == nullptr && tail == nullptr) {
			return true;
		} else {
			Node<Type> *temp = head;
			head = head->getNext();
			temp->setNext(nullptr);
			delete temp;
			temp = nullptr;
			this->length--;
		}

		return true;
	}

	void clear() {
		Node<Type> *current = head;
		while (current != nullptr) {
			Node<Type> *next = current->getNext();
			current->setNext(nullptr);
			delete current;
			current = next;
			next = nullptr;
		}
	}

	Node<Type>* getHead() {

		return head;

	}

	Type getHeadElement() {

		return head->getData();

	}

	Type getTailElement() {

		return tail->getData();

	}

	void process_list(void (*func)(Type *val)) override {
		Node<Type> *current = head;
		while (current != nullptr) {
			Type data = current->getData();
			func(&data);
			current = current->getNext();
		}

	}

	Iterator<Type>* create_iterator() {

		return new IteratorLinkedList<Type>(this);

	}

	~LinkedList() {
		this->clear();
	}

};

/*
 * The class implements an iterator for the LinkedList.
 */

template<typename Type> class IteratorLinkedList: public Iterator<Type> {
public:

	IteratorLinkedList() {
		this->container = nullptr;
		this->corent_node = nullptr;
	}

	IteratorLinkedList(LinkedList<Type> *container) {
		this->container = container;
		this->corent_node = container->getHead();
	}

	~IteratorLinkedList() {
		//delete container;
		//delete corent_node;
	}

	void begin() override {
		if (this->container == nullptr) {
			return;
		}

		this->corent_node = container->getHead();
	}

	bool has_more() override {
		return (this->corent_node != nullptr);
	}

	void get_next() override {
		if (this->corent_node == nullptr) {
			return;
		}

		this->corent_node = this->corent_node->getNext();
	}

	Type current() override {
		if (this->corent_node == nullptr) {
			return nullptr;
		}

		return this->corent_node->getData();
	}

protected:
	LinkedList<Type> *container;
	Node<Type> *corent_node;
};

}

#endif /* INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_LINKEDLIST_H_ */
