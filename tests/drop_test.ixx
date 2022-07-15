//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Drop;

import Boost.TMP;

using namespace boost::tmp;

export namespace drop_test {
	int run() {
		using drop_list = list_<uint_<0>, uint_<1>>;

		list_<uint_<1>>{} = call_<unpack_<drop_<uint_<1>>>, drop_list>{};
		list_<>{}         = call_<unpack_<drop_<uint_<2>>>, drop_list>{};

		return 0;
	}
} // namespace drop_test
