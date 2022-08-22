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

export module Boost.TMP:Base.Try;

import :Base.Types;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {

export template <template <typename...> class F, typename C = identity_>
struct try_ {};

template <typename T>
struct t_ {
    using type = T;
};

namespace impl {

template <template <typename...> class F, typename... Ts>
t_<F<Ts...>> try_f(lift_<F>, list_<Ts...>);
t_<nothing_> try_f(...);

template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, try_<F, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<typename decltype(
            try_f(lift_<F>{}, list_<Ts...>{}))::type>;
};

} // namespace impl

namespace try_test {

// TODO: Implement try_test
// template <typename T>
// using call_type = T::type;

// struct has_type {
//     using type = int;
// };

// nothing_{}   = call_<try_<call_type>, int>{}; // should SFINAE, int has no ::type
// list_<int>{} = list_<call_<try_<call_type>, has_type>>{}; // should not SFINAE
// list_<int>{} = call_<try_<call_type, listify_>, has_type>{}; // test the continuation

} // namespace try_test

} // namespace boost::tmp
