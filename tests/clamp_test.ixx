//  Copyright 2018-2019 Odin Holmes.
//            2022      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Clamp;

import Boost.TMP;

using namespace boost::tmp;

export namespace clamp_test {
	int run() {
		using alist = list_<uint_<0>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>;

		list_<uint_<4>>{} = call_<unpack_<clamp_<uint_<3>, uint_<10>>>, alist>{};
		list_<uint_<3>, uint_<4>>{} = call_<unpack_<clamp_<uint_<2>, uint_<10>>>, alist>{};

		return 0;
	}
} // namespace clamp_test
