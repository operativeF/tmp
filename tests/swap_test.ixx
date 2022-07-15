//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Swap;

import Boost.TMP;

using namespace boost::tmp;

export namespace swap_test {
	int run() {
		using alist = list_<uint_<0>, uint_<1>>;
		using blist = list_<uint_<1>, uint_<2>>;

		using alist_swap = call_<unpack_<swap_<>>, alist>;

		list_<uint_<1>, uint_<0>>{} = alist_swap{};

		using ab_swap = call_<swap_<>, alist, blist>;

		list_<blist, alist>{} = ab_swap{};

		return 0;
	}
} // namespace swap_test