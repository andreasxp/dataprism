#pragma once
#include <type_traits>
#include <iterator>
#include <cstddef>

#include <zh/type_traits.hpp>

namespace zh {

// Iterator ============================================================================================================
template<class Iter>
class ifce {
	static_assert(std::is_base_of_v<ifce, Iter>, "Iter must be the class that inherits proxy");

protected:
	Iter& iter() noexcept;
	const Iter& iter() const noexcept;

public:
	decltype(auto) operator*() const noexcept;
	decltype(auto) operator++() noexcept;
};

// Input iterator ======================================================================================================
template<class Iter>
class input_ifce : public ifce<Iter> {
	static_assert(std::is_base_of_v<input_ifce, Iter>, "Iter must be the class that inherits proxy");

public:
	decltype(auto) operator++(int) noexcept;
	decltype(auto) operator->() const noexcept;
};

template<class Iter> bool operator==(const input_ifce<Iter>& lhs, const input_ifce<Iter>& rhs);
template<class Iter> bool operator!=(const input_ifce<Iter>& lhs, const input_ifce<Iter>& rhs);

// Forward iterator ====================================================================================================
template<class Iter>
class forward_ifce : public input_ifce<Iter> {
	static_assert(std::is_base_of_v<forward_ifce, Iter>, "Iter must be the class that inherits proxy");

};

// Bidirectional iterator ==============================================================================================
template<class Iter>
class bidirectional_ifce : public forward_ifce<Iter> {
	static_assert(std::is_base_of_v<bidirectional_ifce, Iter>, "Iter must be the class that inherits proxy");

public:
	decltype(auto) operator--() noexcept;
	decltype(auto) operator--(int) noexcept;
};

// Random access iterator ==============================================================================================
template<class Iter>
class random_access_ifce : public bidirectional_ifce<Iter> {
	static_assert(std::is_base_of_v<random_access_ifce, Iter>, "Iter must be the class that inherits proxy");

public:
	template<class D> decltype(auto) operator+=(D offset) noexcept;
	template<class D> decltype(auto) operator-=(D offset) noexcept;
	
	template<class D> decltype(auto) operator[](D offset) const noexcept;
};

template<class Iter, class D> decltype(auto) operator+(random_access_ifce<Iter> lhs, D rhs) noexcept;
template<class Iter, class D> decltype(auto) operator+(D lhs, random_access_ifce<Iter> rhs) noexcept;

template<class Iter, class D> decltype(auto) operator-(random_access_ifce<Iter> lhs, D rhs) noexcept;
template<class Iter> decltype(auto) operator-(
	random_access_ifce<Iter> lhs, 
	const random_access_ifce<Iter>& rhs) noexcept;

template<class Iter> bool operator< (const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs);
template<class Iter> bool operator> (const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs);
template<class Iter> bool operator<=(const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs);
template<class Iter> bool operator>=(const random_access_ifce<Iter>& lhs, const random_access_ifce<Iter>& rhs);

} // namespace zh

#include "iterator.inl"