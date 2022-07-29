//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Drop;

import Boost.TMP;

namespace drop_test {
	using namespace boost::tmp;

	export int run() {
		list_<int_<1>>{}          = call_<drop_<uint_<1>>, int_<0>, int_<1>>{};
		list_<int_<1>, int_<2>>{} = call_<drop_<uint_<0>>, int_<1>, int_<2>>{};
		return 0;
	}
} // namespace drop_test
