//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.FindIf;

import Boost.TMP;

using namespace boost::tmp;

export namespace find_if_test {
	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	namespace tmp = boost::tmp;

	template <int X>
	struct equals_to {
		template <typename Y>
		using f = tmp::bool_<(Y::value == X)>;
	};

	using olist = list_<int_<1>, int_<1>, int_<1>, int_<1>, int_<1>, int_<1>, int_<1>, int_<1>, int_<2>>;
	using rlist = list_<int_<1>, int_<3>, int_<4>, int_<2>>;
	using alist = list_<list_<int_<1>, int_<3>>, list_<int_<1>, int_<2>>>;

	using new_list = call_<ui0_<>, alist>;

	using blist = list_<uint_<1>, uint_<1>>;

	int run() {
		sizet_<8>{} = call_<unpack_<find_if_<lift_<is_even>>>, olist>{};
		nothing_{} = call_<find_if_<lift_<is_even>>, int_<1>>{};

		sizet_<400>{} = call_<make_sequence_<identity_, find_if_<is_<sizet_<400>>>>, sizet_<500>>{};

		return 0;
	}
} // namespace find_if_test
