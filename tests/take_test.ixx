//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Test.Take;

import Boost.TMP;

using namespace boost::tmp;

template <int>
struct x;

using xs0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;

using result0 = call_<unpack_<take_<uint_<0>>>, xs0>;
using result1 = call_<unpack_<take_<uint_<1>>>, xs0>;
using result2 = call_<unpack_<take_<uint_<9>>>, xs0>;

export namespace take_test {
	int run() {
		return 0;
	}
} // namespace take_test