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

export module Boost.TMP:Algorithm.Counted;

import :Algorithm.Drop;
import :Algorithm.Take;
import :Base.Types;

import std;

namespace boost::tmp {

// counted_ :
export template<typename StartIndex, typename Count, typename C = listify_>
struct counted_ {};

// counted_ : implemenation
template<std::size_t N, typename StartIndex, typename Count, typename C>
struct dispatch<N, counted_<StartIndex, Count, C>> {
    template<typename... Ts>
    using f = dispatch<sizeof...(Ts), drop_<StartIndex, take_<Count, C>>>::template f<Ts...>;
};

} // namespace boost::tmp

namespace counted_test {

using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
struct GetTheMiddle123;

using counted_test_1 = GetTheMiddle123<call_<counted_<int_<1>, int_<3>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<5>, int_<7>>>;

} // namespace counted_test
