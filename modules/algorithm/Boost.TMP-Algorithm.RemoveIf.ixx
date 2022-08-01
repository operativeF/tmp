//  Copyright 2018 Odin Holmes.
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

export module Boost.TMP:Algorithm.RemoveIf;

import :Algorithm.Filter;
import :Base.Always;
import :Base.Bool;
import :Base.If;
import :Base.Dispatch;

#if _MSC_VER
import std;
#endif

/// \brief Given a predicate F, check the variadic parameter pack passed in
/// and remove the value if the predicate holds true.
namespace boost::tmp {
    export template <typename F, typename C = listify_>
    struct remove_if_ {};

    template<std::size_t N, typename F, typename C>
    struct dispatch<N, remove_if_<F, C>>
        : dispatch<N, filter_<if_<F, always_<false_>, always_<true_>>, C>> {};
} // namespace boost::tmp
