//  Copyright 2018-2019 Odin Holmes.
//            2022      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Clamp;

import Boost.TMP;

namespace clamp_test {
	using namespace boost::tmp;

	using alist = list_<uint_<0>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>;

	export int run() {
		list_<uint_<4>>{} = call_<unpack_<clamp_<uint_<3>, uint_<10>>>, alist>{};

		return 0;
	}
} // namespace clamp_test
