//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Tests:PopFront;

import Boost.TMP;

namespace pop_front_test {
    using namespace boost::tmp;

    export int run() {
        // Pop front off of single element list to return an empty list.
        list_<>{} = call_<pop_front_<>, list_<int_<1>>>{};

        // Pop front off of empty list_ to return an empty list_
        list_<>{} = call_<pop_front_<>, list_<>>{};

        // UNDER CONSIDERATION: Removal / modification of behavior of
        // pop_front_ on no input. Currently returns a list_<nothing_>
        list_<nothing_>{} = call_<pop_front_<>>{};

        return 0;
    }
} // namespace pop_front_test
