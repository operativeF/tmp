//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include <boost/tmp_units/composite.hpp>
#include <iostream>
#include "test_util.hpp"

namespace all_of_test {
    template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

	template <typename T, typename U>
	using push = call_<join_<>, T, U>;

	using list_A = list_<list_<uint_<1>>, list_<uint_<2>>>;
	using list_B = list_<list_<uint_<3>>, list_<uint_<4>>>;

	//template<typename L1, typename L2, typename C = listify_>
	//using divide_units_ = call_<fold_left_<lift_<push>>, list_<>, call_<ui0_<>, L1>, call_<ui1_<>, L2>>, list_<>, call_<ui1_<>, L1>, call_<ui0_<>, L2>>;
	//using divide_units_test1 = call_<tee_<ui0_<>, ui0_<>, listify_>, list_A>;
	//using divide_units_ = call_<tee_< tee_<ui0_<>, ui3_<>, listify_>, tee_<ui1_<>, ui2_<>, listify_>, listify_>, push<list_A, list_B> >;

	using new_list = call_<divide_units_<>, list_A, list_B>;

    using alist = list_<uint_<2>, uint_<100>, uint_<4>, uint_<500>>;

	int run() {
        bool_<true>{} = call_<unpack_<all_of_<lift_<is_even>>>, alist>{};
		//list_<list_<uint_<1>, uint_<4>>, list_<uint_<2>, uint_<4>>>{} = new_list{};
		new_list{} = list_< list_<list_<uint_<1>>, list_<uint_<4>>>, list_<list_<uint_<2>>, list_<uint_<3>>> >{};
		//index_f{} = list_<uint_<1>>{};
		return 0;
	}
} // namespace all_of_test