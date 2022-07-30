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

export module Boost.TMP:Base.Integral;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <unsigned long long V>
    struct uint_ {
        static constexpr unsigned long long value = V;
    };
    export template <long long I>
    struct int_ {
        static constexpr long long value = I;
    };

    export template<std::uint8_t V>
    struct uint8_ {
        static constexpr std::uint8_t value = V;
    };

    export template<std::uint16_t V>
    struct uint16_ {
        static constexpr std::uint16_t value = V;
    };

    export template<std::uint32_t V>
    struct uint32_ {
        static constexpr std::uint32_t value = V;
    };

    export template<std::int8_t V>
    struct int8_ {
        static constexpr std::int8_t value = V;
    };

    export template<std::int16_t V>
    struct int16_ {
        static constexpr std::int16_t value = V;
    };

    export template<std::int32_t V>
    struct int32_ {
        static constexpr std::int32_t value = V;
    };

    export template<std::size_t S>
    struct sizet_
    {
        static constexpr std::size_t value = S;
    };
} // namespace boost::tmp
