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

export module Boost.TMP:Sequence.Take;

import :Base.Integral;
import :Base.List;
import :Base.Dispatch;
import :Sequence.Drop;
import :Sequence.Rotate;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename N = sizet_<0>, typename C = listify_>
    struct take_ {};

    template <std::size_t N, typename P, typename C>
    struct dispatch<N, take_<P, C>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)),
                     rotate_<P, drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>>::template f<Ts...>;
    };
} // namespace boost::tmp