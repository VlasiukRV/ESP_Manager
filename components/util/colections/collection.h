/*
 * colection.h
 *
 *  Created on: Sep 27, 2023
 *      Author: TSB
 */
#pragma once

#ifndef INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_COLECTION_H_
#define INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_COLECTION_H_

#include "node.h"

namespace esp_util {

/*
 * Defines base template classes - interface for the iterator.
 */

template<typename Type> class Iterator {
public:
	virtual ~Iterator() {
	}
	;
	virtual void begin();
	virtual bool has_more();
	virtual void get_next();
	virtual Type current();
};

// end class Iterator

/*
 * Defines base template classes which represents the base class for collections such as lists, arrays, etc.
 */

template<typename Type> class Collection {
protected:
	int length;
public:
	Collection() :
			length(0) {
	}
	;
	virtual ~Collection() {
	}
	;
	int size() {
		return length;
	}
	;
	virtual bool add(const Type &val);
	Iterator<Type>* create_iterator();
	virtual void process_list(void (*func)(Type *val));

};

// end class Collection

}

#endif /* INCLUDE_SIMPLEOBJECTLIB_COLECTIONS_COLECTION_H_ */
