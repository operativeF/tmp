//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include "test_util.hpp"

namespace replace_if_test {
	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	int run() {
		using alist = list_<uint_<0>, uint_<1>>;
		using blist = call_<unpack_<replace_if_<uint_<1>, lift_<is_even>>>, alist>;

		list_<uint_<1>, uint_<1>>{} = blist{};

		return 0;
	}
} // namespace replace_if_test