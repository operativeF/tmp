//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Partition;

import Boost.TMP;

namespace partition_test {
	using namespace boost::tmp;

	template <typename T>
	using greater_than_two = bool_<(T::value > 2)>;

	export int run() {
		list_<list_<int_<1>, int_<2>>, list_<int_<3>, int_<4>>>{} =
			call_<partition_<lift_<greater_than_two>>, int_<1>, int_<2>, int_<3>, int_<4>>{};
		return 0;
	}
} // namespace partition_test
