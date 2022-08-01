//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Base.Char;

namespace boost::tmp {
    export template<char C>
    struct char_
    {
        static constexpr char value = C;
    };

    export template<wchar_t C>
    struct wchar_
    {
        static constexpr wchar_t value = C;
    };

    export template<unsigned char C>
    struct uchar_
    {
        static constexpr unsigned char value = C;
    };

    export template<char8_t C>
    struct char8_
    {
        static constexpr char8_t value = C;
    };

    export template<char16_t C>
    struct char16_
    {
        static constexpr char16_t value = C;
    };

    export template<char32_t C>
    struct char32_
    {
        static constexpr char32_t value = C;
    };
} // namespace boost::tmp
