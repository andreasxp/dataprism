#include <iostream>
#include <vector>
#include <boost/iterator/iterator_adaptor.hpp>
#include "zh/prism.hpp"

using namespace zh;

int main() {
	using base = std::vector<int>;
	using cont = prism<base, base::iterator, base::const_iterator>;
	using ccont = cprism<base, base::const_iterator>;
	using fcont = fprism<base, base::iterator, base::const_iterator>;
	using cfcont = cfprism<base, base::const_iterator>;

	base v = {1, 2, 3, 4, 5, 6};
	cont vv(v);
	ccont& c = vv;
	fcont& f = vv;
	cfcont& cf = vv;
	ccont* cp = &vv;
	//fcont* fp = &vv;
	cfcont* cfp = &vv;

	for (auto i : vv) {
		std::cout << i << std::endl;
	}
}