//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include "test_util.hpp"

namespace size_test {
	int run() {
		using alist = list_<uint_<0>, uint_<2>, uint_<4>>;

		uint_<3>{} = call_<unpack_<size_<>>, alist>{};

		return 0;
	}
} // namespace size_test