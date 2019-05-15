//  Copyright 2018-2019 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/algorithm/count_if.hpp>
#include "test_util.hpp"

namespace count_if_test {
	template <typename T>
	using divide_by_two_celing = int_<((T::value >> 1) + (T::value & 1))>;
	template <typename T>
	using multiply_by_2 = uint_<(T::value << 1)>;

	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;
	int run() {

		uint_<0>{} = call_<count_if_<lift_<is_even>>, int_<1>>{};
		uint_<1>{} = call_<count_if_<lift_<is_even>>, int_<2>>{};
		uint_<0>{} = call_<count_if_<lift_<is_even>>, int_<1>, int_<1>, int_<1>>{};

		return 0;
	}
} // namespace count_if_test