//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:RemoveIf;

import Boost.TMP;

namespace remove_if_test {
	using namespace boost::tmp;

	template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	using alist = list_<uint_<0>, uint_<1>, uint_<2>, uint_<4>>;

	export int run() {
		list_<uint_<1>>{} = call_<unpack_<remove_if_<lift_<is_even>>>, alist>{};
		return 0;
	}
} // namespace remove_if_test
