//  Copyright 2023 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef __BOOST_NTTMP_HPP
#define __BOOST_NTTMP_HPP

#if defined(__GNUC__) || defined(__clang__) || !defined(ENABLE_CPP_MODULE)
#include <cstdint>
#include <limits>
#define BOOST_TMP_EXPORT
#endif // defined(__GNUC__ ) || defined(__clang__)

#include "Boost.TMP.Base.hpp"
#include "Boost.TMP.hpp"

namespace boost::tmp {

BOOST_TMP_EXPORT using default_type_lookup_table_ =
    list_<
        list_<bool, lift_v_<bool_>>,
        list_<int,  lift_v_<int_>>,
        list_<unsigned int, lift_v_<uint_>>,
        list_<char, lift_v_<char_>>,
        list_<wchar_t, lift_v_<wchar_>>,
        list_<unsigned char, lift_v_<uchar_>>,
        list_<char8_t, lift_v_<char8_>>,
        list_<char16_t, lift_v_<char16_>>,
        list_<char32_t, lift_v_<char32_>>,
        list_<std::size_t, lift_v_<sizet_>>,
        list_<std::uint8_t, lift_v_<uint8_>>,
        list_<std::uint16_t, lift_v_<uint16_>>,
        list_<std::uint32_t, lift_v_<uint32_>>,
        list_<std::uint64_t, lift_v_<uint64_>>,
        list_<std::int8_t, lift_v_<int8_>>,
        list_<std::int16_t, lift_v_<int16_>>,
        list_<std::int32_t, lift_v_<int32_>>,
        list_<std::int64_t, lift_v_<int64_>>
    >;

BOOST_TMP_EXPORT template <typename F, auto... Vs>
using call_v_ = impl::dispatch<impl::find_dispatch(sizeof...(Vs)), F>::template f<Vs...>;

BOOST_TMP_EXPORT template <typename F, typename T, auto... Vs>
using call_tv_ = impl::dispatch<impl::find_dispatch(sizeof...(Vs) + 1), F>::template f<T, Vs...>;

BOOST_TMP_EXPORT template <auto... Vs>
struct call_vv_ {
    template<typename F>
    using f = impl::dispatch<impl::find_dispatch(sizeof...(Vs)), F>::template f<Vs...>;
};

// always_v_ : metaclosure returns NTTP / shovels the NTTP into the continuation C.
// Useful when a functional metaclosure is required, but you just want to use it
// to return a certain NTTP.
BOOST_TMP_EXPORT template <auto V, typename C = listify_v_>
struct always_v_ {};
namespace impl { // always_v_
    template <std::size_t N, auto V, typename C>
    struct dispatch<N, always_v_<V, C>> {
        template <auto...>
        using f = dispatch<1, C>::template f<V>;
    };
} // namespace impl

// drop_v_ : Remove N values from the front of the input VPP.
// Input params: Parameter value pack
// Closure params: N - Positive integer
//                 C - Continuation; default listify_v_
// Functional description:
// input  - T0, T1, ..., T(M), T(M + 1), ..., TN
// apply  - (drop M values)
// result - T(M), T(M + 1), ..., TN
// Empty return type: list_<>
BOOST_TMP_EXPORT template <std::size_t N, typename C = listify_v_>
struct drop_v_ {};
namespace impl { // drop_v_
    template <std::size_t, typename C>
    struct drop_v_impl;
    // TODO: Is this correct behavior for dropping nothing?
    template <typename C>
    struct drop_v_impl<0, C> {
        template <auto... Vs>
        using f = call_v_<C, Vs...>;
    };
    template <typename C>
    struct drop_v_impl<1, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<2, C> {
        template <auto V0, auto V1, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<3, C> {
        template <auto V0, auto V1, auto V2, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<4, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<5, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<6, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<7, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto V6, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<8, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto V6, auto V7, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<16, C> {
        template<auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                 auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                 auto V10, auto V11, auto V12, auto V13, auto V14,
                 auto V15, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<32, C> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15, auto V16, auto V17, auto V18, auto V19,
                  auto V20, auto V21, auto V22, auto V23, auto V24,
                  auto V25, auto V26, auto V27, auto V28, auto V29,
                  auto V30, auto V31, typename... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <typename C>
    struct drop_v_impl<64, C> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15, auto V16, auto V17, auto V18, auto V19,
                  auto V20, auto V21, auto V22, auto V23, auto V24,
                  auto V25, auto V26, auto V27, auto V28, auto V29,
                  auto V30, auto V31, auto V32, auto V33, auto V34,
                  auto V35, auto V36, auto V37, auto V38, auto V39,
                  auto V40, auto V41, auto V42, auto V43, auto V44,
                  auto V45, auto V46, auto V47, auto V48, auto V49,
                  auto V50, auto V51, auto V52, auto V53, auto V54,
                  auto V55, auto V56, auto V57, auto V58, auto V59,
                  auto V60, auto V61, auto V62, auto V63, auto... Vs>
        using f = dispatch<sizeof...(Vs), C>::template f<Vs...>;
    };
    template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
    struct make_drop_v : drop_v_impl<Step, drop_v_<(P - Step), C>> { /* not done */
    };
    template <std::size_t P, typename C>
    struct make_drop_v<P, C, P> : drop_v_impl<P, C> {};
    template <std::size_t N, std::size_t P, typename C>
    struct dispatch<N, drop_v_<P, C>> : make_drop_v<P, C> {};
} // namespace impl

// each_v_ : Given a VPP, apply a matching metaclosure to each value parameter.
// In other words, each VPP element gets its own corresponding metaclosure (Fs...).
// Input Parameters: VPP
// Closure Parameters: Fs... - Closures that map 1-to-1 to each element in VPP
// Output: Result of last closure in (Fs...) combining results of (Fs... - 1).
// Output type format: Depends on last metaclosure (Fs...); takes in result of every
// prior closure.
BOOST_TMP_EXPORT template <typename... Fs>
struct each_v_ {};
namespace impl { // each_
    template <typename F, typename C>
    struct dispatch<1, each_v_<F, C>> {
        template <auto V>
        using f = dispatch<1, C>::template f<typename dispatch<1, F>::template f<V>>;
    };
    template <typename F0, typename F1, typename C>
    struct dispatch<2, each_v_<F0, F1, C>> {
        template <auto V0, auto V1>
        using f = dispatch<2, C>::template f<typename dispatch<1, F0>::template f<V0>,
                                             typename dispatch<1, F1>::template f<V1>>;
    };
    template <typename F0, typename F1, typename F2, typename C>
    struct dispatch<3, each_v_<F0, F1, F2, C>> {
        template <auto V0, auto V1, auto V2>
        using f = dispatch<3, C>::template f<typename dispatch<1, F0>::template f<V0>,
                                             typename dispatch<1, F1>::template f<V1>,
                                             typename dispatch<1, F2>::template f<V2>>;
    };
    template <typename F0, typename F1, typename F2, typename F3, typename C>
    struct dispatch<4, each_v_<F0, F1, F2, F3, C>> {
        template <auto V0, auto V1, auto V2, auto V3>
        using f = dispatch<4, C>::template f<typename dispatch<1, F0>::template f<V0>,
                                             typename dispatch<1, F1>::template f<V1>,
                                             typename dispatch<1, F2>::template f<V2>,
                                             typename dispatch<1, F3>::template f<V3>>;
    };
} // namespace impl

// reverse_v_ : Reverse the order of the input VPP. 
// Input params: Value parameter pack
// Closure params: C - Continuation; default listify_v_
// Functional description:
// input  -  V0, V1, ..., VN
// apply  - (reverse element order of value parameter pack)
// result -  VN, ..., V1, V0
// Empty return type: list_<>
BOOST_TMP_EXPORT template <typename C = listify_v_>
struct reverse_v_ {};
namespace impl { // reverse_v_
    template<auto... Vs>
    struct reverse_v_impl {
        template <typename C, auto... Ws>
        using f = dispatch<
            find_dispatch(sizeof...(Vs) + sizeof...(Ws)), C>::template f<Vs..., Ws...>;
    };
    template <typename C>
    struct dispatch<0, reverse_v_<C>> {
        template <auto...>
        using f = dispatch<0, C>::template f<>;
    };
    template <typename C>
    struct dispatch<1, reverse_v_<C>> {
        template <auto V>
        using f = dispatch<1, C>::template f<V>;
    };
    template <typename C>
    struct dispatch<2, reverse_v_<C>> {
        template <auto V0, auto V1>
        using f = dispatch<2, C>::template f<V1, V0>;
    };
    template <typename C>
    struct dispatch<3, reverse_v_<C>> {
        template <auto V0, auto V1, auto V2>
        using f = dispatch<3, C>::template f<V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<4, reverse_v_<C>> {
        template <auto V0, auto V1, auto V2, auto V3>
        using f = dispatch<4, C>::template f<V3, V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<5, reverse_v_<C>> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4>
        using f = dispatch<5, C>::template f<V4, V3, V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<6, reverse_v_<C>> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4, auto V5>
        using f = dispatch<6, C>::template f<V5, V4, V3, V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<7, reverse_v_<C>> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto V6>
        using f = dispatch<7, C>::template f<V6, V5, V4, V3, V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<8, reverse_v_<C>> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto V6, auto V7>
        using f = dispatch<8, C>::template f<V7, V6, V5, V4, V3, V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<9, reverse_v_<C>> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto V6, auto V7, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)),
                            reverse_v_<lift_v_<reverse_v_impl>>>::template f<Vs...>::
                                template f<C, V7, V6, V5, V4, V3, V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<16, reverse_v_<C>> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15>
        using f = dispatch<16, C>::template f<V15, V14, V13, V12, V11, V10, V9, V8,
                                              V7,  V6,  V5,  V4,  V3,  V2,  V1, V0>;
    };
    template <typename C>
    struct dispatch<17, reverse_v_<C>> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)),
                                    reverse_v_<lift_v_<reverse_v_impl>>>::template f<Vs...>::
                template f<C, V15, V14, V13, V12, V11, V10, V9, V8, V7, V6, V5, V4, V3, V2, V1, V0>;
    };
    template <typename C>
    struct dispatch<32, reverse_v_<C>> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15, auto V16, auto V17, auto V18, auto V19,
                  auto V20, auto V21, auto V22, auto V23, auto V24,
                  auto V25, auto V26, auto V27, auto V28, auto V29,
                  auto V30, auto V31>
        using f = dispatch<32, C>::template f<V31, V30, V29, V28, V27, V26, V25, V24,
                                              V23, V22, V21, V20, V19, V18, V17, V16,
                                              V15, V14, V13, V12, V11, V10, V9,  V8,
                                              V7,  V6,  V5,  V4,  V3,  V2,  V1,  V0>;
    };
    template <typename C>
    struct dispatch<33, reverse_v_<C>> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15, auto V16, auto V17, auto V18, auto V19,
                  auto V20, auto V21, auto V22, auto V23, auto V24,
                  auto V25, auto V26, auto V27, auto V28, auto V29,
                  auto V30, auto V31, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), reverse_v_<lift_v_<reverse_v_impl>>>::template
                    f<Vs...>::template f<C, V31, V30, V29, V28, V27, V26, V25, V24,
                                            V23, V22, V21, V20, V19, V18, V17, V16,
                                            V15, V14, V13, V12, V11, V10, V9,  V8,
                                            V7,  V6,  V5,  V4,  V3,  V2,  V1,  V0>;
    };
    template <typename C>
    struct dispatch<64, reverse_v_<C>> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15, auto V16, auto V17, auto V18, auto V19,
                  auto V20, auto V21, auto V22, auto V23, auto V24,
                  auto V25, auto V26, auto V27, auto V28, auto V29,
                  auto V30, auto V31, auto V32, auto V33, auto V34,
                  auto V35, auto V36, auto V37, auto V38, auto V39,
                  auto V40, auto V41, auto V42, auto V43, auto V44,
                  auto V45, auto V46, auto V47, auto V48, auto V49,
                  auto V50, auto V51, auto V52, auto V53, auto V54,
                  auto V55, auto V56, auto V57, auto V58, auto V59,
                  auto V60, auto V61, auto V62, auto V63>
        using f = dispatch<16, C>::template f<V63, V62, V61, V60, V59, V58, V57, V56,
                                              V55, V54, V53, V52, V51, V50, V49, V48,
                                              V47, V46, V45, V44, V43, V42, V41, V40,
                                              V39, V38, V37, V36, V35, V34, V33, V32,
                                              V31, V30, V29, V28, V27, V26, V25, V24,
                                              V23, V22, V21, V20, V19, V18, V17, V16,
                                              V15, V14, V13, V12, V11, V10, V9,  V8,
                                              V7,  V6,  V5,  V4,  V3,  V2,  V1,  V0>;
    };
    template <typename C>
    struct dispatch<65, reverse_v_<C>> {
        template <auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                  auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                  auto V10, auto V11, auto V12, auto V13, auto V14,
                  auto V15, auto V16, auto V17, auto V18, auto V19,
                  auto V20, auto V21, auto V22, auto V23, auto V24,
                  auto V25, auto V26, auto V27, auto V28, auto V29,
                  auto V30, auto V31, auto V32, auto V33, auto V34,
                  auto V35, auto V36, auto V37, auto V38, auto V39,
                  auto V40, auto V41, auto V42, auto V43, auto V44,
                  auto V45, auto V46, auto V47, auto V48, auto V49,
                  auto V50, auto V51, auto V52, auto V53, auto V54,
                  auto V55, auto V56, auto V57, auto V58, auto V59,
                  auto V60, auto V61, auto V62, auto V63, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)),
                        reverse_v_<lift_v_<reverse_v_impl>>>::template f<Vs...>::template
                        f<C, V63, V62, V61, V60, V59, V58, V57, V56, V55, V54, V53, V52, V51, V50,
                             V49, V48, V47, V46, V45, V44, V43, V42, V41, V40, V39, V38, V37, V36,
                             V35, V34, V33, V32, V31, V30, V29, V28, V27, V26, V25, V24, V23, V22,
                             V21, V20, V19, V18, V17, V16, V15, V14, V13, V12, V11, V10, V9,  V8,
                             V7,  V6,  V5,  V4,  V3,  V2,  V1,  V0>;
    };
} // namespace impl

