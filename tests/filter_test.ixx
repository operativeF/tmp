//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Filter;

import Boost.TMP;

using namespace boost::tmp;

template <typename N>
using is_even = bool_<N::value % 2 == 0>;
using xs0     = list_<int_<1>, int_<2>, int_<3>, int_<4>, int_<5>,
						int_<6>, int_<7>, int_<8>, int_<9>, int_<10>>;

export namespace filter_test {
	int run() {
		list_<int_<2>, int_<4>, int_<6>, int_<8>, int_<10>>{} =
		        call_<unpack_<filter_<lift_<is_even>>>, xs0>{};
		return 0;
	}
} // namespace filter_test
