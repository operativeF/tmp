//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Join;

import Boost.TMP;
import std.core;

using namespace boost::tmp;

export namespace join_test {
	using joined_sequences = call_<join_seq_<lift_<into_sequence>>, std::index_sequence<1, 2>, std::index_sequence<3, 4>>;
	int run() {
		// using make_listified_sequence = make_sequence_<listify_, push_front_<list_<>, join_<>>>;
		// call_<make_sequence_<make_algo<make_sequence_<>>>, extent>{} =
		//        call_<make_sequence_<make_algo<make_listified_sequence>>, extent>{};
		joined_sequences{} = std::index_sequence<1, 2, 3, 4>{};
		return 0;
	}
} // namespace join_test
