//  Copyright 2018-2019 Odin Holmes.
//		      2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:RangeMath;

import Boost.TMP;

namespace range_math_test {
	using namespace boost::tmp;

	using alist = list_<int_<-2>, int_<100>, int_<4>, int_<500>>;
	using blist = list_<int_<10>, int_<20>, int_<5>, int_<1>>;

	export int run() {
		int_<602>{} = call_<unpack_<accumulate_<>>, alist>{};

		int_<-606>{} = call_<unpack_<decimate_left_<>>, alist>{};
		int_<398>{}  = call_<unpack_<decimate_right_<>>, alist>{};

		int_<4>{}   = call_<unpack_<sorted_decimate_<>>, blist>{};
		int_<-34>{} = call_<unpack_<decimate_right_<>>, blist>{};
		int_<-16>{} = call_<unpack_<decimate_left_<>>, blist>{};

		int_<-400000>{} = call_<unpack_<multiplicate_<>>, alist>{};
		return 0;
	}
} // namespace range_math_test