// rotate_v_ : Move the elements of the input VPP from right to left,
// cycling elements in the front to the back.
// Input Parameters: VPP
// Closure Parameters: N - Number of rotations; positive
//                     C - Continuation; default listify_v_
// Output: V0, V1, ..., VM
// (rotate N) ->
BOOST_TMP_EXPORT template <std::size_t N = 0, typename C = listify_v_>
struct rotate_v_ {};
namespace impl { // rotate_v_
    // TODO: Add more conditions.
    consteval auto select_rotation(int Rcount, int Vcount) {
        if(Rcount < 0) {
            return step_selector(Vcount + Rcount);
        }
        else if(Rcount > Vcount) {
            return step_selector(Rcount % Vcount);
        }
        else {
            return step_selector(Rcount);
        }
    }

    // rotate_v_ impl
    template <std::size_t P, typename C>
    struct rotate_v_impl;

    // rotate_v_ selection
    template<std::size_t P, typename C>
    struct rotate_v_selection {
        template<auto... Vs>
        using f = rotate_v_impl<select_rotation(P, sizeof...(Vs)), C>::template f<Vs...>;
    };

    template <typename C>
    struct rotate_v_impl<0, C> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<Vs...>;
    };
    template <typename C>
    struct rotate_v_impl<1, C> {
        template <auto V, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1), C>::template
                        f<Vs..., V>;
    };
    template <typename C>
    struct rotate_v_impl<2, C> {
        template <auto V0, auto V1, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 2), C>::template
                        f<Vs..., V0, V1>;
    };
    template <typename C>
    struct rotate_v_impl<3, C> {
        template <auto V0, auto V1, auto V2, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 3), C>::template
                        f<Vs..., V0, V1, V2>;
    };
    template <typename C>
    struct rotate_v_impl<4, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 4), C>::template
                        f<Vs..., V0, V1, V2, V3>;
    };
    template <typename C>
    struct rotate_v_impl<5, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                typename... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 5), C>::template
                        f<Vs..., V0, V1, V2, V3, V4>;
    };
    template <typename C>
    struct rotate_v_impl<6, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 6), C>::template
                        f<Vs..., V0, V1, V2, V3, V4, V5>;
    };
    template <typename C>
    struct rotate_v_impl<7, C> {
        template <auto V0, auto V1, auto V2, auto V3, auto V4,
                  auto V5, auto V6, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 7), C>::template
                        f<Vs..., V0, V1, V2, V3, V4, V5, V6>;
    };
    template <typename C>
    struct rotate_v_impl<8, C> {
        template<auto V0, auto V1, auto V2, auto V3, auto V4,
                 auto V5, auto V6, auto V7, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 8), C>::template
                        f<Vs..., V0, V1, V2, V3, V4, V5, V6, V7>;
    };
    template <typename C>
    struct rotate_v_impl<16, C> {
        template<auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                 auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                 auto V10, auto V11, auto V12, auto V13, auto V14,
                 auto V15, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 16), C>::template
                        f<Vs..., V0, V1, V2,  V3,  V4,  V5,  V6,  V7,
                                 V8, V9, V10, V11, V12, V13, V14, V15>;
    };
    template <typename C>
    struct rotate_v_impl<32, C> {
        template<auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                 auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                 auto V10, auto V11, auto V12, auto V13, auto V14,
                 auto V15, auto V16, auto V17, auto V18, auto V19,
                 auto V20, auto V21, auto V22, auto V23, auto V24,
                 auto V25, auto V26, auto V27, auto V28, auto V29,
                 auto V30, auto V31, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 32), C>::template
                        f<Vs..., V0,  V1,  V2,  V3,  V4,  V5,  V6, V7,
                                 V8,  V9,  V10, V11, V12, V13, V14, V15,
                                 V16, V17, V18, V19, V20, V21, V22, V23,
                                 V24, V25, V26, V27, V28, V29, V30, V31>;
    };
    template <typename C>
    struct rotate_v_impl<64, C> {
        template<auto V0,  auto V1,  auto V2,  auto V3,  auto V4,
                 auto V5,  auto V6,  auto V7,  auto V8,  auto V9,
                 auto V10, auto V11, auto V12, auto V13, auto V14,
                 auto V15, auto V16, auto V17, auto V18, auto V19,
                 auto V20, auto V21, auto V22, auto V23, auto V24,
                 auto V25, auto V26, auto V27, auto V28, auto V29,
                 auto V30, auto V31, auto V32, auto V33, auto V34,
                 auto V35, auto V36, auto V37, auto V38, auto V39,
                 auto V40, auto V41, auto V42, auto V43, auto V44,
                 auto V45, auto V46, auto V47, auto V48, auto V49,
                 auto V50, auto V51, auto V52, auto V53, auto V54,
                 auto V55, auto V56, auto V57, auto V58, auto V59,
                 auto V60, auto V61, auto V62, auto V63, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 64), C>::template
                        f<Vs..., V0,  V1,  V2,  V3,  V4,  V5,  V6,  V7,  V8,  V9,  V10,
                                 V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21,
                                 V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32,
                                 V33, V34, V35, V36, V37, V38, V39, V40, V41, V42, V43,
                                 V44, V45, V46, V47, V48, V49, V50, V51, V52, V53, V54,
                                 V55, V56, V57, V58, V59, V60, V61, V62, V63>;
    };
    template <std::size_t P, typename C>
    struct dispatch<0, rotate_v_<P, C>> {
        template <auto...>
        using f = dispatch<0, C>::template f<>;
    };
    template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
    struct make_rotate_v_
        : rotate_v_selection<step_selector(Step), rotate_v_<(P - Step), C>> { /* not done */
    };
    template <std::size_t P, typename C>
    struct make_rotate_v_<P, C, P> : rotate_v_selection<P, C> {};
    template <std::size_t N, std::size_t P, typename C>
    struct dispatch<N, rotate_v_<P, C>> : make_rotate_v_<P, C> {};
} // namespace impl

