//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/remove_if.hpp"

namespace remove_if_test {
	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	int run() {
		using alist = list_<uint_<0>, uint_<1>, uint_<2>, uint_<4>>;

		list_<uint_<1>>{} = call_<unpack_<remove_if_<lift_<is_even>>>, alist>{};

		return 0;
	}
} // namespace remove_if_test