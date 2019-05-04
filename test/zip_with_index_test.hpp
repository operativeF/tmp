//  Copyright 2018-2019 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "test_util.hpp"

namespace zip_with_index_test {
	template <typename T>
	using doubleify = list_<T, T>;

	int run() {
		using lhs = make_sequence_<lift_<doubleify>>;
		using rhs = make_sequence_<identity_, zip_with_index_<>>;
		call_<make_sequence_<make_algo<lhs>>, extent>{} =
		        call_<make_sequence_<make_algo<rhs>>, extent>{};

		return 0;
	}
} // namespace zip_with_index_test
