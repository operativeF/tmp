//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:Reverse;

import Boost.TMP;

namespace reverse_test {
    using namespace boost::tmp;

    export int run() {
        list_<int_<2>, int_<1>, int_<0>>{} = call_<reverse_<>, int_<0>, int_<1>, int_<2>>{};

        // Reversing empty input results in empty list
        list_<>{} = call_<reverse_<>>{};

        // Reversing single input results in single input list
        list_<int_<1>>{} = call_<reverse_<>, int_<1>>{};

        return 0;
    }
} // namespace reverse_test
