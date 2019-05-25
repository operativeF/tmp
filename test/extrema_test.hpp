//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include "test_util.hpp"

namespace extrema_test {
    using alist = list_<uint_<6>, uint_<5>, uint_<11>>;
	using blist = list_<uint_<11>, uint_<6>, uint_<5>>;
	using clist = list_<uint_<5>, uint_<11>, uint_<6>, uint_<1>>;
	using dlist = list_<uint_<5>, uint_<70>, uint_<61>, uint_<1>>;

	int run() {
    	uint_<5>{} = call_<unpack_<min_element_<>>, alist>{};
    	uint_<5>{} = call_<unpack_<min_element_<>>, blist>{};
    	uint_<11>{} = call_<unpack_<max_element_<>>, clist>{};
    	uint_<11>{} = call_<unpack_<max_element_<>>, alist>{};
    	uint_<70>{} = call_<unpack_<max_element_<>>, dlist>{};

		return 0;
	}
} // namespace extrema_test
