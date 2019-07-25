#ifndef BOOST_TMP_ANY_OF_TEST_HPP_INCLUDED
#define BOOST_TMP_ANY_OF_TEST_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include "test_util.hpp"

namespace any_of_test {
	
    template <typename T>
	using is_even = bool_<(T::value % 2 == 0)>;

    template <typename T, typename U>
	using plus_ = int_<(T::value + U::value)>;

    template<typename T, typename U>
    using same_as = call_<is_<T>, U>;

    using alist = list_<int_<1>>;
    using arslist = list_<int_<1>, int_<1>>;

    // This is important. For flatten_ to work properly here, we have to join the results; otherwise, it's just a variadic parameter pack floating around.
    using dlist = call_<product_<flatten_<>, join_<>>, alist, alist>;

    using rlist = call_<fold_left_< each_<unpack_<fold_left_<lift_<same_as>>>, unpack_<fold_left_<lift_<same_as>>>, lift_<same_as>> >, alist, alist>;

	int run() {

        rlist{} = true_{};

        dlist{} = list_<int_<1>, int_<1>>{};

        //bool_<true>{} = call_<unpack_<any_of_<lift_<is_even>>>, alist>{};
		//bool_<false>{} = call_<unpack_<any_of_<lift_<is_even>>>, blist>{};
        //bool_<true>{} = call_<unpack_<any_of_<lift_<is_even>>>, clist>{};

        return 0;
	}
} // namespace any_of_test

#endif