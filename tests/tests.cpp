#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include <type_traits>

#include <doctest/doctest.h>
#include <zh/prism.hpp>

#include "traverse.hpp"

using base = std::vector<int>;
using zh::prism;
using zh::cprism;
using zh::fprism;
using zh::cfprism;

TEST_CASE("Unit.nop.prism") {
	using cont = prism<base, base::iterator, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<int&, decltype(prismed.front())>, "type of prism is not int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	rtraverse_and_compare(data, prismed);
	crtraverse_and_compare(data, prismed);
}

TEST_CASE("Unit.nop.cprism") {
	using cont = cprism<base, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<const int&, decltype(prismed.front())>, "type of prism is not const int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	rtraverse_and_compare(data, prismed);
	crtraverse_and_compare(data, prismed);
}

TEST_CASE("Unit.nop.fprism") {
	using cont = fprism<base, base::iterator, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<int&, decltype(prismed.front())>, "type of prism is not int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	//rtraverse_and_compare(data, prismed);
	//crtraverse_and_compare(data, prismed);
}

TEST_CASE("Unit.nop.cfprism") {
	using cont = cfprism<base, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<const int&, decltype(prismed.front())>, "type of prism is not cosnt int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	//rtraverse_and_compare(data, prismed);
	//crtraverse_and_compare(data, prismed);
}
