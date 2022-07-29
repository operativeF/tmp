//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:ReplaceIf;

import Boost.TMP;

namespace replace_if_test {
	using namespace boost::tmp;

	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	export int run() {
		list_<uint_<1>, char_<'c'>, uint_<1>>{} = call_<replace_if_<char_<'c'>, lift_<is_even>>, uint_<1>, uint_<2>, uint_<1>>{};
		return 0;
	}
} // namespace replace_if_test
