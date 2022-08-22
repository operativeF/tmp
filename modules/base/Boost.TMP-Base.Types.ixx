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
#include <type_traits>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Types;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

namespace impl {
// dispatch : The type finds the appropriate metaclosure to invoke and forms
// the basis of the library.
template <std::size_t N, typename T>
struct dispatch;

// find_dispatch : 
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

// dispatch_unknown :
template <typename C>
struct dispatch_unknown {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
};

consteval std::size_t step_selector(std::size_t N) {
    return N <= 8 ? N : N < 16 ? 8 : N < 32 ? 16 : N < 64 ? 32 : 64;
}

} // namespace impl

// Boolean type wrapper
export template<bool B>
struct bool_ { static constexpr bool value = B; };

// bool_ type aliases
export using true_  = bool_<true>;
export using false_ = bool_<false>;

// std::byte type wrapper
export template<std::byte B>
struct byte_ { static constexpr std::byte value = B; };

// Char type wrappers
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

// identity_ :
export struct identity_ {};

// identity_ : implementation
namespace impl {

template <>
struct dispatch<1, identity_> {
    template <typename T>
    using f = T;
};

} // namespace impl

// Unsigned and signed integral type wrappers
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

// nothing_ : 
export struct nothing_ {};

// lift_ : Used for lifting a type into a function.
export template <template <typename...> class F, typename C = identity_>
struct lift_ {};

// lift_ : implementation
namespace impl {

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

} // namespace impl

// list_ :
export template <typename... Ts>
struct list_ {};
// listify_ : 
export using listify_ = lift_<list_>;

// always_ : metaclosure returns type / shovels into the continuation C.
export template <typename T, typename C = identity_>
struct always_ {};

// always_ : implementation
namespace impl {

template <std::size_t N, typename T, typename C>
struct dispatch<N, always_<T, C>> {
    template <typename...>
    using f = dispatch<1, C>::template f<T>;
};

} // namespace impl

// result_: The same as always_, but refers to the type inside
// of the input type T.
export template <typename C = identity_>
struct result_ {};

// result_ : implementation
namespace impl {

template <typename C>
struct dispatch<1, result_<C>> {
    template <typename T>
    using f = dispatch<1, C>::template f<T::type>;
};

} // namespace impl

// call_ : a foundational metaclosure that immediately evaluates the input metaclosure(s).
export template <typename F, typename... Ts>
using call_ = impl::dispatch<impl::find_dispatch(sizeof...(Ts)), F>::template f<Ts...>;
export template <typename T, typename... Ts>
using call_t = impl::dispatch<impl::find_dispatch(sizeof...(Ts)), T>::template
                    f<Ts...>::type;
// call_f_ : 
export template <typename C = identity_>
struct call_f_ {};

// call_f_ : implementation
namespace impl {

template <std::size_t N, typename C>
struct dispatch<N, call_f_<C>> {
    template <typename F, typename... Ts>
    using f = dispatch<1, C>::template f<
                    typename dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>>;
};

} // namespace impl

// maybe_ metaclosure
namespace impl
{

template <bool B>
struct maybe_test_ {
    template <typename T>
    using f = T;
};
template <>
struct maybe_test_<true> {};
template <typename T> // TODO: Get rid of std::is_same_v here.
using maybe_impl = maybe_test_<std::is_same_v<T, nothing_>>::template f<T>;

} // namespace impl

export template <typename T, typename... Ts>
using maybe_ = impl::maybe_impl<typename impl::dispatch<impl::find_dispatch(sizeof...(Ts)), T>::template
                    f<Ts...>>;
export template <typename T, typename... Ts>
using maybe_t = impl::maybe_impl<typename impl::dispatch<impl::find_dispatch(sizeof...(Ts)), T>::template
                    f<Ts...>::type>;

} // namespace boost::tmp
