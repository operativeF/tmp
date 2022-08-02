//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstddef>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Byte;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template<std::byte B>
    struct byte_ {
        static constexpr std::byte value = B;
    };
} // namespace boost::tmp
