//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <type_traits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Maybe;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    template <bool B>
    struct maybe_test_impl {
        template <typename T>
        using f = T;
    };

    template <>
    struct maybe_test_impl<true> {};

    // TODO: Get rid of std::is_same_v here.
    template <typename T>
    using maybe_impl = maybe_test_impl<std::is_same_v<T, nothing_>>::template f<T>;

    export template <typename T, typename... Ts>
    using maybe_ = maybe_impl<typename dispatch<find_dispatch(sizeof...(Ts)), T>::template
                      f<Ts...>>;

    export template <typename T, typename... Ts>
    using maybe_t = maybe_impl<typename dispatch<find_dispatch(sizeof...(Ts)), T>::template
                       f<Ts...>::type>;

    export template <typename T, typename... Ts>
    constexpr auto maybe_v = maybe_impl<typename dispatch<find_dispatch(sizeof...(Ts)), T>::template
                                f<Ts...>>::value;
} // namespace boost::tmp
