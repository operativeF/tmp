//  Copyright 2018-2019 Odin Holmes.
//            2022      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Comparison;

import Boost.TMP;

import std;

namespace comparison_test {
    using namespace boost::tmp;

    template<int A, int B>
    struct two_ints {
        int a{A};
        int b{B};
    };

    export int run() {
            false_{} = call_<less_f_<lift_<std::alignment_of>>, two_ints<1, 2>, char_<'c'>>{};
            true_{}  = call_<less_f_<lift_<std::alignment_of>>, char_<'c'>,     two_ints<1, 2>>{};
        return 0;
    }
} // namespace comparison_test
