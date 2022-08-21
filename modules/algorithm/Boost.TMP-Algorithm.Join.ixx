//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#include <utility>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Join;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {

} // namespace boost::tmp

// TESTING:
namespace join_test {
using namespace boost::tmp;

// TODO: Implement join_test
// using joined_sequences = call_<join_seq_<lift_<into_sequence>>, std::index_sequence<1, 2>, std::index_sequence<3, 4>>;

// joined_sequences{} = std::index_sequence<1, 2, 3, 4>{};
} // namespace join_test
