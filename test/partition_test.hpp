//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/partition.hpp"

namespace partition_test
{
	using xs0 = list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<5>, uint_<6>, uint_<7>, uint_<8>, uint_<9>, uint_<10>>;

	template <typename T>
	using more_than_5 = bool_<(T::value > 5)>;

	using result0 = call_<unpack_<partition_<lift_<more_than_5>>>, xs0>;
	
	int run() {
		list_<
			list_<uint_<6>, uint_<7>, uint_<8>, uint_<9>, uint_<10>>,
			list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<5>>>{} = result0{};
		return 0;
	}
} // namespace partition_test