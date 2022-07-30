//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:RemoveIf;

import Boost.TMP;
import :Helpers;

namespace remove_if_test {
    using namespace boost::tmp;

    export int run() {
        list_<int_<1>, int_<3>>{} = call_<remove_if_<lift_<is_even>>, int_<1>, int_<2>, int_<3>>{};
        return 0;
    }
} // namespace remove_if_test
