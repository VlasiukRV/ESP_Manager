/*
 * util.h
 *
 *  Created on: May 21, 2024
 *      Author: vlasi
 */

#ifndef COMPONENTS_UTIL_MATH_H_
#define COMPONENTS_UTIL_MATH_H_

namespace esp_util {

/*
 * Function returns the maximum of the two values.
 */

template<class T> const T& max(const T &a, const T &b) {
	return (a < b) ? b : a;     // or: return comp(a,b)?b:a; for version (2)
}

template<class T> T* strcpy(T *destination, const T *source) {
	T *start = destination; // Сохраняем начальный адрес назначения

	while (*source != '\0') {
		*destination = *source; // Копируем символ из source в destination
		++destination;
		++source;
	}

	*destination = '\0'; // Устанавливаем нулевой символ в конце строки
	return start; // Возвращаем начальный адрес назначения
}

template<class T> int strcmp(const T *str1, const T *str2) {
	while (*str1 && *str2 && *str1 == *str2) {
		++str1;
		++str2;
	}

	return *str1 - *str2;
}

}

#endif /* COMPONENTS_UTIL_MATH_H_ */
