//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Test.Product;

import Boost.TMP;

using namespace boost::tmp;

export namespace product_test {

	using xl0 = list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<5>, uint_<6>, uint_<7>,
	                  uint_<8>, uint_<9>, uint_<10>>;
	using xr0 = list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<5>, uint_<6>, uint_<7>,
	                  uint_<8>, uint_<9>, uint_<10>>;

	using result0 = call_<product_<>, xl0, xr0>;

	using xl1 = list_<uint_<1>, uint_<2>, uint_<3>>;
	using xr1 = list_<uint_<1>, uint_<2>, uint_<3>>;

	using result1 = call_<product_<>, xl1, xr1>;
	int run() {
		list_<list_<uint_<1>, uint_<1>>, list_<uint_<1>, uint_<2>>, list_<uint_<1>, uint_<3>>,
		      list_<uint_<2>, uint_<1>>, list_<uint_<2>, uint_<2>>, list_<uint_<2>, uint_<3>>,
		      list_<uint_<3>, uint_<1>>, list_<uint_<3>, uint_<2>>, list_<uint_<3>, uint_<3>>>{} =
		        result1{};
		return 0;
	}
} // namespace product_test