// join_v_ : Given a parameter pack consisting of list_v_'s, concatenate
// them all together into a single list_v_ in the order they are input.
BOOST_TMP_EXPORT template<typename C = listify_v_>
struct join_v_ {};
namespace impl { // join_v_
    template<template<auto...> typename C, typename...>
    struct joiner_v;

    template <template <auto...> class C,
                auto... V0s, auto... V1s, auto... V2s, auto... V3s,
                auto... V4s, auto... V5s, auto... V6s, auto... V7s>
    struct joiner_v<C, list_v_<V0s...>, list_v_<V1s...>, list_v_<V2s...>, list_v_<V3s...>,
                        list_v_<V4s...>, list_v_<V5s...>, list_v_<V6s...>, list_v_<V7s...>> {
        template <auto... Vs>
        using f = C<V0s..., V1s..., V2s..., V3s..., V4s..., V5s..., V6s..., V7s..., Vs...>;
    };
    template<template <auto...> class C,
            auto... V0s,  auto... V1s,  auto... V2s,  auto... V3s,
            auto... V4s,  auto... V5s,  auto... V6s,  auto... V7s,
            auto... V8s,  auto... V9s,  auto... V10s, auto... V11s,
            auto... V12s, auto... V13s, auto... V14s, auto... V15s,
            auto... V16s, auto... V17s, auto... V18s, auto... V19s,
            auto... V20s, auto... V21s, auto... V22s, auto... V23s,
            auto... V24s, auto... V25s, auto... V26s, auto... V27s,
            auto... V28s, auto... V29s, auto... V30s, auto... V31s>
    struct joiner_v<C, list_v_<V0s...>,  list_v_<V1s...>,  list_v_<V2s...>,  list_v_<V3s...>,
                    list_v_<V4s...>,  list_v_<V5s...>,  list_v_<V6s...>,  list_v_<V7s...>,
                    list_v_<V8s...>,  list_v_<V9s...>,  list_v_<V10s...>, list_v_<V11s...>,
                    list_v_<V12s...>, list_v_<V13s...>, list_v_<V14s...>, list_v_<V15s...>,
                    list_v_<V16s...>, list_v_<V17s...>, list_v_<V18s...>, list_v_<V19s...>,
                    list_v_<V20s...>, list_v_<V21s...>, list_v_<V22s...>, list_v_<V23s...>,
                    list_v_<V24s...>, list_v_<V25s...>, list_v_<V26s...>, list_v_<V27s...>,
                    list_v_<V28s...>, list_v_<V29s...>, list_v_<V30s...>, list_v_<V31s...>> {
        template <auto... Vs>
        using f = C<V0s...,  V1s...,  V2s...,  V3s...,  V4s...,  V5s...,  V6s...,  V7s...,
                    V8s...,  V9s...,  V10s..., V11s..., V12s..., V13s..., V14s..., V15s...,
                    V16s..., V17s..., V18s..., V19s..., V20s..., V21s..., V22s..., V23s...,
                    V24s..., V25s..., V26s..., V27s..., V28s..., V29s..., V30s..., V31s..., Vs...>;
    };
    
    template <std::size_t N>
    struct join_loop_v;
    template <>
    struct join_loop_v<1> {
        template <template <auto...> class C,
                typename LV0  = list_v_<>, typename LV1  = list_v_<>, typename LV2  = list_v_<>,
                typename LV3  = list_v_<>, typename LV4  = list_v_<>, typename LV5  = list_v_<>,
                typename LV6  = list_v_<>, typename LV7  = list_v_<>, typename LV8  = list_v_<>,
                typename LV9  = list_v_<>, typename LV10 = list_v_<>, typename LV11 = list_v_<>,
                typename LV12 = list_v_<>, typename LV13 = list_v_<>, typename LV14 = list_v_<>,
                typename LV15 = list_v_<>, typename LV16 = list_v_<>, typename LV17 = list_v_<>,
                typename LV18 = list_v_<>, typename LV19 = list_v_<>, typename LV20 = list_v_<>,
                typename LV21 = list_v_<>, typename LV22 = list_v_<>, typename LV23 = list_v_<>,
                typename LV24 = list_v_<>, typename LV25 = list_v_<>, typename LV26 = list_v_<>,
                typename LV27 = list_v_<>, typename LV28 = list_v_<>, typename LV29 = list_v_<>,
                typename LV30 = list_v_<>, typename LV31 = list_v_<>, typename... Ts>
        using f = join_loop_v<(sizeof...(Ts) > 8)>::template f<
                joiner_v<C, LV0,  LV1,  LV2,  LV3,  LV4,  LV5,  LV6,  LV7,  LV8,  LV9,  LV10, LV11, LV12, LV13,
                        LV14, LV15, LV16, LV17, LV18, LV19, LV20, LV21, LV22, LV23, LV24, LV25, LV26, LV27,
                        LV28, LV29, LV30, LV31>::template f, Ts...>;
    };
    template <>
    struct join_loop_v<0> {
        template <template <auto...> class C,
                typename LV0 = list_v_<>, typename LV1 = list_v_<>, typename LV2 = list_v_<>,
                typename LV3 = list_v_<>, typename LV4 = list_v_<>, typename LV5 = list_v_<>,
                typename LV6 = list_v_<>, typename LV7 = list_v_<>, typename LV8 = list_v_<>>
        using f = joiner_v<C, LV0, LV1, LV2, LV3, LV4, LV5, LV6, LV7>::template f<>;
    };

    template <std::size_t N, template <auto...> class C>
    struct dispatch<N, join_v_<lift_v_<C>>> {
        template <typename... VTs>
        using f = join_loop_v<(sizeof...(VTs) > 8)>::template f<C, VTs...>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, join_v_<C>> {
        template <typename... VTs>
        using f = join_loop_v<(
                sizeof...(VTs) > 8)>::template f<dispatch_unknown_v<C>::template f, VTs...>;
    };
} // namespace impl


// drop_last_v_ : Given an N >= 0, drop the last N elements off of an input VPP.
BOOST_TMP_EXPORT template<std::size_t N, typename C = listify_v_>
struct drop_last_v_ {};
namespace impl { // drop_last_
    template<std::size_t N, std::size_t DropN, typename C>
    struct dispatch<N, drop_last_v_<DropN, C>> : dispatch<N, reverse_v_<drop_v_<DropN, reverse_v_<C>>>> {};
} // namespace impl

// pop_front_v_ : Given an input VPP, remove the first element.
BOOST_TMP_EXPORT template <typename C = listify_v_>
struct pop_front_v_ {};
namespace impl { // pop_front_
    template <std::size_t N, typename C>
    struct dispatch<N, pop_front_v_<C>> {
        template <auto V, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<Vs...>;
    };
    // TODO: Should this be kept? This differs from the behavior of popping
    // the front off of an empty list (which results in an empty list).
    // This, however, will return a list_<nothing_>
    template <typename C>
    struct dispatch<0, pop_front_v_<C>> {
    template <auto... Vs>
    using f = dispatch<1, C>::template f<nothing_{}>;
};
} // namespace impl

// erase_v_ : Given an input VPP, erase the nth element in the VPP.
BOOST_TMP_EXPORT template <std::size_t N, typename C = listify_v_>
struct erase_v_ {};
namespace impl {
    // erase_v_
    template <std::size_t N, std::size_t I, typename C>
    struct dispatch<N, erase_v_<I, C>> {
        template <auto... Vs>
        using f = dispatch<N,
            rotate_v_<I,
                pop_front_v_<rotate_v_<(sizeof...(Vs) - I - 1), C>>>>::template f<Vs...>;
    };
    template <std::size_t I, typename C>
    struct dispatch<0, erase_v_<I, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<nothing_{}>;
    };
} // namespace impl

