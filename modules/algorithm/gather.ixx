//  Copyright 2019 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Algorithm.Gather;

import Boost.TMP.Base.Call;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;

import Boost.TMP.Sequence.Join;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

export namespace boost::tmp {
    // Sorts, and then groups items into a list of lists of the same type.
    template<typename F, typename C = listify_>
    struct gather_;

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, gather_<F, C>>{};
} // export namespace boost::tmp
