//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:FoldLeft;

import Boost.TMP;
import :Helpers;

namespace fold_left_test {
    using namespace boost::tmp;

    export int run() {
        list_<>{}                   = call_<fold_left_<lift_<pusher>>, list_<>>{};
        list_<uint_<1>, uint_<2>>{} = call_<fold_left_<lift_<pusher>>, list_<>, uint_<1>, uint_<2>>{};

        return 0;
    }
} // namespace fold_left_test