// filter_v_: Given an unary predicate F, keep elements from the input VPP
// satisfying F (reword: remove elements *not* satisfying F).
BOOST_TMP_EXPORT template <typename F, typename C = listify_v_>
struct filter_v_ {};
namespace impl { // filter_v_
    template <std::size_t N, template <auto...> class F, typename C>
    struct filtery_v;
    template <template <auto...> class F, typename C>
    struct filtery_v<0, F, C> {
        template <std::size_t N, auto V, auto U, auto... Vs>
        using f = filtery_v<(F<U>::value + 2 * (N == 1)), F,
                                    C>::template f<(N - 1), U, Vs...>;
    };
    template <template <auto...> class F, typename C>
    struct filtery_v<1, F, C> {
        template <std::size_t N, auto V, auto U, auto... Vs>
        using f = filtery_v<(F<U>::value + 2 * (N == 1)), F, C>::template
                        f<(N - 1), U, Vs..., V>;
    };
    template <template <auto...> class F, typename C>
    struct filtery_v<2, F, C> { // all the way around, remove last
        template <std::size_t N, auto V, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<Vs...>;
    };
    template <template <auto...> class F, typename C>
    struct filtery_v<3, F, C> { // all the way around, keep last
        template <std::size_t N, auto V, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1), C>::template f<Vs..., V>;
    };
    template <std::size_t N, template <auto...> class F, typename C>
    struct dispatch<N, filter_v_<lift_v_<F>, C>> {
        template <auto V, auto... Vs>
        using f = filtery_v<(F<V>::value + 2 * (sizeof...(Vs) == 0)), F,
                                    C>::template f<(sizeof...(Vs)), V, Vs...>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, filter_v_<F, C>> {
        template <auto V, auto... Vs>
        using f = filtery_v<
                (dispatch<1, F>::template f<V>::value + 2 * (sizeof...(Vs) == 0)),
                dispatch<1, F>::template f, C>::template f<(sizeof...(Vs)), V, Vs...>;
    };
    template <typename F, typename C>
    struct dispatch<0, filter_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<0, C>::template f<>;
    };
    template <template <auto...> class F, typename C>
    struct dispatch<0, filter_v_<lift_v_<F>, C>> {
        template <auto... Vs>
        using f = dispatch<0, C>::template f<>;
    };
} // namespace impl

/// fold_left_v_ : folds left over a list using a binary predicate /
/// fold left considers the first element in the input pack the initial state, use
/// `push_front_v_<>` to add initial state if needed
/// Multiple input, single output
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
struct fold_left_v_ {};
namespace impl { // fold_left_v_
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<0, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <auto...>
        using f = nothing_;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<1, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <auto V>
        using f = C<list_v_<V>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<2, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0>
        using f = C<F<In, V0>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<3, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0, auto V1>
        using f = C<F<F<In, V0>, V1>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<4, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0, auto V1, auto V2>
        using f = C<F<F<F<In, V0>, V1>, V2>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<5, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0, auto V1, auto V2, auto V3>
        using f = C<F<F<F<F<In, V0>, V1>, V2>, V3>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<6, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0, auto V1, auto V2, auto V3,
                auto V4>
        using f = C<F<F<F<F<F<In, V0>, V1>, V2>, V3>, V4>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<7, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0, auto V1, auto V2, auto V3,
                auto V4, auto V5>
        using f = C<F<F<F<F<F<F<In, V0>, V1>, V2>, V3>, V4>, V5>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<8, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0, auto V1, auto V2, auto V3,
                auto V4, auto V5, auto V6>
        using f = C<F<F<F<F<F<F<F<In, V0>, V1>, V2>, V3>, V4>, V5>, V6>>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<9, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In, auto V0, auto V1, auto V2, auto V3,
                auto V4, auto V5, auto V6, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1),
                                    fold_left_v_<lift_tv_<F>, lift_<C>>>::
                template f<F<F<F<F<F<F<F<In, V0>, V1>, V2>, V3>, V4>, V5>, V6>, Vs...>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<16, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template <typename In,  auto V0,  auto V1,  auto V2,  auto V3,
                auto V4,  auto V5,  auto V6,  auto V7,  auto V8,
                auto V9,  auto V10, auto V11, auto V12, auto V13,
                auto V14, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1), fold_left_v_<lift_tv_<F>, lift_<C>>>::template
                    f<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In, V0>,
                                                  V1>,
                                                V2>,
                                              V3>,
                                            V4>,
                                          V5>,
                                        V6>,
                                      V7>,
                                    V8>,
                                  V9>,
                                V10>,
                              V11>,
                            V12>,
                          V13>,
                        V14>,
                      Vs...>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<17, fold_left_v_<lift_tv_<F>, lift_<C>>>
        : dispatch<16, fold_left_v_<lift_tv_<F>, lift_<C>>> {};
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<32, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template<typename In,  auto V0,  auto V1,  auto V2,  auto V3,
                auto V4,  auto V5,  auto V6,  auto V7,  auto V8,
                auto V9,  auto V10, auto V11, auto V12, auto V13,
                auto V14, auto V15, auto V16, auto V17, auto V18,
                auto V19, auto V20, auto V21, auto V22, auto V23,
                auto V24, auto V25, auto V26, auto V27, auto V28,
                auto V29, auto V30, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1),
                    fold_left_v_<lift_tv_<F>, lift_<C>>>::template
                    f<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In, V0>,
                                                                                  V1>,
                                                                                V2>,
                                                                              V3>,
                                                                            V4>,
                                                                          V5>,
                                                                        V6>,
                                                                      V7>,
                                                                    V8>,
                                                                  V9>,
                                                                V10>,
                                                              V11>,
                                                            V12>,
                                                          V13>,
                                                        V14>,
                                                      V15>,
                                                    V16>,
                                                  V17>,
                                                V18>,
                                              V19>,
                                            V20>,
                                          V21>,
                                        V22>,
                                      V23>,
                                    V24>,
                                  V25>,
                                V26>,
                              V27>,
                            V28>,
                          V29>,
                        V30>,
                      Vs...>;
    };
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<33, fold_left_v_<lift_tv_<F>, lift_<C>>>
        : dispatch<32, fold_left_v_<lift_tv_<F>, lift_<C>>> {};
    template <template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<64, fold_left_v_<lift_tv_<F>, lift_<C>>> {
        template<typename In,  auto V0,  auto V1,  auto V2,  auto V3,
                auto V4,  auto V5,  auto V6,  auto V7,  auto V8,
                auto V9,  auto V10, auto V11, auto V12, auto V13,
                auto V14, auto V15, auto V16, auto V17, auto V18,
                auto V19, auto V20, auto V21, auto V22, auto V23,
                auto V24, auto V25, auto V26, auto V27, auto V28,
                auto V29, auto V30, auto V31, auto V32, auto V33,
                auto V34, auto V35, auto V36, auto V37, auto V38,
                auto V39, auto V40, auto V41, auto V42, auto V43,
                auto V44, auto V45, auto V46, auto V47, auto V48,
                auto V49, auto V50, auto V51, auto V52, auto V53,
                auto V54, auto V55, auto V56, auto V57, auto V58,
                auto V59, auto V60, auto V61, auto V62, auto V63,
                auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1),
                fold_left_v_<lift_tv_<F>, lift_<C>>>::
        template f<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<F<In,
                                                                                                                                                   V0>,
                                                                                                                                                 V1>,
                                                                                                                                               V2>,
                                                                                                                                             V3>,
                                                                                                                                           V4>,
                                                                                                                                         V5>,
                                                                                                                                       V6>,
                                                                                                                                     V7>,
                                                                                                                                   V8>,
                                                                                                                                 V9>,
                                                                                                                               V10>,
                                                                                                                             V11>,
                                                                                                                           V12>,
                                                                                                                         V13>,
                                                                                                                       V14>,
                                                                                                                     V15>,
                                                                                                                   V16>,
                                                                                                                 V17>,
                                                                                                               V18>,
                                                                                                             V19>,
                                                                                                           V20>,
                                                                                                         V21>,
                                                                                                       V22>,
                                                                                                     V23>,
                                                                                                   V24>,
                                                                                                 V25>,
                                                                                               V26>,
                                                                                             V27>,
                                                                                           V28>,
                                                                                         V29>,
                                                                                       V30>,
                                                                                     V31>,
                                                                                   V32>,
                                                                                 V33>,
                                                                               V34>,
                                                                             V35>,
                                                                           V36>,
                                                                         V37>,
                                                                       V38>,
                                                                     V39>,
                                                                   V40>,
                                                                 V41>,
                                                               V42>,
                                                             V43>,
                                                           V44>,
                                                         V45>,
                                                       V46>,
                                                     V47>,
                                                   V48>,
                                                 V49>,
                                               V50>,
                                             V51>,
                                           V52>,
                                         V53>,
                                       V54>,
                                     V55>,
                                   V56>,
                                 V57>,
                               V58>,
                             V59>,
                           V60>,
                         V61>,
                       V62>,
                     V63>,
                   Vs...>;
    };
    template <std::size_t N, template<typename, auto...> typename F, template <typename...> class C>
    struct dispatch<N, fold_left_v_<lift_tv_<F>, lift_<C>>>
        : dispatch<64, fold_left_v_<lift_tv_<F>, lift_<C>>> {};

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, fold_left_v_<F, C>>
        : dispatch<N, fold_left_v_<lift_<dispatch<2, F>::template f>,
                                    lift_<dispatch<1, C>::template f>>> {};
    template <std::size_t N, template <typename, auto...> class F, typename C>
    struct dispatch<N, fold_left_v_<lift_tv_<F>, C>>
        : dispatch<N, fold_left_v_<lift_tv_<F>, lift_<dispatch<1, C>::template f>>> {};
    template <std::size_t N, typename F, template <typename...> class C>
    struct dispatch<N, fold_left_v_<F, lift_<C>>>
        : dispatch<N, fold_left_v_<lift_tv_<dispatch<2, F>::template f>, lift_<C>>> {};
} // namespace impl

