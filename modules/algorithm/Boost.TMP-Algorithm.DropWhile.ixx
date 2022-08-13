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

export module Boost.TMP:Algorithm.DropWhile;

import :Algorithm.Drop;
import :Algorithm.FunctionIf;
import :Algorithm.Tee;
import :Algorithm.Unpack;
import :Base.Types;

// FIXME: Off by one from find_if_. Needs to decrement or needs to have
// a find find_if_before_ or something.
namespace boost::tmp {

// drop_list_ :
template<typename C = listify_>
struct drop_list_ {};

// drop_list_ : implementation
template<std::size_t N, typename C>
struct dispatch<N, drop_list_<C>> {
    template<typename DropValue, typename... Ts>
    using f = dispatch<sizeof...(Ts), unpack_<drop_<DropValue, C>>>::template f<Ts...>;
};

// drop_while_ :
template<typename F, typename C = listify_>
struct drop_while_ {};

// drop_while_ : implementation
template<std::size_t N, typename F, typename C>
struct dispatch<N, drop_while_<F, C>> : dispatch<N, tee_<find_if_not_<F>, listify_, drop_list_<C>>> {};

} // namespace boost::tmp

namespace drop_while_test {

using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<1>>>)
struct DropEvenNumbersAtFront;

template<typename T>
using is_even = bool_<(T::value % 2 == 0)>;

using drop_while_test_1 = DropEvenNumbersAtFront<call_<drop_while_<lift_<is_even>>, int_<2>, int_<2>, int_<1>, int_<1>>>;

} // drop_while_test