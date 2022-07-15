//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Transform;

import Boost.TMP;

using namespace boost::tmp;

export namespace transform_test {
	int run() {
		// using rhs = make_sequence_<identity_, transform_<listify_>>;
		// using lhs = make_sequence_<listify_>;
		// call_<make_sequence_<make_algo<lhs>>, extent>{} =
		//        call_<make_sequence_<make_algo<rhs>>, extent>{};

		return 0;
	}
} // namespace transform_test
