//  Copyright 2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:TestHelpers;

import :Base.Types;
import :Algorithm.Join;

namespace boost::tmp::utils {
    using namespace boost::tmp;

    template <typename T, typename U>
    using add = uint_<(T::value + U::value)>;

    template <typename T>
    using is_even = bool_<(T::value % 2 == 0)>;

    template <typename T>
    using greater_than_two = bool_<(T::value > 2)>;

    template <typename T, typename U>
    using less = bool_<(T::value < U::value)>;

    template <typename T, typename U>
    using pusher = call_<join_<>, T, list_<U>>;
} // namespace boost::tmp::utils
