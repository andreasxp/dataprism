#include <gtest/gtest.h>
#include <vector>
#include <type_traits>

#include "prism.hpp"

#include "traverse.hpp"

using base = std::vector<int>;
using zh::prism;
using zh::cprism;
using zh::fprism;
using zh::cfprism;

TEST(dataprism_nop_test, prism) {
	using cont = prism<base, base::iterator, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<int&, decltype(prismed.front())>, "type of prism is not int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	rtraverse_and_compare(data, prismed);
	crtraverse_and_compare(data, prismed);
}

TEST(dataprism_nop_test, cprism) {
	using cont = cprism<base, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<const int&, decltype(prismed.front())>, "type of prism is not const int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	rtraverse_and_compare(data, prismed);
	crtraverse_and_compare(data, prismed);
}

TEST(dataprism_nop_test, fprism) {
	using cont = fprism<base, base::iterator, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<int&, decltype(prismed.front())>, "type of prism is not int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	//rtraverse_and_compare(data, prismed);
	//crtraverse_and_compare(data, prismed);
}

TEST(dataprism_nop_test, cfprism) {
	using cont = cfprism<base, base::const_iterator>;

	base data = {1, 2, 3, 4, 5};
	cont prismed(data);

	static_assert(std::is_same_v<const int&, decltype(prismed.front())>, "type of prism is not cosnt int&");

	traverse_and_compare(data, prismed);
	ctraverse_and_compare(data, prismed);
	//rtraverse_and_compare(data, prismed);
	//crtraverse_and_compare(data, prismed);
}

int main() {
	testing::InitGoogleTest();
	int result = RUN_ALL_TESTS();

	system("PAUSE");
	return result;
}