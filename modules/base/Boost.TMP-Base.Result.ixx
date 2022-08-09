//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Base.Result;

import :Base.Types;

namespace boost::tmp {
    export template <typename C = identity_>
    struct result_ {};

    template <typename C>
    struct dispatch<1, result_<C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<T::type>;
    };
} // namespace boost::tmp