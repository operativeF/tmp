//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Logic;

import Boost.TMP;

namespace logic_test {
	using namespace boost::tmp;

	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	export int run() {
		false_{} = call_<and_<lift_<is_even>>, int_<1>, int_<1>, int_<1>, int_<1>, int_<1>,
		                       int_<1>, int_<1>, int_<1>, int_<1>>{};

		true_{} = call_<and_<lift_<is_even>>, int_<2>, int_<2>, int_<2>>{};

		false_{} = call_<or_<lift_<is_even>>, int_<1>, int_<1>, int_<1>, int_<1>, int_<1>,
		                       int_<1>, int_<1>, int_<1>, int_<1>>{};

		true_{} = call_<or_<lift_<is_even>>, int_<2>, int_<2>, int_<2>>{};

		return 0;
	}
} // namespace logic_test
