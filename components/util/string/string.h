/*
 * string.h
 *
 *  Created on: May 11, 2024
 *      Author: vlasi
 */

#ifndef INCLUDE_SIMPLEOBJECTLIB_STRING_H_
#define INCLUDE_SIMPLEOBJECTLIB_STRING_H_

#include "math.h"

namespace esp_util {

/*
 * Provides basic functionality for working with strings, including construction, access, modification, and comparison operations.
 */

class String {
	friend int operator==(char*, const String&);
	friend int operator==(const String&, const String&);
	friend int operator==(const String&, char*);
private:
	int len { 0 };
	char *theChars { nullptr };

public:
	// constructors and destructor
	String() :
			len(0), theChars(nullptr) {
	}
	String(char*);
	String(const String&);
	~String();
	//  accessors
	int length() const {
		return len;
	}
	int at(int, char&) const;
	int find(char) const;
	int substring(String&, int, int) const;
	String operator+(const String&) const;
	//  mutators
	String& operator=(const String&);

};

}

#endif /* INCLUDE_SIMPLEOBJECTLIB_STRING_H_ */
