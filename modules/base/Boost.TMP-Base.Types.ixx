//  Copyright 2018 Odin Holmes.
//            2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstddef>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Types;

#if _MSC_VER
import std;
#endif // _MSC_VER

export namespace boost::tmp {

    // The dispatch type finds the appropriate metaclosure to call and forms
    // the basis of the library.
    template <std::size_t N, typename T>
    struct dispatch;

    consteval std::size_t find_dispatch(std::size_t n) {
        return n <= 8 ? n :
                        n < 16 ?
                        9 :
                        n == 16 ?
                        16 :
                        n < 32 ?
                        17 :
                        n == 32 ?
                        32 :
                        n < 64 ? 33 : n == 64 ? 64 : n < 128 ? 65 : n == 128 ? 128 : 129;
    }

    template <typename C>
    struct dispatch_unknown {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
    };

    // Boolean types / aliases
    export template<bool B>
    struct bool_ { static constexpr bool value = B; };

    export using true_  = bool_<true>;
    export using false_ = bool_<false>;

    // byte type
    export template<std::byte B>
    struct byte_ { static constexpr std::byte value = B; };

    // char types
    export template<char C>
    struct char_ { static constexpr char value = C; };
    export template<wchar_t C>
    struct wchar_ { static constexpr wchar_t value = C; };
    export template<unsigned char C>
    struct uchar_ { static constexpr unsigned char value = C; };
    export template<char8_t C>
    struct char8_ { static constexpr char8_t value = C; };
    export template<char16_t C>
    struct char16_ { static constexpr char16_t value = C; };
    export template<char32_t C>
    struct char32_ { static constexpr char32_t value = C; };

    // Identity type
    export struct identity_ {};

    template <>
    struct dispatch<1, identity_> {
        template <typename T>
        using f = T;
    };

    // Integral types
    export template<unsigned long long V>
    struct uint_ { static constexpr unsigned long long value = V; };
    export template<long long I>
    struct int_ { static constexpr long long value = I; };
    export template<std::size_t S>
    struct sizet_ { static constexpr std::size_t value = S; };
    export template<std::uint8_t V>
    struct uint8_ { static constexpr std::uint8_t value = V; };
    export template<std::uint16_t V>
    struct uint16_ { static constexpr std::uint16_t value = V; };
    export template<std::uint32_t V>
    struct uint32_ { static constexpr std::uint32_t value = V; };
    export template<std::uint64_t V>
    struct uint64_ { static constexpr std::uint64_t value = V; };
    export template<std::int8_t V>
    struct int8_ { static constexpr std::int8_t value = V; };
    export template<std::int16_t V>
    struct int16_ { static constexpr std::int16_t value = V; };
    export template<std::int32_t V>
    struct int32_ { static constexpr std::int32_t value = V; };
    export template<std::int64_t V>
    struct int64_ { static constexpr std::int64_t value = V; };

    // Nothing type
    export struct nothing_ {};

    // Lift type - Used for applying a function to a continuation argument (parameter pack).
    export template <template <typename...> class F, typename C = identity_>
    struct lift_ {};

    template <template <typename...> class F, typename C>
    struct dispatch<1, lift_<F, C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<F<T>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<2, lift_<F, C>> {
        template <typename T0, typename T1>
        using f = dispatch<1, C>::template f<F<T0, T1>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<3, lift_<F, C>> {
        template <typename T0, typename T1, typename T2>
        using f = dispatch<1, C>::template f<F<T0, T1, T2>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<4, lift_<F, C>> {
        template <typename T0, typename T1, typename T2, typename T3>
        using f = dispatch<1, C>::template f<F<T0, T1, T2, T3>>;
    };
    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, lift_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<F<Ts...>>;
    };

    // List types / aliases
    export template <typename... Ts>
    struct list_ {};

    export using listify_ = lift_<list_>;

    // The always type returns type / shovels into the continuation C.
    export template <typename T, typename C = identity_>
    struct always_ {};

    template <std::size_t N, typename T, typename C>
    struct dispatch<N, always_<T, C>> {
        template <typename...>
        using f = dispatch<1, C>::template f<T>;
    };
} // namespace boost::tmp
