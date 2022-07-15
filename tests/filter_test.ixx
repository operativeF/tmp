//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Filter;

import Boost.TMP;

using namespace boost::tmp;

export namespace filter_test {
	template <typename T>
	using divide_by_two_celing = int_<((T::value >> 1) + (T::value & 1))>;
	template <typename T>
	using multiply_by_2 = uint_<(T::value << 1)>;

	template <typename N>
	using is_even = bool_<N::value % 2 == 0>;
	using xs0     = list_<int_<1>, int_<2>, int_<3>, int_<4>, int_<5>,
                           int_<6>, int_<7>, int_<8>, int_<9>, int_<10>>;
	using result0 = call_<unpack_<filter_<lift_<is_even>>>, xs0>;

	int run() {
		list_<int_<2>, int_<4>, int_<6>, int_<8>, int_<10>>{} =
		        call_<unpack_<filter_<lift_<is_even>>>, xs0>{};

		// using make_filtered_sequence = make_sequence_<identity_, filter_<lift_<is_even>>>;
		// using make_stride2_sequence =
		//        lift_<divide_by_two_celing, make_sequence_<lift_<multiply_by_2>>>;

		// call_<make_sequence_<make_algo<make_stride2_sequence>>, extent>{} =
		//        call_<make_sequence_<make_algo<make_filtered_sequence>>, extent>{};

		return 0;
	}
} // namespace filter_test
