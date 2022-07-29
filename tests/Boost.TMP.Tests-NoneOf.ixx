//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:NoneOf;

import Boost.TMP;
import :Helpers;

namespace none_of_test {
    using namespace boost::tmp;

    export int run() {
        false_{} = call_<none_of_<lift_<is_even>>, int_<2>, int_<100>, int_<4>, int_<500>>{};
        true_{}  = call_<none_of_<lift_<is_even>>, int_<1>, int_<3>>{};
        return 0;
    }
} // namespace none_of_test