// \brief turns a list of types into a variadic pack of those types /
// example: call<all<>,true_,false_,true_> is equivalent to
// call<unpack<all<>>,list<true_,false_,true_>>
// \requirement
// Unpack always needs a continuation, so even if you're just unpacking
// a list, you need to use it like the following:
// using alist = list_v_<0>;
// 0 = call_<unpack_v_<identity_>, alist>{}; // This will be vaild
BOOST_TMP_EXPORT template <typename C>
struct unpack_v_ {};
namespace impl { // unpack_v_
    template <typename C, typename L>
    struct unpack_impl_v;
    template <typename C, template <auto...> class Seq, auto... Ls>
    struct unpack_impl_v<C, Seq<Ls...>> {
        using type = dispatch<find_dispatch(sizeof...(Ls)), C>::template f<Ls...>;
    };
    // in case of nothing_ input give a nothing_ output
    template <typename C>
    struct unpack_impl_v<C, nothing_> {
        using type = dispatch<1, C>::template f<nothing_{}>;
    };
    template <typename C>
    struct dispatch<1, unpack_v_<C>> {
        template <typename L>
        using f = unpack_impl_v<C, L>::type;
    };
} // namespace impl

BOOST_TMP_EXPORT template<std::size_t I, typename C = listify_v_>
struct index_v_ {};
BOOST_TMP_EXPORT template<std::size_t I, typename C = listify_v_>
using unpack_index_v_ = unpack_v_<index_v_<I, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using front_v_ = index_v_<0, C>;

BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv0_ = index_v_<0, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv1_ = index_v_<1, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv2_ = index_v_<2, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv3_ = index_v_<3, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv4_ = index_v_<4, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv5_ = index_v_<5, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv6_ = index_v_<6, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using iv7_ = index_v_<7, C>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv0_ = unpack_<index_v_<0, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv1_ = unpack_<index_v_<1, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv2_ = unpack_<index_v_<2, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv3_ = unpack_<index_v_<3, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv4_ = unpack_<index_v_<4, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv5_ = unpack_<index_v_<5, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv6_ = unpack_<index_v_<6, C>>;
BOOST_TMP_EXPORT template<typename C = listify_v_>
using uiv7_ = unpack_<index_v_<7, C>>;
namespace impl { // index_v_
    // TODO: Use a "mechanical" method for this instead of using other metaclosures.
    template <std::size_t N, std::size_t I, typename C>
    struct dispatch<N, index_v_<I, C>> : dispatch<N, drop_v_<I, front_v_<C>>> {};

    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<std::numeric_limits<std::size_t>::max(), C>> { // 
        template <auto... Vs>
        using f = dispatch<1, C>::template f<nothing_{}>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<0, C>> {
        template <auto V0, auto... Vs>
        using f = dispatch<1, C>::template f<V0>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<1, C>> {
        template <auto V0, auto V1, auto... Vs>
        using f = dispatch<1, C>::template f<V1>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<2, C>> {
        template <auto V0, auto V1, auto V2, auto... Vs>
        using f = dispatch<1, C>::template f<V2>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<3, C>> {
        template <auto V0, auto V1, auto V2, auto V3, auto... Vs>
        using f = dispatch<1, C>::template f<V3>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<4, C>> {
        template<auto V0, auto V1, auto V2, auto V3,
                 auto V4, auto... Vs>
        using f = dispatch<1, C>::template f<V4>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<5, C>> {
        template<auto V0, auto V1, auto V2, auto V3,
                 auto V4, auto V5, auto... Vs>
        using f = dispatch<1, C>::template f<V5>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<6, C>> {
        template<auto V0, auto V1, auto V2, auto V3,
                 auto V4, auto V5, auto V6, auto... Vs>
        using f = dispatch<1, C>::template f<V6>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<7, C>> {
    template <auto V0, auto V1, auto V2, auto V3,
              auto V4, auto V5, auto V6, auto V7, auto... Vs>
    using f = dispatch<1, C>::template f<V7>;
};
} // namespace impl

// is_not_v_ : 
BOOST_TMP_EXPORT template <auto P, typename C = listify_v_>
struct is_not_v_ {};
namespace impl { // is_v_
    template <auto P, typename C>
    struct dispatch<1, is_not_v_<P, C>> {
        template <auto T>
        using f = dispatch<1, C>::template f<(P != T)>;
    };
} // namespace impl

// less_f_v_ : 
BOOST_TMP_EXPORT template <typename F, typename C = listify_v_>
struct less_f_v_ {};
namespace impl { // less_f_
    template <template<auto...> typename F, typename C>
    struct dispatch<2, less_f_v_<lift_v_<F>, C>> {
        template<auto T, auto U>
        using f = dispatch<1, C>::template f<(F<T>::value < F<U>::value)>;
    };
} // namespace impl

// not_v_ : 
BOOST_TMP_EXPORT template <typename C = listify_v_>
struct not_v_ {};
namespace impl { // not_v_
    template <typename C>
    struct dispatch<1, not_v_<C>> {
        template <auto V>
        using f = dispatch<1, C>::template f<(!V)>;
    };
} // namespace impl

// pop_back_v_ :
BOOST_TMP_EXPORT template <typename C = listify_v_>
struct pop_back_v_ {};
namespace impl { // pop_back_v_
    template<std::size_t N, typename C>
    struct dispatch<N, pop_back_v_<C>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), rotate_v_<sizeof...(Vs) - 1, pop_front_v_<
                        rotate_v_<(sizeof...(Vs) - 1), C>>>>::template f<Vs...>;
    };
    // TODO: Should this be the default behavior for no value?
    template <typename C>
    struct dispatch<0, pop_back_v_<C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<nothing_{}>;
    };
} // namespace impl

// push_back_v_ :
BOOST_TMP_EXPORT template <auto V, typename C = listify_v_>
struct push_back_v_ {};
namespace impl { // push_back_v_
    template <std::size_t N, auto V, typename C>
    struct dispatch<N, push_back_v_<V, C>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1), C>::template f<Vs..., V>;
    };
} // namespace impl

// push_front_v_ : Given a value V, push this value to the front of the value
// parameter pack input.
BOOST_TMP_EXPORT template <auto V = nothing_{}, typename C = listify_v_>
struct push_front_v_ {};
namespace impl { // push_front_v_
    template <std::size_t N, auto V, typename C>
    struct dispatch<N, push_front_v_<V, C>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1), C>::template f<V, Vs...>;
    };
    template <std::size_t N, typename C>
    struct dispatch<N, push_front_v_<nothing_{}, C>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<Vs...>;
    };
} // namespace impl

// range_lo_hi_v_ : 
BOOST_TMP_EXPORT template <auto LV, auto UV, typename C = listify_v_>
struct range_lo_hi_v_ {};
namespace impl { // range_lo_hi_v_
    template <auto Lower, auto Upper, typename C>
    struct dispatch<1, range_lo_hi_v_<Lower, Upper, C>> {
        template<auto T>
        using f = dispatch<1, C>::template f<!((Lower < T) && (T < Upper))>;
};

} // namespace impl

// repeat_sequence_ :
BOOST_TMP_EXPORT template<std::size_t N = 0, typename C = listify_v_>
struct repeat_sequence_v_{};
namespace impl { // repeat_sequence_
    template <std::size_t, typename C>
    struct repeat_seq_impl_v;
    template <typename C>
    struct repeat_seq_impl_v<0, C> {
        template <auto...>
        using f = dispatch<0, C>::template f<>;
    };
    template <typename C>
    struct repeat_seq_impl_v<1, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 1, C>::template f<V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<2, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 2, C>::template f<V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<3, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 3, C>::template f<V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<4, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 4, C>::template f<V, V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<5, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 5, C>::template f<V, V, V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<6, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 6, C>::template f<V, V, V, V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<7, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 7, C>::template f<V, V, V, V, V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<8, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 8, C>::template f<V, V, V, V, V, V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<16, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 16, C>::template f<V, V, V, V, V, V, V, V,
                                                            V, V, V, V, V, V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<32, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 32, C>::template f<V, V, V, V, V, V, V, V,
                                                            V, V, V, V, V, V, V, V,
                                                            V, V, V, V, V, V, V, V,
                                                            V, V, V, V, V, V, V, V, Vs...>;
    };
    template <typename C>
    struct repeat_seq_impl_v<64, C> {
        template <auto V, auto... Vs>
        using f = dispatch<sizeof...(Vs) + 64, C>::template f<
                V, V, V, V, V, V, V, V,
                V, V, V, V, V, V, V, V,
                V, V, V, V, V, V, V, V,
                V, V, V, V, V, V, V, V,
                V, V, V, V, V, V, V, V,
                V, V, V, V, V, V, V, V,
                V, V, V, V, V, V, V, V,
                V, V, V, V, V, V, V, V, Vs...>;
    };
    template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
    struct make_repeat_v : repeat_seq_impl_v<Step, repeat_sequence_v_<(P - Step) + 1, C>> {};
    template <std::size_t P, typename C>
    struct make_repeat_v<P, C, P> : repeat_seq_impl_v<P, C> {};
    template <std::size_t N, std::size_t P, typename C>
    struct dispatch<N, repeat_sequence_v_<P, C>> : make_repeat_v<P, C> {};
} // namespace impl

