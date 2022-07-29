//  Copyright 2018-2019 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:CountIf;

import Boost.TMP;
import :Helpers;

namespace count_if_test {
	using namespace boost::tmp;
	
	export int run() {
		sizet_<0>{} = call_<count_if_<lift_<is_even>>, int_<1>>{};
		sizet_<1>{} = call_<count_if_<lift_<is_even>>, int_<2>>{};
		sizet_<3>{} = call_<count_if_<lift_<is_even>>, int_<0>, int_<2>, int_<4>>{};

		return 0;
	}
} // namespace count_if_test
