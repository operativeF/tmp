//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Test.Erase;

import Boost.TMP;

#if _MSC_VER
import std;
#endif

using namespace boost::tmp;

export namespace erase_test {
	template <std::size_t>
	struct x;

	using xs0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;

	using result0 = call_<unpack_<erase_<sizet_<0>>>, xs0>;
	using result1 = call_<unpack_<erase_<sizet_<1>>>, xs0>;
	using result2 = call_<unpack_<erase_<sizet_<9>>>, xs0>;

	int run() {

		result0{} = list_<x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>{};
		result1{} = list_<x<1>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>{};
		result2{} = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>>{};

		return 0;
	}
} // namespace erase_test
