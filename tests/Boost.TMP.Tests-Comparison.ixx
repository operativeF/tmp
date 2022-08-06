//  Copyright 2018-2019 Odin Holmes.
//            2022      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <type_traits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP.Tests:Comparison;

import Boost.TMP;

#if _MSC_VER
import std;
#endif // _MSC_VER

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
