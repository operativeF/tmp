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

// always_v_ : metaclosure returns NTTP / shovels into the continuation C.
BOOST_TMP_EXPORT template <auto V, typename C = identity_>
struct always_v_ {};
namespace impl { // always_v_
    template <std::size_t N, auto V, typename C>
    struct dispatch<N, always_v_<V, C>> {
        template <auto...>
        using f = dispatch<1, C>::template f<V>;
    };
} // namespace impl

// contains_v_ : Given a non-type parameter (V), return true_ / false_ on whether a given NTTP
// contains the value V.
// BOOST_TMP_EXPORT template <auto V, typename C = identity_>
// struct contains_v_ {};
// namespace impl { // contains_
//     template <std::size_t N, auto V, typename C>
//     struct dispatch<N, contains_v_<V, C>> : dispatch<N, or_<is_v_<V>, C>> {};
// } // namespace impl

// drop_v_ : Remove (N) values from the front of the input VPP.
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

// reverse_v_ :
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

// rotate_v_
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
        template <typename...>
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

// join_v_ :
BOOST_TMP_EXPORT template<typename C = listify_v_>
struct join_v_ {};
namespace impl { // join_v_
    template<template<auto...> typename C, typename...>
    struct joiner_v;

    template <template <auto...> class C,
                auto... T0s, auto... T1s, auto... T2s, auto... T3s,
                auto... T4s, auto... T5s, auto... T6s, auto... T7s>
    struct joiner_v<C, list_v_<T0s...>, list_v_<T1s...>, list_v_<T2s...>, list_v_<T3s...>,
                        list_v_<T4s...>, list_v_<T5s...>, list_v_<T6s...>, list_v_<T7s...>> {
        template <auto... Vs>
        using f = C<T0s..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., Vs...>;
    };
    template<template <auto...> class C,
            auto... T0s,  auto... T1s,  auto... T2s,  auto... T3s,
            auto... T4s,  auto... T5s,  auto... T6s,  auto... T7s,
            auto... T8s,  auto... T9s,  auto... T10s, auto... T11s,
            auto... T12s, auto... T13s, auto... T14s, auto... T15s,
            auto... T16s, auto... T17s, auto... T18s, auto... T19s,
            auto... T20s, auto... T21s, auto... T22s, auto... T23s,
            auto... T24s, auto... T25s, auto... T26s, auto... T27s,
            auto... T28s, auto... T29s, auto... T30s, auto... T31s>
    struct joiner_v<C, list_v_<T0s...>,  list_v_<T1s...>,  list_v_<T2s...>,  list_v_<T3s...>,
                    list_v_<T4s...>,  list_v_<T5s...>,  list_v_<T6s...>,  list_v_<T7s...>,
                    list_v_<T8s...>,  list_v_<T9s...>,  list_v_<T10s...>, list_v_<T11s...>,
                    list_v_<T12s...>, list_v_<T13s...>, list_v_<T14s...>, list_v_<T15s...>,
                    list_v_<T16s...>, list_v_<T17s...>, list_v_<T18s...>, list_v_<T19s...>,
                    list_v_<T20s...>, list_v_<T21s...>, list_v_<T22s...>, list_v_<T23s...>,
                    list_v_<T24s...>, list_v_<T25s...>, list_v_<T26s...>, list_v_<T27s...>,
                    list_v_<T28s...>, list_v_<T29s...>, list_v_<T30s...>, list_v_<T31s...>> {
        template <auto... Vs>
        using f = C<T0s...,  T1s...,  T2s...,  T3s...,  T4s...,  T5s...,  T6s...,  T7s...,
                    T8s...,  T9s...,  T10s..., T11s..., T12s..., T13s..., T14s..., T15s...,
                    T16s..., T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s...,
                    T24s..., T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., Vs...>;
    };
    
