//  Copyright 2018-2019 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <utility>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP.Tests:Join;

import Boost.TMP;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace join_test {
    using namespace boost::tmp;

    using joined_sequences = call_<join_seq_<lift_<into_sequence>>, std::index_sequence<1, 2>, std::index_sequence<3, 4>>;

    export int run() {
        joined_sequences{} = std::index_sequence<1, 2, 3, 4>{};
        return 0;
    }
} // namespace join_test