// TODO: finish find_v_
// BOOST_TMP_EXPORT template <typename M, typename C = identity_>
// struct find_v_ {};
// namespace impl {
//     template<std::size_t I, auto Vs>
//     using index_helper_v = call_v_<unpack_index_v_<I>, Vs>;
//     template<std::size_t N, typename M, typename C>
//     struct dispatch<N, find_v_<M, C>> {
//         template<auto V>
//         using f = dispatch<N, unpack_v_<tee_v_<keys_<find_if_v_<is_v_<V>>>, values_v_<>, lift_<index_helper, C>>>>::template f<M>;
//     };
// } // namespace impl

// find_if_ : Given an input VPP, return the index of the type that satisfies the
// unary predicate.
BOOST_TMP_EXPORT template <typename UnaryPredicate, typename C = identity_>
struct find_if_v_ {};
namespace impl { // find_if_v_
    template <bool Found, std::size_t At, template <auto...> class F>
    struct county_v {
        static constexpr auto value{std::numeric_limits<std::size_t>::max()};
        template <auto V>
        using f = county_v<F<V>::value, (At + 1), F>;
    };
    template <std::size_t At, template <auto...> class F>
    struct county_v<true, At, F> {
        template <auto V>
        using f                    = county_v;
        static constexpr std::size_t value = At;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, find_if_v_<F, C>> {
        template <auto... Vs>
        using f = typename dispatch<1, C>::template f<
                        typename foldey<select_foldey_loop(sizeof...(Vs))>::template f<
                        county_v<false,
                                std::numeric_limits<std::size_t>::max(),
                                dispatch<1, F>::template f>, 0, Vs...>>;
    };
    template <std::size_t N, template <auto...> class F, typename C>
    struct dispatch<N, find_if_v_<lift_v_<F>, C>> {
            template <auto... Vs>
            using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
                        sizeof...(Vs))>::template f<county_v<false,
                                                            std::numeric_limits<std::size_t>::max(),
                                                            F>, 0, Vs...>>;
    };
} // namespace impl

// tee_v_ : Given a set of NTTP metaclosures, pipe the input VPP to 
// each metaclosure (Fs...), with the last metaclosure being a metaclosure
// that combines the results of each metaclosure together. This can be a join_v_,
// listify_v_, or metaclosure that takes a specific number of parameters.
// However it is done, it is *necessary* to do so as it essentially a Continuation
// metaclosure.
BOOST_TMP_EXPORT template <typename... Fs>
struct tee_v_ {};
namespace impl { // tee_v_
    template <typename N, typename L, typename C, typename... Fs>
    struct tee_impl_v {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                    typename dispatch<find_dispatch(sizeof...(Vs)), Fs>::template f<Vs...>...,
                    typename dispatch<find_dispatch(sizeof...(Vs)), L>::template f<Vs...>>;
    };
    // specialization for case where last closure is a forward
    template <typename N, typename C, typename... Fs>
    struct tee_impl_v<N, identity_, C, Fs...> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Fs) + sizeof...(Vs)), C>::template
                    f<dispatch<find_dispatch(sizeof...(Vs)), Fs>::template f<Vs...>...,
                            Vs...>;
    };
    template <typename L, typename C, typename... Fs>
    struct tee_impl_v<sizet_<1>, L, C, Fs...> {
        template <auto V0>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                    typename dispatch<1, Fs>::template f<V0>...,
                    typename dispatch<1, L>::template f<V0>>;
    };
    // specialization for case where last closure is a forward
    template <typename C, typename... Fs>
    struct tee_impl_v<sizet_<1>, identity_, C, Fs...> {
        template <auto V0>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                    typename dispatch<1, Fs>::template f<V0>..., V0>;
    };
    template <typename L, typename C, typename... Fs>
    struct tee_impl_v<sizet_<2>, L, C, Fs...> {
        template <auto V0, auto V1>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template
                        f<typename dispatch<2, Fs>::template f<V0, V1>...,
                        typename dispatch<2, L>::template f<V0, V1>>;
    };
    // specialization for case where last closure is a forward
    template <typename C, typename... Fs>
    struct tee_impl_v<sizet_<2>, identity_, C, Fs...> {
        template <auto V0, auto V1>
        using f = dispatch<find_dispatch(sizeof...(Fs) + 2), C>::template f<
                    typename dispatch<2, Fs>::template f<V0, V1>..., V0, V1>;
    };

    // in case the continuation is an and_

    // template <bool b, typename C, typename... Fs>
    // struct tee_and_impl;
    // template <typename C, typename... Fs>
    // struct tee_and_impl<false, C, Fs...> {
    //     template <typename... Ts>
    //     using f = dispatch<1, C>::template f<false_>;
    // };
    // template <typename C, typename... Fs>
    // struct tee_and_impl<true, C, Fs...> {
    //     template <typename... Ts>
    //     using f = dispatch<1, C>::template f<true_>;
    // };
    // template <typename C, typename F, typename... Fs>
    // struct tee_and_impl<true, C, F, Fs...> {
    //     template <typename... Ts>
    //     using f = tee_and_impl<dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
    //             Fs...>::template f<Ts...>;
    // };
    // template <bool b, typename C, typename... Fs>
    // struct tee_and_impl_1;
    // template <typename C, typename... Fs>
    // struct tee_and_impl_1<false, C, Fs...> {
    //     template <typename T0>
    //     using f = dispatch<1, C>::template f<false_>;
    // };
    // template <typename C, typename... Fs>
    // struct tee_and_impl_1<true, C, Fs...> {
    //     template <typename T0>
    //     using f1 = dispatch<1, C>::template f<true_>;
    // };
    // template <typename C, typename F, typename... Fs>
    // struct tee_and_impl_1<true, C, F, Fs...> {
    //     template <typename T0>
    //     using f = tee_and_impl<dispatch<1, F>::template f<T0>::value, C,
    //                                     Fs...>::template f<T0>;
    // };
    // template <bool b, typename C, typename... Fs>
    // struct tee_and_impl_2;
    // template <typename C, typename... Fs>
    // struct tee_and_impl_2<false, C, Fs...> {
    //     template <typename T0, typename T1>
    //     using f = dispatch<1, C>::template f<false_>;
    // };
    // template <typename C, typename... Fs>
    // struct tee_and_impl_2<true, C, Fs...> {
    //     template <typename T0, typename T1>
    //     using f = dispatch<1, C>::template f<true_>;
    // };
    // template <typename C, typename F, typename... Fs>
    // struct tee_and_impl_2<true, C, F, Fs...> {
    //     template <typename T0, typename T1>
    //     using f = tee_and_impl<dispatch<2, F>::template f<T0, T1>::value, C,
    //                                     Fs...>::template f<T0, T1>;
    // };

    // template <typename N, typename L, typename C, typename... Fs>
    // struct tee_impl<N, L, and_<identity_, C>, Fs...> : tee_and_impl<true, C, Fs..., L> {};
    // template <typename L, typename C, typename... Fs>
    // struct tee_impl<sizet_<1>, L, and_<identity_, C>, Fs...>
    //         : tee_and_impl_1<true, C, Fs..., L> {};
    // template <typename C, typename... Fs>
    // struct tee_impl<sizet_<1>, identity_, and_<identity_, C>, Fs...>
    //         : tee_and_impl_1<true, C, Fs..., identity_> {};
    // template <typename L, typename C, typename... Fs>
    // struct tee_impl<sizet_<2>, L, and_<identity_, C>, Fs...>
    //         : tee_and_impl_2<true, C, Fs..., L> {};
    // template <typename C, typename... Fs>
    // struct tee_impl<sizet_<2>, identity_, and_<identity_, C>, Fs...>
    //         : tee_and_impl_2<true, C, Fs..., identity_> {};

    // in case the continuation is an or_

    // template <bool b, typename C, typename... Fs>
    // struct tee_or_impl;
    // template <typename C, typename... Fs>
    // struct tee_or_impl<true, C, Fs...> {
    //     template <typename... Ts>
    //     using f = dispatch<1, C>::template f<true_>;
    // };
    // template <typename C, typename... Fs>
    // struct tee_or_impl<false, C, Fs...> {
    //     template <typename... Ts>
    //     using f = dispatch<1, C>::template f<false_>;
    // };
    // template <typename C, typename F, typename... Fs>
    // struct tee_or_impl<false, C, F, Fs...> {
    //     template <typename... Ts>
    //     using f = tee_or_impl<
    //             dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
    //             Fs...>::template f<Ts...>;
    // };
    // template <bool b, typename C, typename... Fs>
    // struct tee_or_impl_1;
    // template <typename C, typename... Fs>
    // struct tee_or_impl_1<true, C, Fs...> {
    //     template <typename T0>
    //     using f = dispatch<1, C>::template f<true_>;
    // };
    // template <typename C, typename... Fs>
    // struct tee_or_impl_1<false, C, Fs...> {
    //     template <typename T0>
    //     using f1 = dispatch<1, C>::template f<false_>;
    // };
    // template <typename C, typename F, typename... Fs>
    // struct tee_or_impl_1<false, C, F, Fs...> {
    //     template <typename T0>
    //     using f = tee_or_impl<dispatch<1, F>::template f<T0>::value, C,
    //                                     Fs...>::template f<T0>;
    // };
    // template <bool b, typename C, typename... Fs>
    // struct tee_or_impl_2;
    // template <typename C, typename... Fs>
    // struct tee_or_impl_2<true, C, Fs...> {
    //     template <typename T0, typename T1>
    //     using f = dispatch<1, C>::template f<true_>;
    // };
    // template <typename C, typename... Fs>
    // struct tee_or_impl_2<false, C, Fs...> {
    //     template <typename T0, typename T1>
    //     using f = dispatch<1, C>::template f<false_>;
    // };
    // template <typename C, typename F, typename... Fs>
    // struct tee_or_impl_2<false, C, F, Fs...> {
    //     template <typename T0, typename T1>
    //     using f = tee_or_impl<dispatch<2, F>::template f<T0, T1>::value, C,
    //                                     Fs...>::template f<T0, T1>;
    // };

    // template <typename N, typename L, typename C, typename... Fs>
    // struct tee_impl<N, L, or_<identity_, C>, Fs...> : tee_or_impl<false, C, Fs..., L> {};
    // template <typename L, typename C, typename... Fs>
    // struct tee_impl<sizet_<1>, L, or_<identity_, C>, Fs...>
    //         : tee_or_impl_1<false, C, Fs..., L> {};
    // template <typename C, typename... Fs>
    // struct tee_impl<sizet_<1>, identity_, or_<identity_, C>, Fs...>
    //         : tee_or_impl_1<false, C, Fs..., identity_> {};
    // template <typename L, typename C, typename... Fs>
    // struct tee_impl<sizet_<2>, L, or_<identity_, C>, Fs...>
    //         : tee_or_impl_2<false, C, Fs..., L> {};

    template <std::size_t N, typename F0, typename F1, typename... Fs>
    struct dispatch<N, tee_v_<F0, F1, Fs...>>
        : dispatch<find_dispatch(sizeof...(Fs) + 2),
                    rotate_<sizet_<sizeof...(Fs)>, push_front_<sizet_<N>, lift_<tee_impl_v>>>>::
                    template f<F0, F1, Fs...> {};
} // namespace impl

