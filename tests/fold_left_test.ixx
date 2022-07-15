//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.FoldLeft;

import Boost.TMP;

using namespace boost::tmp;

export namespace fold_left_test {
	template <typename T, typename U>
	using add = uint_<(T::value + U::value)>;
	template <typename T, typename U>
	using push = call_<join_<>, T, list_<U>>;
	int run() {
		list_<>{}                   = call_<fold_left_<lift_<push>>, list_<>>{};
		list_<uint_<1>, uint_<2>>{} = call_<fold_left_<lift_<push>>, list_<>, uint_<1>, uint_<2>>{};
		list_<uint_<1>, uint_<2>, uint_<3>>{} =
		        call_<fold_left_<lift_<push>>, list_<>, uint_<1>, uint_<2>, uint_<3>>{};
		list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>>{} =
		        call_<fold_left_<lift_<push>>, list_<>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>{};
		list_<uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>,
		      uint_<1>, uint_<1>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>{} =
		        call_<fold_left_<lift_<push>>, list_<>, uint_<1>, uint_<1>, uint_<1>, uint_<1>,
		              uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>,
		              uint_<2>, uint_<3>, uint_<4>>{};
		uint_<1>{}  = call_<fold_left_<lift_<add>>, uint_<1>>{};
		uint_<3>{}  = call_<fold_left_<lift_<add>>, uint_<1>, uint_<2>>{};
		uint_<6>{}  = call_<fold_left_<lift_<add>>, uint_<1>, uint_<2>, uint_<3>>{};
		uint_<10>{} = call_<fold_left_<lift_<add>>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>{};
		uint_<20>{} = call_<fold_left_<lift_<add>>, uint_<1>, uint_<1>, uint_<1>, uint_<1>,
		                    uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>, uint_<1>,
		                    uint_<2>, uint_<3>, uint_<4>>{};

		return 0;
	}
} // namespace fold_left_test
