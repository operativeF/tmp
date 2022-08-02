//  Copyright 2018 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.CountIf;

import :Algorithm.Transform;
import :Base.Always;
import :Base.Dispatch;
import :Base.Identity;
import :Base.If;
import :Base.List;
import :Sequence.Join;
import :Sequence.Size;

#if _MSC_VER
import std;
#endif

/// \brief Given a predicate F, check the variadic parameter pack passed in and count
/// each time that the predicate holds true. Returns n counts as sizet_<n>.
/// \example
///
namespace boost::tmp {
    export template <typename F, typename C = identity_>
    struct count_if_ {};
    
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, count_if_<F, C>>
        : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
                                    join_<size_<C>>>> {};
} // namespace boost::tmp
