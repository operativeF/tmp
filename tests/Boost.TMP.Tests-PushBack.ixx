//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:PushBack;

import Boost.TMP;

namespace push_back_test {
    using namespace boost::tmp;

    export int run() {
        list_<int_<1>, int_<2>, char_<'c'>>{} = call_<push_back_<char_<'c'>>, int_<1>, int_<2>>{};
        return 0;
    }
} // namespace push_back_test
