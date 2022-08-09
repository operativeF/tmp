//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#include <limits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.FindIf;

import :Base.Call;
import :Base.Foldey;
import :Base.Types;

import :TestHelpers;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename F, typename C = identity_>
    struct find_if_ {};

    template <bool Found, std::size_t At, template <typename...> class F>
    struct county {
        static constexpr auto value{std::numeric_limits<std::size_t>::max()};
        template <typename T>
        using f = county<F<T>::value, (At + 1), F>;
    };
    template <std::size_t At, template <typename...> class F>
    struct county<true, At, F> {
        template <typename T>
        using f                    = county;
        static constexpr std::size_t value = At;
    };

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, find_if_<F, C>> {
        template <typename... Ts>
        using f = typename dispatch<1, C>::template f<
                     typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
                        county<false,
                               std::numeric_limits<std::size_t>::max(),
                               dispatch<1, F>::template f>, 0, Ts...>>;
    };

    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, find_if_<lift_<F>, C>> {
        template <typename... Ts>
        using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
                     sizeof...(Ts))>::template f<county<false,
                                                        std::numeric_limits<std::size_t>::max(),
                                                        F>, 0, Ts...>>;
    };
} // namespace boost::tmp

// TESTING:
namespace find_if_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, sizet_<3>>)
    struct EvenNumberAtPositionThree;

    template<typename T> requires(std::same_as<T, nothing_>)
    struct ReturnNothingForNoValueFound;

    using test_one = EvenNumberAtPositionThree<call_<find_if_<lift_<utils::is_even>>, int_<1>, int_<1>, int_<1>, int_<2>>>;
    
    // find_if_ returns nothing_ when there is no value found that satisfies the predicate.
    using test_two = ReturnNothingForNoValueFound<call_<find_if_<lift_<utils::is_even>>, int_<1>>>;
} // namespace find_if_test
