//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include <boost/tmp_units/composite.hpp>
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

	using aalist = list_<uint_<1>, uint_<2>, uint_<3>, uint_<9>>;
	using bblist = list_<uint_<2>, uint_<1>, uint_<7>, uint_<4>, uint_<3>>;
	
	template <typename T, typename U>
	using lessen = bool_<(T::value < U::value)>;
	
	using new_set = call_<product_<>, aalist, bblist>;

    using alist = list_<uint_<2>, uint_<100>, uint_<4>, uint_<500>>;

	using union_set = call_<set_union_<>, aalist, bblist>;

	using intersect_set = call_<set_intersection_<>, aalist, bblist>;

	using sym_set = call_<set_symmetric_difference_<>, aalist, bblist>;

	using diff_a = call_<set_difference_B_<>, aalist, bblist>;

	int run() {
		sym_set{} = list_<uint_<4>, uint_<7>, uint_<9>>{};
		union_set{} = list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<7>, uint_<9>>{};
		intersect_set{} = list_<uint_<1>, uint_<2>, uint_<3>>{};
        bool_<true>{} = call_<unpack_<all_of_<lift_<is_even>>>, alist>{};
		return 0;
	}
} // namespace all_of_test