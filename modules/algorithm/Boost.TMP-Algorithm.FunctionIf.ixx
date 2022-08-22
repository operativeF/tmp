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
import :Algorithm.Join;
import :Algorithm.Logic;
import :Algorithm.Size;
import :Algorithm.Transform;
import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
// count_if_ : Given a predicate F, check the variadic parameter pack passed in and count
// each time that the predicate holds true. Returns n counts as sizet_<n>.
export template <typename F, typename C = identity_>
struct count_if_ {};

// count_if_ : implementation
namespace impl {

template <std::size_t N, typename F, typename C>
struct dispatch<N, count_if_<F, C>>
    : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
                                join_<size_<C>>>> {};

} // namespace impl

// find_if_ : 
export template <typename F, typename C = identity_>
struct find_if_ {};

// find_if_ : implementation
namespace impl {

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

} // namespace impl

// find_if_not_ : 
export template <typename F, typename C = identity_>
struct find_if_not_ {};

namespace impl {

// find_if_not_ : implementation
template <bool Found, std::size_t At, template <typename...> class F>
struct county_not {
    static constexpr auto value{std::numeric_limits<std::size_t>::max()};
    template <typename T>
    using f = county_not<F<T>::value, (At + 1), F>;
};
template <std::size_t At, template <typename...> class F>
struct county_not<false, At, F> {
    template <typename T>
    using f                    = county_not;
    static constexpr std::size_t value = At;
};
template <std::size_t N, typename F, typename C>
struct dispatch<N, find_if_not_<F, C>> {
    template <typename... Ts>
    using f = typename dispatch<1, C>::template f<
                    typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
                    county_not<true,
                            std::numeric_limits<std::size_t>::max(),
                            dispatch<1, F>::template f>, 0, Ts...>>;
};
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, find_if_not_<lift_<F>, C>> {
        template <typename... Ts>
        using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
                     sizeof...(Ts))>::template f<county_not<true,
                                                        std::numeric_limits<std::size_t>::max(),
                                                        F>, 0, Ts...>>;
};

} // namespace impl

// remove_if_ : Given a predicate F, check the variadic parameter pack passed in
// and remove the value if the predicate holds true.
export template <typename F, typename C = listify_>
struct remove_if_ {};

// remove_if_ : implementation
namespace impl {

template<std::size_t N, typename F, typename C>
struct dispatch<N, remove_if_<F, C>>
        : dispatch<N, filter_<if_<F, always_<false_>, always_<true_>>, C>> {};

} // namespace impl

// replace_if_ : Given a variadic parameter pack, replace every value that fulfills
// the predicate F with the value Input.
export template <typename Input, typename F, typename C = listify_>
struct replace_if_ {};

// replace_if_ : implementation
namespace impl {

template <std::size_t N, typename Input, typename F, typename C>
struct dispatch<N, replace_if_<Input, F, C>>
        : dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};

} // namespace impl

namespace test {

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<3>>>)
struct RemoveIfOnlyOddNumbersLeft;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using remove_if_test_1 = RemoveIfOnlyOddNumbersLeft<call_<remove_if_<lift_<is_even>>, int_<1>, int_<2>, int_<3>>>;

template<typename T> requires(std::same_as<T, sizet_<0>>)
struct CountIfNoEvenNumbers;

template<typename T> requires(std::same_as<T, sizet_<3>>)
struct CountIfHasThreeEvenNumbers;

using count_if_test_1  = CountIfNoEvenNumbers<call_<count_if_<lift_<is_even>>, int_<1>, int_<3>>>;

using count_if_test_2  = CountIfHasThreeEvenNumbers<call_<count_if_<lift_<is_even>>, int_<0>, int_<2>, int_<4>>>;

// Empty input pack returns 0
using count_if_test_3 = CountIfNoEvenNumbers<call_<count_if_<lift_<is_even>>>>;

template<typename T> requires(std::same_as<T, list_<uint_<1>, char_<'c'>, uint_<1>>>)
struct ReplaceTwoWithC;

template<typename T> requires(std::same_as<T, list_<>>)
struct ReplaceIfEmptyPackReturnsAnEmptyList;

using replace_if_test_1 = ReplaceTwoWithC<call_<replace_if_<char_<'c'>, lift_<is_even>>, uint_<1>, uint_<2>, uint_<1>>>;

using replace_if_test_2 = ReplaceIfEmptyPackReturnsAnEmptyList<call_<replace_if_<char_<'c'>, lift_<is_even>>>>;

template<typename T> requires(std::same_as<T, sizet_<3>>)
struct FindIfEvenNumberAtPositionThree;

template<typename T> requires(std::same_as<T, nothing_>)
struct FindIfReturnNothingForNoValueFound;

using find_if_test_1 = FindIfEvenNumberAtPositionThree<call_<find_if_<lift_<is_even>>, int_<1>, int_<1>, int_<1>, int_<2>>>;

// find_if_ returns nothing_ when there is no value found that satisfies the predicate.
using find_if_test_2 = FindIfReturnNothingForNoValueFound<call_<find_if_<lift_<is_even>>, int_<1>>>;

template<typename T> requires(std::same_as<T, sizet_<2>>)
struct FindIfNotOddNumberAtPositionTwo;

template<typename T> requires(std::same_as<T, nothing_>)
struct FindIfNotReturnNothingForNoValueFound;

using find_if_not_test_1 = FindIfNotOddNumberAtPositionTwo<call_<find_if_not_<lift_<is_even>>, int_<2>, int_<4>, int_<1>, int_<2>>>;

// find_if_ returns nothing_ when there is no value found that satisfies the predicate.
using find_if_not_test_2 = FindIfNotReturnNothingForNoValueFound<call_<find_if_not_<lift_<is_even>>, int_<2>>>;

} // namespace test

} // namespace boost::tmp
