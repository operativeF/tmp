//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Foldey;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
consteval std::size_t select_foldey_loop(std::size_t rest_size) {
    return static_cast<std::size_t>(rest_size < 8 ? (rest_size == 0 ? 1000 : 1001) : 1008);
}

// FIXME: Workaround employed after value isn't found when invoking F::template f<T0>::value
// in foldey<1001>. The value of the type is found after referring to it here, not in foldey<1001>.
template<typename WorkAroundT>
consteval std::size_t select_foldey(std::size_t chunk_size, std::size_t rest_size) {
    return WorkAroundT::value == std::numeric_limits<std::size_t>::max() ? select_foldey_loop(rest_size) :
                                    chunk_size - WorkAroundT::value;
}

template <std::size_t S>
struct foldey {
    template <typename F, std::size_t N, typename...>
    using f = sizet_<N - S>;
};
template <>
struct foldey<1000> {
    template <typename F, std::size_t N, typename... Ts>
    using f = nothing_;
};
// FIXME: Workaround for extracting value in F::template f<T0>. Pass type into now templated select_foldey.
template <>
struct foldey<1001> {
    template <typename F, std::size_t N, typename T0, typename... Ts> 
    using f = foldey<select_foldey<typename F::template f<T0>>(1, sizeof...(Ts))>::template f<F, N + 1, Ts...>;
};
template <>
struct foldey<1008> {
    template <typename F, std::size_t N, typename T0, typename T1, typename T2,
                typename T3, typename T4, typename T5, typename T6, typename T7,
                typename... Ts>
    using f = foldey<select_foldey(8, sizeof...(Ts),
                F::template
                  f<T0>::template
                    f<T1>::template
                      f<T2>::template
                        f<T3>::template
                          f<T4>::template
                            f<T5>::template
                              f<T6>::template
                                f<T7>::value)>::template
                                  f<F, N + 8, Ts...>;
};
template <>
struct foldey<1000000> {};
} // export namespace boost::tmp