    template <std::size_t N>
    struct join_loop_v;
    template <>
    struct join_loop_v<1> {
        template <template <auto...> class C,
                typename T0  = list_v_<>, typename T1  = list_v_<>, typename T2  = list_v_<>,
                typename T3  = list_v_<>, typename T4  = list_v_<>, typename T5  = list_v_<>,
                typename T6  = list_v_<>, typename T7  = list_v_<>, typename T8  = list_v_<>,
                typename T9  = list_v_<>, typename T10 = list_v_<>, typename T11 = list_v_<>,
                typename T12 = list_v_<>, typename T13 = list_v_<>, typename T14 = list_v_<>,
                typename T15 = list_v_<>, typename T16 = list_v_<>, typename T17 = list_v_<>,
                typename T18 = list_v_<>, typename T19 = list_v_<>, typename T20 = list_v_<>,
                typename T21 = list_v_<>, typename T22 = list_v_<>, typename T23 = list_v_<>,
                typename T24 = list_v_<>, typename T25 = list_v_<>, typename T26 = list_v_<>,
                typename T27 = list_v_<>, typename T28 = list_v_<>, typename T29 = list_v_<>,
                typename T30 = list_v_<>, typename T31 = list_v_<>, typename... Ts>
        using f = join_loop_v<(sizeof...(Ts) > 8)>::template f<
                joiner_v<C, T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12, T13,
                        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
                        T28, T29, T30, T31>::template f, Ts...>;
    };
    template <>
    struct join_loop_v<0> {
        template <template <auto...> class C,
                typename T0 = list_v_<>, typename T1 = list_v_<>, typename T2 = list_v_<>,
                typename T3 = list_v_<>, typename T4 = list_v_<>, typename T5 = list_v_<>,
                typename T6 = list_v_<>, typename T7 = list_v_<>, typename T8 = list_v_<>>
        using f = joiner_v<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
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


// drop_last_v_ :
BOOST_TMP_EXPORT template<std::size_t N, typename C = listify_v_>
struct drop_last_v_ {};
namespace impl { // drop_last_
    template<std::size_t N, std::size_t DropN, typename C>
    struct dispatch<N, drop_last_v_<DropN, C>> : dispatch<N, reverse_v_<drop_v_<DropN, reverse_v_<C>>>> {};
} // namespace impl

// pop_front_v_ :
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
    using f = dispatch<1, C>::template f<nothing_>;
};
} // namespace impl

// Like erase_ except the nth value is given by a value, N
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

