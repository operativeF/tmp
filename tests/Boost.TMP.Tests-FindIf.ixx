//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:FindIf;

import Boost.TMP;
import :Helpers;

namespace find_if_test {
    using namespace boost::tmp;

    export int run() {
        sizet_<3>{} = call_<unpack_<find_if_<lift_<is_even>>>, list_<int_<1>, int_<1>, int_<1>, int_<2>>>{};
        
        // find_if_ returns nothing_ when there is no value found that satisfies the predicate.
        nothing_{} = call_<find_if_<lift_<is_even>>, int_<1>>{};

        return 0;
    }
} // namespace find_if_test
