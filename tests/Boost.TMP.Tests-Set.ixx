//  Copyright 2018-2019 Odin Holmes.
//			  2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Set;

import Boost.TMP;

namespace set_test {
    using namespace boost::tmp;

    // using aalist = list_<uint_<1>, uint_<2>, uint_<3>, uint_<9>, uint_<3>>;
    // using bblist = list_<uint_<2>, uint_<1>, uint_<7>, uint_<4>, uint_<3>>;
    // using cclist = list_<uint_<1>, uint_<2>, uint_<3>, uint_<9>, uint_<3>>;
    // using ddlist = list_<>;

    // using union_set = call_<set_union_<>, aalist, bblist>;

    // using intersect_set = call_<set_intersection_<>, aalist, bblist>;

    // using sym_set = call_<set_symmetric_difference_<>, aalist, bblist>;

    // using diff_a = call_<set_difference_A_<>, aalist, bblist>;

    // using diff_b = call_<set_difference_B_<>, aalist, bblist>;

    // using quotient = list_<diff_a, diff_b>;

    // using diff_c = call_<set_difference_A_<>, cclist, ddlist>;

    // using diff_d = call_<set_difference_B_<>, cclist, ddlist>;

    // using quotient_b = list_<diff_c, diff_d>;

    export int run() {
        // quotient{} = list_<list_<uint_<3>, uint_<9>>, list_<uint_<4>, uint_<7>>>{};
        // sym_set{} = list_<uint_<3>, uint_<4>, uint_<7>, uint_<9>>{};
        // union_set{} = list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<7>, uint_<9>>{};
        // intersect_set{} = list_<uint_<1>, uint_<2>, uint_<3>>{};
        return 0;
    }
} // namespace set_test
