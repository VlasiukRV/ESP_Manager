/*
 * arrayList.h
 *
 *  Created on: Apr 17, 2024
 *      Author: vlasi
 */

#ifndef INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_ARRAYLIST_H_
#define INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_ARRAYLIST_H_

#include "collection.h"
#include "math.h"

namespace esp_util {

template<typename Type> class IteratorArrayList;

/*
 * Defines a template class ArrayList, which is a subclass of the Collection<Type> class.
 * This class is a dynamic array that can change its size as needed.
 */

template<typename Type> class ArrayList: public Collection<Type> {
	friend class IteratorArrayList<Type> ;

public:
	ArrayList() :
			capacity(0), data(nullptr) {

	}

	ArrayList(const ArrayList<Type> &a) {
		this->length = a.size();
		capacity = this->size();
		data = nullptr;
		if (this->size() != 0)
			data = new Type[this->size()];
		else
			data = 0;
		for (int i = 0; i < this->size(); ++i)
			data[i] = a.data[i];
	}

	ArrayList(int size) {
		this->length = size;
		capacity = size;
		if (size != 0)
			data = new Type[size];
		else
			data = nullptr;
	}

	~ArrayList() {
		if (data)
			delete[] data;
	}

	void trim_to_size() {
		resize(this->size(), this->size());
	}

	bool add(const Type &val) override {

		resize(this->size() + 1);
		data[this->size() - 1] = val;
		return true;

	}

	Type& get(int i) {
		return data[i];
	}

	Type& operator[](int i) {
		return data[i];
	}

	void process_list(void (*func)(Type *val)) override {

		for (int i = 0; i < this->size(); ++i) {
			func(&data[i]);
		}

	}

private:
	int capacity;
	Type *data;

	void resize(int size, int new_capacity) {

		if (size > capacity
				|| (new_capacity != capacity && new_capacity > this->size())) {

			Type *new_data = new Type[new_capacity];
			for (int i = 0; i < this->size(); ++i)
				new_data[i] = data[i];
			delete[] data;
			data = new_data;
			capacity = new_capacity;

		}

		this->length = size;

	}

	int resize(int size) {

		int new_capacity = this->size();
		if (size > capacity) {
			new_capacity = max(size, this->size() * 2);
		}

		resize(size, new_capacity);

		return capacity;
	}

};

}

#endif /* INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_ARRAYLIST_H_ */
