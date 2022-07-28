//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Test.Drop;

import Boost.TMP;

using namespace boost::tmp;

export namespace drop_test {
	int run() {
		list_<int_<1>>{} = call_<drop_<uint_<1>>, int_<0>, int_<1>>{};
		return 0;
	}
} // namespace drop_test
