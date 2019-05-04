//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include "test_util.hpp"
#include "../include/boost/tmp/algorithm/product.hpp"

namespace product_test {
	template <int I>
	struct x {
		static constexpr int value = I;
	};

	using xl0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;
	using xr0 = list_<x<1>, x<2>, x<3>, x<4>, x<5>, x<6>, x<7>, x<8>, x<9>, x<10>>;

	using result0 = call_<product_<>, xl0, xr0>;

	using xl1 = list_<x<1>, x<2>, x<3>>;
	using xr1 = list_<x<1>, x<2>, x<3>>;
	
	using result1 = call_<product_<>, xl1, xr1>;
	int run() {
		list_<
			list_<x<1>, x<1>>, list_<x<1>, x<2>>, list_<x<1>, x<3>>,
			list_<x<2>, x<1>>, list_<x<2>, x<2>>, list_<x<2>, x<3>>,
			list_<x<3>, x<1>>, list_<x<3>, x<2>>, list_<x<3>, x<3>>
		>{} = result1{};
		return 0;
	}
} // namespace product_test