// filter_v_:
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
// fold_left_v_ : 
BOOST_TMP_EXPORT template <auto F, typename C = listify_v_>
struct fold_left_v_ {};
namespace impl { // fold_left_v_
    template <auto F, template <auto...> class C>
    struct dispatch<0, fold_left_v_<F, lift_v_<C>>> {
        template <auto...>
        using f = nothing_;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<1, fold_left_v_<F, lift_v_<C>>> {
        template <auto V>
        using f = C<V>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<2, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0>
        using f = C<F(In, V0)>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<3, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0, auto V1>
        using f = C<F(F(In, V0), V1)>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<4, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0, auto V1, auto V2>
        using f = C<F(F(F(In, V0), V1), V2)>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<5, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0, auto V1, auto V2, auto V3>
        using f = C<F(F(F(F(In, V0), V1), V2), V3)>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<6, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0, auto V1, auto V2, auto V3,
                auto V4>
        using f = C<F(F(F(F(F(In, V0), V1), V2), V3), V4)>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<7, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0, auto V1, auto V2, auto V3,
                auto V4, auto V5>
        using f = C<F(F(F(F(F(F(In, V0), V1), V2), V3), V4), V5)>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<8, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0, auto V1, auto V2, auto V3,
                auto V4, auto V5, auto V6>
        using f = C<F(F(F(F(F(F(F(In, V0), V1), V2), V3), V4), V5), V6)>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<9, fold_left_v_<F, lift_v_<C>>> {
        template <auto In, auto V0, auto V1, auto V2, auto V3,
                auto V4, auto V5, auto V6, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1),
                                    fold_left_v_<F, lift_v_<C>>>::
                template f<F(F(F(F(F(F(F(In, V0), V1), V2), V3), V4), V5), V6), Vs...>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<16, fold_left_v_<F, lift_v_<C>>> {
        template <auto In,  auto V0,  auto V1,  auto V2,  auto V3,
                auto V4,  auto V5,  auto V6,  auto V7,  auto V8,
                auto V9,  auto V10, auto V11, auto V12, auto V13,
                auto V14, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1), fold_left_v_<F, lift_v_<C>>>::template
                    f<F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(In, V0),
                                                  V1),
                                                V2),
                                              V3),
                                            V4),
                                          V5),
                                        V6),
                                      V7),
                                    V8),
                                  V9),
                                V10),
                              V11),
                            V12),
                          V13),
                        V14),
                      Vs...>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<17, fold_left_v_<F, lift_v_<C>>>
        : dispatch<16, fold_left_v_<F, lift_v_<C>>> {};
    template <auto F, template <auto...> class C>
    struct dispatch<32, fold_left_v_<F, lift_v_<C>>> {
        template<auto In,  auto V0,  auto V1,  auto V2,  auto V3,
                auto V4,  auto V5,  auto V6,  auto V7,  auto V8,
                auto V9,  auto V10, auto V11, auto V12, auto V13,
                auto V14, auto V15, auto V16, auto V17, auto V18,
                auto V19, auto V20, auto V21, auto V22, auto V23,
                auto V24, auto V25, auto V26, auto V27, auto V28,
                auto V29, auto V30, auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs) + 1),
                    fold_left_v_<F, lift_v_<C>>>::template
                    f<F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(In, V0),
                                                                                  V1),
                                                                                V2),
                                                                              V3),
                                                                            V4),
                                                                          V5),
                                                                        V6),
                                                                      V7),
                                                                    V8),
                                                                  V9),
                                                                V10),
                                                              V11),
                                                            V12),
                                                          V13),
                                                        V14),
                                                      V15),
                                                    V16),
                                                  V17),
                                                V18),
                                              V19),
                                            V20),
                                          V21),
                                        V22),
                                      V23),
                                    V24),
                                  V25),
                                V26),
                              V27),
                            V28),
                          V29),
                        V30),
                      Vs...>;
    };
    template <auto F, template <auto...> class C>
    struct dispatch<33, fold_left_v_<F, lift_v_<C>>>
        : dispatch<32, fold_left_v_<F, lift_v_<C>>> {};
    template <auto F, template <auto...> class C>
    struct dispatch<64, fold_left_v_<F, lift_v_<C>>> {
        template<auto In,  auto V0,  auto V1,  auto V2,  auto V3,
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
                fold_left_v_<F, lift_v_<C>>>::
        template f<F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(F(In,
                                                                                                                                                   V0),
                                                                                                                                                 V1),
                                                                                                                                               V2),
                                                                                                                                             V3),
                                                                                                                                           V4),
                                                                                                                                         V5),
                                                                                                                                       V6),
                                                                                                                                     V7),
                                                                                                                                   V8),
                                                                                                                                 V9),
                                                                                                                               V10),
                                                                                                                             V11),
                                                                                                                           V12),
                                                                                                                         V13),
                                                                                                                       V14),
                                                                                                                     V15),
                                                                                                                   V16),
                                                                                                                 V17),
                                                                                                               V18),
                                                                                                             V19),
                                                                                                           V20),
                                                                                                         V21),
                                                                                                       V22),
                                                                                                     V23),
                                                                                                   V24),
                                                                                                 V25),
                                                                                               V26),
                                                                                             V27),
                                                                                           V28),
                                                                                         V29),
                                                                                       V30),
                                                                                     V31),
                                                                                   V32),
                                                                                 V33),
                                                                               V34),
                                                                             V35),
                                                                           V36),
                                                                         V37),
                                                                       V38),
                                                                     V39),
                                                                   V40),
                                                                 V41),
                                                               V42),
                                                             V43),
                                                           V44),
                                                         V45),
                                                       V46),
                                                     V47),
                                                   V48),
                                                 V49),
                                               V50),
                                             V51),
                                           V52),
                                         V53),
                                       V54),
                                     V55),
                                   V56),
                                 V57),
                               V58),
                             V59),
                           V60),
                         V61),
                       V62),
                     V63),
                   Vs...>;
    };
    template <std::size_t N, auto F, template <auto...> class C>
    struct dispatch<N, fold_left_v_<F, lift_v_<C>>>
        : dispatch<64, fold_left_v_<F, lift_v_<C>>> {};
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
    template <std::size_t N, std::size_t I, typename C>
    struct dispatch<N, index_v_<I, C>> : dispatch<N, drop_v_<I, front_v_<C>>> {};

    template <std::size_t N, typename C>
    struct dispatch<N, index_v_<std::numeric_limits<std::size_t>::max(), C>> { // 
        template <auto... Ts>
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

// is_v_ : 
BOOST_TMP_EXPORT template <auto P, typename C = listify_v_>
struct is_v_ {};
namespace impl { // is_v_
    template <auto P, typename C>
    struct dispatch<1, is_v_<P, C>> {
        template <auto T>
        using f = dispatch<1, C>::template f<(P == T)>;
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
BOOST_TMP_EXPORT template <typename F, typename C = identity_>
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

// push_front_v_ :
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

// find_if_ :
// Returns the index of the type that satisfies UnaryPredicate.
BOOST_TMP_EXPORT template <typename UnaryPred, typename C = identity_>
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

// insert_v_ :
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
        template <auto... Ts>
        using f = dispatch<1, C>::template f<V>;
    };
} // namespace impl

BOOST_TMP_EXPORT template <typename C = identity_>
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

// take_v_ :
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

// take_last_v_ :
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

// transform_v_ : 
// BOOST_TMP_EXPORT template <typename F = identity_, typename C = listify_v_>
// struct transform_v_ {};
// namespace impl { // transform_v_
//     template <std::size_t N, typename F, typename C>
//     struct dispatch<N, transform_v_<F, C>> {
//         template <auto... Vs>
//         using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<
//                         typename dispatch<1, F>::template f<Vs>...>;
//     };
//     template <std::size_t N, template <auto...> class F, typename FC, typename C>
//     struct dispatch<N, transform_v_<lift_v_<F, FC>, C>> {
//         template <auto... Vs>
//         using f = dispatch<(N + (N > sizeof...(Vs))), C>::template f<F<Vs>...>;
//     };
// } // namespace impl

// transform_v_ :
BOOST_TMP_EXPORT template <auto F, typename C = listify_v_>
struct transform_v_ {};
namespace impl { // transform_v_
    template <std::size_t N, auto F, typename C>
    struct dispatch<N, transform_v_<F, C>> {
        template <auto... Vs>
        using f = dispatch<find_dispatch(sizeof...(Vs)), C>::template f<F(Vs)...>;
    };
} // namespace impl

} // namespace boost::tmp

#endif // __BOOST_NTTMP_HPP
