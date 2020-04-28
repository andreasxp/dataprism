#pragma once
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include "iterator.hpp"

namespace zh {

template<class... Args>
void print(Args&&... args) {
	(std::cout << ... << args);
}

template<class... Args>
void runtime_assert(bool cond, Args&&... args) {
	#ifndef NDEBUG
	if (!cond) {
		print(std::forward<Args>(args)...);
		std::abort();
	}
	#endif
}

// Iterator ============================================================================================================
template<class Iter>
Iter& ifce<Iter>::iter() noexcept {
	// Implementation requirement
	runtime_assert(typeid(*this) == typeid(Iter), "iterator must directly inherit from the proxy base");

	// LegacyIterator requirements
	static_assert(std::is_copy_constructible_v<Iter>, "iterator must be copy-constructible");
	static_assert(std::is_copy_assignable_v<Iter>, "iterator must be copy-assignable");
	static_assert(std::is_destructible_v<Iter>, "iterator must be destructible");
	static_assert(std::is_swappable_v<Iter>, "iterator must be destructible");
	static_assert(std::is_swappable_v<Iter>, "iterator must be destructible");

	return *static_cast<Iter*>(this);
}

template<class Iter>
const Iter& ifce<Iter>::iter() const noexcept {
	return static_cast<const Iter&>(*this);
}

template<class Iter>
decltype(auto) ifce<Iter>::operator*() const noexcept {
	return iter().dereference();
}

template<class Iter>
decltype(auto) ifce<Iter>::operator++() noexcept {
	iter().increment();
	return iter();
}

// Input iterator ======================================================================================================
template<class Iter>
decltype(auto) input_ifce<Iter>::operator++(int) noexcept {
	input_ifce tmp(*this);
    operator++();
    return tmp.iter();
}

template<class Iter>
decltype(auto) input_ifce<Iter>::operator->() const noexcept {
	return &*(*this);
}

template<class Iter>
bool operator==(const input_ifce<Iter>& lhs, const input_ifce<Iter>& rhs) {
	return lhs.equal(rhs);
}

template<class Iter> 
bool operator!=(const input_ifce<Iter>& lhs, const input_ifce<Iter>& rhs) {
	return !lhs.equal(rhs);
}

// Forward iterator ====================================================================================================
// Bidirectional iterator ==============================================================================================
template<class Iter>
decltype(auto) bidirectional_ifce<Iter>::operator--() noexcept {
	this->iter().decrement();
	return this->iter();
}

template<class Iter>
decltype(auto) bidirectional_ifce<Iter>::operator--(int) noexcept {
	bidirectional_ifce tmp(*this);
    operator--();
    return tmp.iter();
}

// Random access iterator ==============================================================================================
template<class Iter>
template<class D>
decltype(auto) random_access_ifce<Iter>::operator+=(D offset) noexcept {
	this->iter().advance(offset);
	return this->iter();
}

template<class Iter>
template<class D>
decltype(auto) random_access_ifce<Iter>::operator-=(D offset) noexcept {
	this->iter().advance(-offset);
	return this->iter();
}

template<class Iter>
template<class D>
decltype(auto) random_access_ifce<Iter>::operator[](D offset) const noexcept {
	Iter tmp = this->iter();
	tmp += offset;
	return *tmp;
}

template<class Iter, class D>
decltype(auto) operator+(random_access_ifce<Iter> lhs, D rhs) noexcept {
	lhs += rhs;
	return lhs;
}

template<class Iter, class D>
decltype(auto) operator+(D lhs, random_access_ifce<Iter> rhs) noexcept{
	rhs += lhs;
	return rhs;
}

template<class Iter, class D>
decltype(auto) operator-(random_access_ifce<Iter> lhs, D rhs) noexcept {
	lhs -= rhs;
	return lhs;
}

template<class Iter>
decltype(auto) operator-(const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs) noexcept {
	return rhs.distance_to(lhs);
}

template<class Iter>
bool operator< (const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs) {
	return lhs.distance_to(rhs) > 0;
}

template<class Iter>
bool operator> (const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs) {
	return lhs.distance_to(rhs) < 0;
}

template<class Iter>
bool operator<=(const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs) {
	return lhs.distance_to(rhs) >= 0;
}

template<class Iter>
bool operator>=(const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs) {
	return lhs.distance_to(rhs) <= 0;
}

} // namespace zh