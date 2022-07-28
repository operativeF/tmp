//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Size;

import Boost.TMP;

using namespace boost::tmp;

export namespace size_test {
	int run() {
		sizet_<3>{} = call_<size_<>, int_<0>, int_<2>, int_<4>>{};

		return 0;
	}
} // namespace size_test
