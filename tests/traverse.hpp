#pragma once
#include <utility>
#include <iterator>

#include <doctest/doctest.h>

struct nop_cls {
	template<class T>
	decltype(auto) operator()(T&& val) {
		return std::forward<T>(val);
	}
};
inline nop_cls nop;

template<class T, class U, class ConvertTU>
void traverse_and_compare(T&& data1, U&& data2, ConvertTU&& conv) {
	REQUIRE(
		std::distance(data1.begin(), data1.end()) ==
		std::distance(data2.begin(), data2.end())
	);

	auto it1 = data1.begin();
	auto it2 = data2.begin();
	while(it1 != data1.end()) {
		REQUIRE(conv(*it1) == *it2);

		++it1;
		++it2;
	}
}

template<class T, class U>
void traverse_and_compare(T&& data1, U&& data2) {
	traverse_and_compare(std::forward<T>(data1), std::forward<U>(data2), nop);
}

template<class T, class U, class ConvertTU>
void ctraverse_and_compare(T&& data1, U&& data2, ConvertTU&& conv) {
	REQUIRE(
		std::distance(data1.cbegin(), data1.cend()) ==
		std::distance(data2.cbegin(), data2.cend())
	);

	auto it1 = data1.cbegin();
	auto it2 = data2.cbegin();
	while(it1 != data1.cend()) {
		REQUIRE(conv(*it1) == *it2);

		++it1;
		++it2;
	}
}

template<class T, class U>
void ctraverse_and_compare(T&& data1, U&& data2) {
	ctraverse_and_compare(std::forward<T>(data1), std::forward<U>(data2), nop);
}

template<class T, class U, class ConvertTU>
void rtraverse_and_compare(T&& data1, U&& data2, ConvertTU&& conv) {
	REQUIRE(
		std::distance(data1.rbegin(), data1.rend()) ==
		std::distance(data2.rbegin(), data2.rend())
	);

	auto it1 = data1.rbegin();
	auto it2 = data2.rbegin();
	while(it1 != data1.rend()) {
		REQUIRE(conv(*it1) == *it2);

		++it1;
		++it2;
	}
}

template<class T, class U>
void rtraverse_and_compare(T&& data1, U&& data2) {
	rtraverse_and_compare(std::forward<T>(data1), std::forward<U>(data2), nop);
}

template<class T, class U, class ConvertTU>
void crtraverse_and_compare(T&& data1, U&& data2, ConvertTU&& conv) {
	REQUIRE(
		std::distance(data1.crbegin(), data1.crend()) ==
		std::distance(data2.crbegin(), data2.crend())
	);

	auto it1 = data1.crbegin();
	auto it2 = data2.crbegin();
	while(it1 != data1.crend()) {
		REQUIRE(conv(*it1) == *it2);

		++it1;
		++it2;
	}
}

template<class T, class U>
void crtraverse_and_compare(T&& data1, U&& data2) {
	crtraverse_and_compare(std::forward<T>(data1), std::forward<U>(data2), nop);
}