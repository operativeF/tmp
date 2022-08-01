//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Sort;

import Boost.TMP;
import :Helpers;

namespace sort_test {
	using namespace boost::tmp;

	template <typename T, typename U>
	using push_less = T::template push<U, less>;

	export int run() {
		list_<sizet_<0>, sizet_<1>, sizet_<2>>{} =
		        call_<sort_<lift_<less>>, sizet_<1>, sizet_<0>, sizet_<2>>{};

		return 0;
	}
} // namespace sort_test
