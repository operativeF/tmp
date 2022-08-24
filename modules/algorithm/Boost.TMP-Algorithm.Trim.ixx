//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Trim;

import :Algorithm.Core;
import :Algorithm.FunctionIf;
import :Algorithm.Tee;
import :Base.Types;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

// drop_list_ :
template<typename C = listify_>
struct drop_list_ {};

// drop_list_ : implementation
namespace impl {

template<std::size_t N, typename C>
struct dispatch<N, drop_list_<C>> {
    template<typename DropValue, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), unpack_<drop_<DropValue, C>>>::template f<Ts...>;
};

} // namespace impl

// drop_while_ :
export template<typename F, typename C = listify_>
struct drop_while_ {};

// drop_while_ : implementation
namespace impl {

template<std::size_t N, typename F, typename C>
struct dispatch<N, drop_while_<F, C>> : dispatch<N, tee_<find_if_not_<F>, listify_, drop_list_<C>>> {};

} // namespace impl

// trim_ :
export template<typename F, typename C = listify_>
struct trim_ {};

// trim_ : implementation
namespace impl {

template<std::size_t N, typename F, typename C>
struct dispatch<N, trim_<F, C>> : dispatch<N, drop_while_<F, reverse_<drop_while_<F, reverse_<C>>>>> {};

} // namespace impl

// drop_while_back_ :
export template<typename F, typename C = listify_>
struct drop_while_back_ {};

// drop_while_back_ : implementation
namespace impl {

template<std::size_t N, typename F, typename C>
struct dispatch<N, drop_while_back_<F, C>> : dispatch<N, reverse_<drop_while_<F, reverse_<C>>>> {};

} // namespace impl

#ifdef TMP_COMPILE_TIME_TESTING
namespace test {

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<1>>>)
struct DropEvenNumbersAtFront;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<1>>>)
struct DropEvenNumbersAtBack;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using drop_while_test_1 = DropEvenNumbersAtFront<call_<drop_while_<lift_<is_even>>, int_<2>, int_<2>, int_<1>, int_<1>>>;

using drop_while_back_test_1 = DropEvenNumbersAtBack<call_<drop_while_back_<lift_<is_even>>, int_<1>, int_<1>, int_<2>, int_<2>>>;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<6>, int_<1>>>)
struct TrimEvenNumbersUntilOdd;

using trim_test_1 = TrimEvenNumbersUntilOdd<call_<trim_<lift_<is_even>>, int_<2>, int_<1>, int_<6>, int_<1>, int_<2>>>;

} // test
#endif // TMP_COMPILE_TIME_TESTING

} // namespace boost::tmp
