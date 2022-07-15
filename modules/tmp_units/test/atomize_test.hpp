//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include "test_util.hpp"

namespace atomize_test {
	namespace tmp = boost::tmp;

    template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

    using alist = list_<uint_<2>, uint_<100>, uint_<4>, uint_<500>>;

	int run() {

        return 0;
	}
} // namespace any_of_test