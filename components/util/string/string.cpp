/*
 * string.cpp
 *
 *  Created on: Jun 5, 2024
 *      Author: vlasi
 */

#include "string.h"

namespace esp_util {

//  constructor that initializes from an array of char
String::String(char *init) {
//  find the length of the initializing array (look
//  for null byte)
	len = 0;
	while (init[len] != '\0')
		len++;

//  allocate space and copy chars into invoking obj
	theChars = new char[len];
	for (int i = 0; i < len; i++)
		theChars[i] = init[i];
}

//  copy constructor
String::String(const String &other) :
		len(other.len), theChars(nullptr) {
	if (other.theChars != nullptr) {
		theChars = new char[len + 1]; // Allocate memory for the new string
		esp_util::strcpy(theChars, other.theChars); // Copy the content of the other string
	}
}

//  destructor
String::~String() {
	if (len > 0)
		delete[] theChars;
}

//  concatenate the parm and the invoking String and
//  return the resulting String
String String::operator+(const String &two) const {
	String result;
	int i;

//  if both Strings are empty, result is empty too
	if (len == 0 && two.len == 0) {
		result.len = 0;
		result.theChars = nullptr;
	} else {

//  find length of the result and get space for it
		result.len = len + two.len;
		result.theChars = new char[result.len];

//  copy the invoking String into the new String
		for (i = 0; i < len; i++)
			result.theChars[i] = theChars[i];

//  copy the parm at the end of the new String
		int j = 0;
		while (j < two.len) {
			result.theChars[i] = two.theChars[j];
			i++;
			j++;
		}
	}
	return result;
}

//  return the character at the given position in the
//  parm ch. if position is invalid return false;
//  otherwise return true
int String::at(int position, char &ch) const {
	int returnCode = 0;
	if (position >= 0 && position < len) {
		ch = theChars[position];
		returnCode = 1;
	}
	return returnCode;
}

// Overloaded comparison operators
int operator==(char *str, const String &strObj) {
	return (esp_util::strcmp(str, strObj.theChars) == 0);
}

int operator==(const String &strObj1, const String &strObj2) {
	return (esp_util::strcmp(strObj1.theChars, strObj2.theChars) == 0);
}

int operator==(const String &strObj, char *str) {
	return (esp_util::strcmp(strObj.theChars, str) == 0);
}

//  copy the parm into the invoking object
String& String::operator=(const String &other) {
	if (this != &other) { // Check for self-assignment
		// Deallocate memory if the current string is not empty
		if (theChars != nullptr) {
			delete[] theChars;
			theChars = nullptr;
		}
		len = other.len; // Update the length
		if (other.theChars != nullptr) {
			theChars = new char[len + 1]; // Allocate memory for the new string
			esp_util::strcpy(theChars, other.theChars); // Copy the content of the other string
		}
	}
	return *this;
}

}