// insert_v_ : Given an input VPP, insert the NTTP (V) at index (N).
BOOST_TMP_EXPORT template <std::size_t N, auto V, typename C = listify_v_>
struct insert_v_ {};
namespace impl { // insert_v_
    template <std::size_t N, std::size_t I, auto V, typename C>
    struct dispatch<N, insert_v_<I, V, C>> {
        template <auto... Vs>
        using f = dispatch<N, rotate_v_<I, push_front_v_<V, rotate_v_<(sizeof...(Vs) - I + 1),
                                                        C>>>>::template f<Vs...>;
    };
    template <std::size_t I, auto V, typename C>
    struct dispatch<0, insert_v_<I, V, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<V>;
    };
} // namespace impl

// foldey_v is an internal only helper metaclosure 
template <std::size_t S>
struct foldey_v {
    template <typename F, std::size_t N, auto...>
    using f = sizet_<N - S>;
};
template <>
struct foldey_v<1000> {
    template <typename F, std::size_t N, auto... Vs>
    using f = nothing_;
};
template <>
struct foldey_v<1001> {
    template <typename F, std::size_t N, auto V0, auto... Vs> 
    using f = foldey_v<select_foldey(1, sizeof...(Vs), F::template f<V0>::value)>::template f<F, N + 1, Vs...>;
};
template <>
struct foldey_v<1008> {
    template <typename F, std::size_t N, auto V0, auto V1, auto V2,
              auto V3, auto V4, auto V5, auto V6, auto V7,
              auto... Vs>
    using f = foldey_v<select_foldey(8, sizeof...(Vs),
                F::template
                  f<V0>::template
                    f<V1>::template
                      f<V2>::template
                        f<V3>::template
                          f<V4>::template
                            f<V5>::template
                              f<V6>::template
                                f<V7>::value)>::template
                                  f<F, N + 8, Vs...>;
};
template <>
struct foldey_v<1000000> {};

// find_if_not_v_ : 
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = identity_>
struct find_if_not_v_ {};
namespace impl { // find_if_not_v_
    template <bool Found, std::size_t At, template <auto...> class F>
    struct county_not_v {
        static constexpr auto value{std::numeric_limits<std::size_t>::max()};
        template <auto V>
        using f = county_not_v<F<V>::value, (At + 1), F>;
    };
    template <std::size_t At, template <auto...> class F>
    struct county_not_v<false, At, F> {
        template <typename T>
        using f                    = county_not_v;
        static constexpr std::size_t value = At;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, find_if_not_v_<F, C>> {
        template <auto... Vs>
        using f = typename dispatch<1, C>::template f<
                        foldey_v<select_foldey_loop(sizeof...(Vs))>::template f<
                        county_not_v<true,
                                std::numeric_limits<std::size_t>::max(),
                                dispatch<1, F>::template f>, 0, Vs...>>;
    };
    template <std::size_t N, template <auto...> class F, typename C>
    struct dispatch<N, find_if_not_v_<lift_v_<F>, C>> {
            template <auto... Vs>
            using f = typename dispatch<1, C>::template f<typename foldey_v<select_foldey_loop(
                        sizeof...(Vs))>::template f<county_not_v<true,
                                                            std::numeric_limits<std::size_t>::max(),
                                                            F>, 0, Vs...>>;
    };
} // namespace impl

// or_v_ : Given an input VPP, 
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
struct or_v_ {};
namespace impl { // or_v_

    template<typename LV>
    struct ory_v_helper;

    template<auto V>
    struct ory_v_helper<bool_<V>> {
        static constexpr auto value = V;
    };

    template<auto V>
    struct ory_v_helper<list_v_<V>> {
        static constexpr auto value = V;
    };

    template <bool Short, template <auto...> class F>
    struct ory_v {
        template <auto V>
        using f                    = ory_v<ory_v_helper<F<V>>::value, F>;
        static constexpr std::size_t value = -1;
    };
    template <template <auto...> class F>
    struct ory_v<true, F> {
        template <auto V>
        using f                    = ory_v;
        static constexpr std::size_t value = 1;
    };
    template <std::size_t N, template <auto...> class F, typename C>
    struct dispatch<N, or_v_<lift_v_<F>, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_, not_<identity_>>,
                        typename foldey_v<(select_foldey_loop(
                                sizeof...(Vs)))>::template f<ory_v<false, F>, 0, Vs...>>>;
    };
    template <template <auto...> class F, typename C>
    struct dispatch<0, or_v_<lift_v_<F>, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, or_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_, not_<identity_>>,
                        typename foldey_v<(select_foldey_loop(sizeof...(Vs)))>::template f<
                                ory_v<false, dispatch<1, F>::template f>, 0, Vs...>>>;
    };
    template <typename F, typename C>
    struct dispatch<0, or_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<false_>;
    };
} // namespace impl

// any_of_ : Given a unary predicate, return true_ / false_ on whether any elements
// in a VPP satisfy that predicate.
BOOST_TMP_EXPORT template <typename F = identity_, typename C = identity_>
struct any_of_v_ {};
namespace impl { // any_of_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, any_of_v_<F, C>> : dispatch<N, or_v_<F, C>> {};
} // namespace impl

// and_v_ : Given a unary predicate, apply the unary predicate to each
// value in the input value parameter pack until logic and returns true.
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
struct and_v_ {};
namespace impl { // and_
    template <bool Short, template <auto...> class F>
    struct andy_v {
        template <auto V>
        using f                    = andy_v<(!F<V>::value), F>;
        static constexpr std::size_t value = -1;
    };
    template <template <auto...> class F>
    struct andy_v<true, F> {
        template <auto V>
        using f                    = andy_v;
        static constexpr std::size_t value = 1;
    };
    template <std::size_t N, template <auto...> class F, typename C>
    struct dispatch<N, and_v_<lift_v_<F>, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_>, typename foldey_v<(select_foldey_loop(sizeof...(
                                                Vs)))>::template f<andy_v<false, F>, 0, Vs...>>>;
    };
    template <template <auto...> class F, typename C>
    struct dispatch<0, and_v_<lift_v_<F>, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, and_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_>,
                        typename foldey_v<(select_foldey_loop(sizeof...(Vs)))>::template f<
                                andy_v<false, dispatch<1, F>::template f>, 0, Vs...>>>;
    };
    template <typename F, typename C>
    struct dispatch<0, and_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<1, C>::template f<false_>;
    };
} // namespace impl

