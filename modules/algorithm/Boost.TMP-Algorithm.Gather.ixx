//  Copyright 2019 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Gather;

import :Base.Call;
import :Base.List;
import :Base.Dispatch;
import :Sequence.Join;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    // Sorts, and then groups items into a list of lists of the same type.
    export template<typename F, typename C = listify_>
    struct gather_;

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, gather_<F, C>>{};
} // namespace boost::tmp

// TESTING:
namespace gather_test {

} // namespace gather_test
