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
	using is_equal = bool_<(std::is_same_v<T, U>)>;

	template <typename T, typename U>
	using push = call_<join_<>, T, U>;

	using list_A = list_<list_<uint_<1>>, list_<uint_<2>>>;
	using list_B = list_<list_<uint_<3>>, list_<uint_<4>>>;
	using list_C = list_<uint_<2>, uint_<2>, uint_<2>, uint_<1>>;

	using new_list = call_<divide_units_<>, list_A, list_B>;

	template <typename T>
	using is_equal_pair = call_<unpack_<lift_<is_equal>>, T>;

	using aalist = list_<uint_<1>, uint_<2>, uint_<3>>;
	using bblist = list_<uint_<2>, uint_<1>, uint_<7>, uint_<4>, uint_<3>>;

	using new_set = call_<product_<>, aalist, bblist>;

	using filt_set = call_<unpack_<filter_<lift_<is_equal_pair>>>, new_set>;

    using alist = list_<uint_<2>, uint_<100>, uint_<4>, uint_<500>>;

	using cclist = list_<uint_<1>, uint_<2>, uint_<3>, uint_<1>, uint_<2>>;

	using union_set = call_<union_<>, aalist, bblist>;

	using intersect = call_<intersection_<>, aalist, bblist>;
	using intersect_set = call_<unpack_<drop_<uint_<1>>>, intersect>;

	int run() {
		union_set{} = list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<7>>{};
		//intersect_set{} = list_<uint_<1>, uint_<2>, uint_<3>>{};
        bool_<true>{} = call_<unpack_<all_of_<lift_<is_even>>>, alist>{};
		return 0;
	}
} // namespace all_of_test