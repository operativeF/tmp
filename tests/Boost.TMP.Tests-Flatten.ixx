//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Flatten;

import Boost.TMP;

namespace flatten_test {
	using namespace boost::tmp;

	using alist = list_<list_<uint_<0>, uint_<1>>, uint_<2>, list_<uint_<3>>, uint_<4>>;

	using result2 = call_<flatten_<>, alist>;
	
	export int run() {
		list_<uint_<0>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>{} = result2{};
		return 0;
	}
} // namespace flatten_test
