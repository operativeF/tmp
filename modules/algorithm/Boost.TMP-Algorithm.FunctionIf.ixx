//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//
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

export module Boost.TMP:Algorithm.FunctionIf;

import :Algorithm.Filter;
import :Algorithm.Logic;
import :Algorithm.Transform;
import :Base.Types;
import :Sequence.Join;
import :Sequence.Size;

import :TestHelpers;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// count_if_ : Given a predicate F, check the variadic parameter pack passed in and count
// each time that the predicate holds true. Returns n counts as sizet_<n>.
export template <typename F, typename C = identity_>
struct count_if_ {};

// count_if_ : implementation
template <std::size_t N, typename F, typename C>
struct dispatch<N, count_if_<F, C>>
    : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
                                join_<size_<C>>>> {};

// find_if_ : 
export template <typename F, typename C = identity_>
struct find_if_ {};

// find_if_ : implementation
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

// remove_if_ : Given a predicate F, check the variadic parameter pack passed in
// and remove the value if the predicate holds true.
export template <typename F, typename C = listify_>
struct remove_if_ {};

// remove_if_ : implementation
template<std::size_t N, typename F, typename C>
struct dispatch<N, remove_if_<F, C>>
        : dispatch<N, filter_<if_<F, always_<false_>, always_<true_>>, C>> {};

// replace_if_ : Given a variadic parameter pack, replace every value that fulfills
// the predicate F with the value Input.
export template <typename Input, typename F, typename C = listify_>
struct replace_if_ {};

// replace_if_ : implementation
template <std::size_t N, typename Input, typename F, typename C>
struct dispatch<N, replace_if_<Input, F, C>>
        : dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};
} // namespace boost::tmp

// TESTING:
namespace remove_if_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<3>>>)
struct OnlyOddNumbersLeft;

using test_one = OnlyOddNumbersLeft<call_<remove_if_<lift_<utils::is_even>>, int_<1>, int_<2>, int_<3>>>;
} // namespace remove_if_test

// TESTING:
namespace count_if_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, sizet_<0>>)
struct NoEvenNumbers;

template<typename T> requires(std::same_as<T, sizet_<3>>)
struct HasThreeEvenNumbers;

using test_one  = NoEvenNumbers<call_<count_if_<lift_<utils::is_even>>, int_<1>, int_<3>>>;

using test_two  = HasThreeEvenNumbers<call_<count_if_<lift_<utils::is_even>>, int_<0>, int_<2>, int_<4>>>;

// Empty input pack returns 0
using test_three = NoEvenNumbers<call_<count_if_<lift_<utils::is_even>>>>;
} // namespace count_if_test

// TESTING:
namespace replace_if_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<uint_<1>, char_<'c'>, uint_<1>>>)
struct ReplaceTwoWithC;

template<typename T> requires(std::same_as<T, list_<>>)
struct EmptyPackReturnsAnEmptyList;

using test_one = ReplaceTwoWithC<call_<replace_if_<char_<'c'>, lift_<utils::is_even>>, uint_<1>, uint_<2>, uint_<1>>>;

using test_two = EmptyPackReturnsAnEmptyList<call_<replace_if_<char_<'c'>, lift_<utils::is_even>>>>;
} // namespace replace_if_test

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
