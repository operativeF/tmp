//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <type_traits>
#endif // defined(__GNUC__) || defined(__clang__)

export module Boost.TMP.Tests:RepeatSequence;

import Boost.TMP;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace repeat_sequence_test {
    using namespace boost::tmp;

    export int run() {
        // std::index_sequence<1, 1, 1, 1, 1, 1, 1, 1, 1, 1>{} = call_<repeat_sequence_<sizet_<10>, lift_<into_sequence>>, sizet_<1>>{};
        list_<sizet_<1>, sizet_<1>, sizet_<1>, sizet_<2>, sizet_<2>, sizet_<2>, sizet_<3>, sizet_<3>, sizet_<3>>{} = call_<transform_<repeat_sequence_<sizet_<3>>, join_<>>, sizet_<1>, sizet_<2>, sizet_<3>>{};
        return 0;
    }
} // namespace repeat_sequence_test