// all_of_v_ : Given an unary predicate, return true_ / false_ on whether all elements
// in a value parameter pack satisfy that predicate. Shorting (uses and_v_).
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
struct all_of_v_ {};
namespace impl { // all_of_
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, all_of_v_<F, C>> : dispatch<N, and_v_<F, C>> {};
} // namespace impl

// size_v_ : Given an input VPP, get the number of elements in the VPP.
// Input: VPP
// Input Parameters: C - defaulted to listify_v_
// Output: Number of elements in VPP
// Default output format: list_v_<OutputValue>
BOOST_TMP_EXPORT template <typename C = listify_v_>
struct size_v_ {};
namespace impl { // size_
    template <std::size_t N, typename C>
    struct dispatch<N, size_v_<C>> {
        template <auto... Ls>
        using f = dispatch<1, C>::template f<sizeof...(Ls)>;
    };
} // namespace impl

// swap_v_ : Swaps two variadic values. Must be only two values.
BOOST_TMP_EXPORT template <typename C = listify_v_>
struct swap_v_ {};
namespace impl { // swap_
    template <typename C>
    struct dispatch<2, swap_v_<C>> {
        template <auto T, auto U>
        using f = dispatch<2, C>::template f<U, T>;
    };
    template<std::size_t N, typename C> requires(N == 2)
    struct dispatch<N, swap_v_<C>> {
        template<auto...>
        using f = nothing_;
    };
} // namespace impl

// take_v_ : Take N values from the input (index 0 to index N-1) value pack.
BOOST_TMP_EXPORT template <std::size_t N, typename C = listify_v_>
struct take_v_ {};
namespace impl { // take_v_
    template <std::size_t N, std::size_t P, typename C>
    struct dispatch<N, take_v_<P, C>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)),
                        rotate_v_<P, drop_v_<(sizeof...(Vs) - P), C>>>::template f<Vs...>;
    };
} // namespace impl

// take_last_v_ : Given an VPP, take the last (N) elements of the VPP.
BOOST_TMP_EXPORT template<std::size_t N, typename C = listify_v_>
struct take_last_v_ {};
namespace impl { // take_last_
    template<std::size_t N, std::size_t P, typename C>
    struct dispatch<N, take_last_v_<P, C>> {
        template<auto... Vs> requires(sizeof...(Vs) >= P)
        using f = dispatch<find_dispatch(sizeof...(Vs)), drop_v_<(sizeof...(Vs) - P), C>>::template f<Vs...>;
    };
    template<std::size_t N, typename C>
    struct dispatch<N, take_last_v_<0, C>> {
        template<auto... Vs>
        using f = dispatch<0, C>::template f<>;
    };
} // namespace impl

// transform_v_ : Apply a unary metaclosure to each value in the input VPP, returning
// a list of the modified values.
BOOST_TMP_EXPORT template <typename F, typename C = listify_>
struct transform_v_ {};
namespace impl { // transform_v_
    template <std::size_t N, template<auto...> typename F, typename FC, typename C>
    struct dispatch<N, transform_v_<lift_v_<F, FC>, C>> {
        template <auto... Vs>
        using f = dispatch<(N + (N > sizeof...(Vs))), C>::template f<F<Vs>...>;
    };

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, transform_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<
            typename dispatch<1, F>::template f<Vs>...>;
    };
} // namespace impl

// map_value_ : Given a value-to-type map (TMap), convert the input value into
// a type-value (int_, bool_, etc).
BOOST_TMP_EXPORT template<typename TMap, typename C = identity_>
struct map_value_ {};
namespace impl {
    template<auto V>
    struct value_type_hoist {
        template<typename AT>
        using f = call_v_<AT, V>;
    };
    
    template<typename TMap, typename C>
    struct dispatch<1, map_value_<TMap, C>> {
        template<auto V>
        using f = dispatch<1, find_<TMap, lift_<value_type_hoist<V>::template f, C>>>::template f<decltype(V)>;
    };
} // namespace impl

// typify_ : Shorthand Continuation for map_value; must be given a TMap type; optionally a Continuation.
BOOST_TMP_EXPORT template<typename TMap, typename C = identity_>
using typify_ = lift_v_<impl::dispatch<1, map_value_<TMap, C>>::template f>;

BOOST_TMP_EXPORT
template<typename C>
using typify_def_ = lift_v_<impl::dispatch<1, map_value_<default_type_lookup_table_, C>>::template f>;

// typify_default_ : Shorthand Continuation that uses default_type_lookup_table_ for map_value.
// Input: Single element VP
// Input parameters: None
// Output: Single type-value
// Output format type: mapped_type_<VP> (like int_<9>, bool_<false>, etc.)
BOOST_TMP_EXPORT
using typify_default_ = typify_def_<identity_>;

BOOST_TMP_EXPORT template<typename C = listify_v_>
struct as_values_ {};
namespace impl {
    template<std::size_t N, typename C>
    struct dispatch<N, as_values_<C>> {
        template<typename... VTs>
        using f = dispatch<find_dispatch(sizeof...(VTs)), C>::template f<VTs::value...>;
    };
} // namespace impl

// if_v_ : Given a unary predicate (UnaryPredicate), return type (T) if true and type (F) if false.
// Input: UnaryPredicate - Single value input unary predicate; must return either true_ or false_.
//        T - type returned upon evaluation of true UnaryPredicate; *must* use always_v_<*your type*>
//        F - type returned upon evaluation of false UnaryPredicate; *must* use always_v_<*your type*>
// VPP: Single element
// Output: Either (T) or (F)
BOOST_TMP_EXPORT template <typename P, typename T, typename F = always_v_<nothing_{}>>
struct if_v_ {};
namespace impl { // if_v_
    template <typename B>
    struct if_impl_v;
    template <>
    struct if_impl_v<list_v_<true>> {
        template <typename T, typename U>
        using f = T;
    };
    template <>
    struct if_impl_v<list_v_<false>> {
        template <typename T, typename U>
        using f = U;
    };
    template <typename P, typename T, typename F>
    struct dispatch<1, if_v_<P, T, F>> {
        template <auto V0>
        using f = dispatch<1, typename if_impl_v<typename dispatch<1, P>::template
                        f<V0>>::template
                            f<T, F>>::template
                                f<V0>;
    };
    template <template <auto...> class P, typename T, typename F>
    struct dispatch<1, if_v_<lift_v_<P>, T, F>> {
        template <auto V0>
        using f = dispatch<1, typename if_impl_v<P<V0>>::template
                        f<T, F>>::template
                            f<V0>;
    };
    template <std::size_t N, typename P, typename T, typename F>
    struct dispatch<N, if_v_<P, T, F>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)),
                        typename if_impl_v<typename dispatch<find_dispatch(sizeof...(Vs)), P>::template
                            f<Vs...>>::template f<T, F>>::template f<Vs...>;
    };
    template <std::size_t N, template <auto...> class P, typename T, typename F>
    struct dispatch<N, if_v_<lift_v_<P>, T, F>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)),
                        typename if_impl_v<P<Vs...>>::template
                            f<T, F>>::template f<Vs...>;
    };
    template <template <auto...> class P, typename T, typename F>
    struct dispatch<2, if_v_<lift_v_<P>, T, F>> {
        template <auto V0, auto V1>
        using f = dispatch<2, typename if_impl_v<P<V0, V1>>::template
                        f<T, F>>::template f<V0, V1>;
    };
    template <template <auto...> class P>
    struct dispatch<1, if_v_<lift_v_<P>, listify_v_, list_v_<>>> {
        template <auto U>
        using f = if_impl_v<P<U>>::template f<list_v_<U>, list_v_<>>;
    };
} // namespace impl

// is_v_ :
BOOST_TMP_EXPORT template <auto P, typename C = listify_v_, typename TMap = typify_default_>
struct is_v_ {};
namespace impl { // is_v_
    template <auto P, typename C, typename TMap>
    struct dispatch<1, is_v_<P, C, TMap>> {
        template <auto T>
        using f = dispatch<1, C>::template f<call_v_<transform_v_<TMap, lift_<std::is_same>>, P, T>::value>;
    };
} // namespace impl

// like_v_ : This metaclosure is like is_v_ except it compares purely by value.
// is_v_ is strict, and compares value *and* type. This compares *only* value for equality.
BOOST_TMP_EXPORT template <auto P, typename C = listify_v_>
struct like_v_ {};
namespace impl { // is_v_
    template <auto P, typename C>
    struct dispatch<1, like_v_<P, C>> {
        template <auto T>
        using f = dispatch<1, C>::template f<(P == T)>;
    };
} // namespace impl

// contains_v_ : Given a non-type parameter (V), return true_ / false_ on whether a given NTTP
// contains the value V.
BOOST_TMP_EXPORT template <auto V, typename C = identity_>
struct contains_v_ {};
namespace impl { // contains_
    template <std::size_t N, auto V, typename C>
    struct dispatch<N, contains_v_<V, C>> : dispatch<N, or_v_<is_v_<V>, C>> {};
} // namespace impl

} // namespace boost::tmp

#endif // __BOOST_NTTMP_HPP
