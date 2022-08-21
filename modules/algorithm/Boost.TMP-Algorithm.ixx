//  Copyright 2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm;

#if _MSC_VER
import std;
#endif // _MSC_VER

import :Base.Types;

namespace boost::tmp {

// rotate_ :
// Input params: Parameter pack
// Closure params: N - Positive (for now) integer type
//                 C - Continuation; default listify_
// Functional description:
// input  - T0, T1, ..., TN
// apply  - (M rotations)
// result - T(M), T(M + 1), ..., T0, T1, ..., TN, ..., T(M - 1)
// Empty return type: list_<>
export template <typename N = sizet_<0>, typename C = listify_>
struct rotate_ {};
inline namespace rotate_implementation {
template <std::size_t, typename C>
struct rotate_impl;
template <typename C>
struct rotate_impl<0, C> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
};
template <typename C>
struct rotate_impl<1, C> {
    template <typename T, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template
                    f<Ts..., T>;
};
template <typename C>
struct rotate_impl<2, C> {
    template <typename T0, typename T1, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 2), C>::template
                    f<Ts..., T0, T1>;
};
template <typename C>
struct rotate_impl<3, C> {
    template <typename T0, typename T1, typename T2, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 3), C>::template
                    f<Ts..., T0, T1, T2>;
};
template <typename C>
struct rotate_impl<4, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 4), C>::template
                    f<Ts..., T0, T1, T2, T3>;
};
template <typename C>
struct rotate_impl<5, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 5), C>::template
                    f<Ts..., T0, T1, T2, T3, T4>;
};
template <typename C>
struct rotate_impl<6, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 6), C>::template
                    f<Ts..., T0, T1, T2, T3, T4, T5>;
};
template <typename C>
struct rotate_impl<7, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename T6, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 7), C>::template
                    f<Ts..., T0, T1, T2, T3, T4, T5, T6>;
};
template <typename C>
struct rotate_impl<8, C> {
    template<typename T0, typename T1, typename T2, typename T3, typename T4,
             typename T5, typename T6, typename T7, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 8), C>::template
                    f<Ts..., T0, T1, T2, T3, T4, T5, T6, T7>;
};
template <typename C>
struct rotate_impl<16, C> {
    template<typename T0, typename T1, typename T2, typename T3, typename T4,
             typename T5, typename T6, typename T7, typename T8, typename T9,
             typename T10, typename T11, typename T12, typename T13, typename T14,
             typename T15, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 16), C>::template
                    f<Ts..., T0, T1, T2,  T3,  T4,  T5,  T6,  T7,
                             T8, T9, T10, T11, T12, T13, T14, T15>;
};
template <typename C>
struct rotate_impl<32, C> {
    template<typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
             typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
             typename T10, typename T11, typename T12, typename T13, typename T14,
             typename T15, typename T16, typename T17, typename T18, typename T19,
             typename T20, typename T21, typename T22, typename T23, typename T24,
             typename T25, typename T26, typename T27, typename T28, typename T29,
             typename T30, typename T31, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 32), C>::template
                    f<Ts..., T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,
                             T8,  T9,  T10, T11, T12, T13, T14, T15,
                             T16, T17, T18, T19, T20, T21, T22, T23,
                             T24, T25, T26, T27, T28, T29, T30, T31>;
};
template <typename C>
struct rotate_impl<64, C> {
    template<typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
             typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
             typename T10, typename T11, typename T12, typename T13, typename T14,
             typename T15, typename T16, typename T17, typename T18, typename T19,
             typename T20, typename T21, typename T22, typename T23, typename T24,
             typename T25, typename T26, typename T27, typename T28, typename T29,
             typename T30, typename T31, typename T32, typename T33, typename T34,
             typename T35, typename T36, typename T37, typename T38, typename T39,
             typename T40, typename T41, typename T42, typename T43, typename T44,
             typename T45, typename T46, typename T47, typename T48, typename T49,
             typename T50, typename T51, typename T52, typename T53, typename T54,
             typename T55, typename T56, typename T57, typename T58, typename T59,
             typename T60, typename T61, typename T62, typename T63, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 64), C>::template
                    f<Ts..., T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10,
                             T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21,
                             T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32,
                             T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
                             T44, T45, T46, T47, T48, T49, T50, T51, T52, T53, T54,
                             T55, T56, T57, T58, T59, T60, T61, T62, T63>;
};
template <typename P, typename C>
struct dispatch<0, rotate_<P, C>> {
    template <typename...>
    using f = dispatch<0, C>::template f<>;
};
template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
struct make_rotate
    : rotate_impl<step_selector(Step), rotate_<sizet_<(P - Step)>, C>> { /* not done */
};
template <std::size_t P, typename C>
struct make_rotate<P, C, P> : rotate_impl<P, C> {};
template <std::size_t N, typename P, typename C>
struct dispatch<N, rotate_<P, C>> : make_rotate<P::value, C> {};
} // inline namespace rotate_implementation
inline namespace rotate_test {
template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
struct ZeroRotation;

template<typename T> requires(std::same_as<T, list_<int_<2>, int_<3>, int_<1>>>)
struct DoOneRotation;

template<typename T> requires(std::same_as<T, list_<>>)
struct RotateEmptyList;

using rotate_test_1   = ZeroRotation<call_<rotate_<int_<0>>, int_<1>, int_<2>, int_<3>>>;
using rotate_test_2   = DoOneRotation<call_<rotate_<int_<1>>, int_<1>, int_<2>, int_<3>>>;
using rotate_test_3   = RotateEmptyList<call_<rotate_<int_<0>>>>;
} // inline namespace rotate_test

// reverse_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, ..., TN
// apply  - (reverse element order of parameter pack)
// result -  TN, ..., T1, T0
// Empty return type: list_<>
export template <typename C = listify_>
struct reverse_ {};
namespace {
template <typename C, typename... Ts>
struct reverse_impl {
    template <typename... Us>
    using f = dispatch<
        find_dispatch(sizeof...(Ts) + sizeof...(Us)), C>::template f<Ts..., Us...>;
};
} // namespace
inline namespace reverse_implementation {
template <typename C>
struct dispatch<0, reverse_<C>> {
    template <typename...>
    using f = dispatch<0, C>::template f<>;
};
template <typename C>
struct dispatch<1, reverse_<C>> {
    template <typename T>
    using f = dispatch<1, C>::template f<T>;
};
template <typename C>
struct dispatch<2, reverse_<C>> {
    template <typename T0, typename T1>
    using f = dispatch<2, C>::template f<T1, T0>;
};
template <typename C>
struct dispatch<3, reverse_<C>> {
    template <typename T0, typename T1, typename T2>
    using f = dispatch<3, C>::template f<T2, T1, T0>;
};
template <typename C>
struct dispatch<4, reverse_<C>> {
    template <typename T0, typename T1, typename T2, typename T3>
    using f = dispatch<4, C>::template f<T3, T2, T1, T0>;
};
template <typename C>
struct dispatch<5, reverse_<C>> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    using f = dispatch<5, C>::template f<T4, T3, T2, T1, T0>;
};
template <typename C>
struct dispatch<6, reverse_<C>> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5>
    using f = dispatch<6, C>::template f<T5, T4, T3, T2, T1, T0>;
};
template <typename C>
struct dispatch<7, reverse_<C>> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename T6>
    using f = dispatch<7, C>::template f<T6, T5, T4, T3, T2, T1, T0>;
};
template <typename C>
struct dispatch<8, reverse_<C>> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename T6, typename T7>
    using f = dispatch<8, C>::template f<T7, T6, T5, T4, T3, T2, T1, T0>;
};
template <typename C>
struct dispatch<9, reverse_<C>> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename T6, typename T7, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                        reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
                            template f<T7, T6, T5, T4, T3, T2, T1, T0>;
};
template <typename C>
struct dispatch<16, reverse_<C>> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15>
    using f = dispatch<16, C>::template f<T15, T14, T13, T12, T11, T10, T9, T8,
                                            T7,  T6,  T5,  T4,  T3,  T2,  T1, T0>;
};
template <typename C>
struct dispatch<17, reverse_<C>> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                                reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::
            template f<T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1, T0>;
};
template <typename C>
struct dispatch<32, reverse_<C>> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15, typename T16, typename T17, typename T18, typename T19,
              typename T20, typename T21, typename T22, typename T23, typename T24,
              typename T25, typename T26, typename T27, typename T28, typename T29,
              typename T30, typename T31>
    using f = dispatch<32, C>::template f<T31, T30, T29, T28, T27, T26, T25, T24,
                                          T23, T22, T21, T20, T19, T18, T17, T16,
                                          T15, T14, T13, T12, T11, T10, T9,  T8,
                                          T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
};
template <typename C>
struct dispatch<33, reverse_<C>> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15, typename T16, typename T17, typename T18, typename T19,
              typename T20, typename T21, typename T22, typename T23, typename T24,
              typename T25, typename T26, typename T27, typename T28, typename T29,
              typename T30, typename T31, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), reverse_<lift_<reverse_impl>>>::template
                f<Ts..., C>::template f<T31, T30, T29, T28, T27, T26, T25, T24,
                                        T23, T22, T21, T20, T19, T18, T17, T16,
                                        T15, T14, T13, T12, T11, T10, T9,  T8,
                                        T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
};
template <typename C>
struct dispatch<64, reverse_<C>> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15, typename T16, typename T17, typename T18, typename T19,
              typename T20, typename T21, typename T22, typename T23, typename T24,
              typename T25, typename T26, typename T27, typename T28, typename T29,
              typename T30, typename T31, typename T32, typename T33, typename T34,
              typename T35, typename T36, typename T37, typename T38, typename T39,
              typename T40, typename T41, typename T42, typename T43, typename T44,
              typename T45, typename T46, typename T47, typename T48, typename T49,
              typename T50, typename T51, typename T52, typename T53, typename T54,
              typename T55, typename T56, typename T57, typename T58, typename T59,
              typename T60, typename T61, typename T62, typename T63>
    using f = dispatch<16, C>::template f<T63, T62, T61, T60, T59, T58, T57, T56,
                                          T55, T54, T53, T52, T51, T50, T49, T48,
                                          T47, T46, T45, T44, T43, T42, T41, T40,
                                          T39, T38, T37, T36, T35, T34, T33, T32,
                                          T31, T30, T29, T28, T27, T26, T25, T24,
                                          T23, T22, T21, T20, T19, T18, T17, T16,
                                          T15, T14, T13, T12, T11, T10, T9,  T8,
                                          T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
};
template <typename C>
struct dispatch<65, reverse_<C>> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15, typename T16, typename T17, typename T18, typename T19,
              typename T20, typename T21, typename T22, typename T23, typename T24,
              typename T25, typename T26, typename T27, typename T28, typename T29,
              typename T30, typename T31, typename T32, typename T33, typename T34,
              typename T35, typename T36, typename T37, typename T38, typename T39,
              typename T40, typename T41, typename T42, typename T43, typename T44,
              typename T45, typename T46, typename T47, typename T48, typename T49,
              typename T50, typename T51, typename T52, typename T53, typename T54,
              typename T55, typename T56, typename T57, typename T58, typename T59,
              typename T60, typename T61, typename T62, typename T63, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1),
                    reverse_<lift_<reverse_impl>>>::template f<Ts..., C>::template
                    f<T63, T62, T61, T60, T59, T58, T57, T56, T55, T54, T53, T52, T51, T50,
                      T49, T48, T47, T46, T45, T44, T43, T42, T41, T40, T39, T38, T37, T36,
                      T35, T34, T33, T32, T31, T30, T29, T28, T27, T26, T25, T24, T23, T22,
                      T21, T20, T19, T18, T17, T16, T15, T14, T13, T12, T11, T10, T9,  T8,
                      T7,  T6,  T5,  T4,  T3,  T2,  T1,  T0>;
};
template <std::size_t N, typename C>
struct dispatch<N, reverse_<C>> : dispatch<65, reverse_<C>> {};
} // inline namespace reverse_implementation
inline namespace reverse_test {
template<typename T> requires(std::same_as<T, list_<int_<2>, int_<1>, int_<0>>>)
struct ListTwoOneZero;

template<typename T> requires(std::same_as<T, list_<>>)
struct EmptyListReturnsEmptyList;

template<typename T> requires(std::same_as<T, list_<int_<1>>>)
struct SingleElementReturnsListOfSingleElement;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
struct DoubleReverseIsOriginal;

using reverse_test_1 = ListTwoOneZero<call_<reverse_<>, int_<0>, int_<1>, int_<2>>>;

// Reversing empty input results in empty list
using reverse_test_2 = EmptyListReturnsEmptyList<call_<reverse_<>>>;

// Reversing single input results in single input list
using reverse_test_3 = SingleElementReturnsListOfSingleElement<call_<reverse_<>, int_<1>>>;

using reverse_test_4 = DoubleReverseIsOriginal<call_<reverse_<reverse_<>>, int_<1>, int_<2>, int_<3>>>;
} // inline namespace reverse_test

// unpack_ :
export template <typename C = listify_>
struct unpack_ {};
namespace {
template <typename C, typename L>
struct unpack_impl;
} // namespace
inline namespace unpack_implementation {
template <typename C, template <typename...> class Seq, typename... Ls>
struct unpack_impl<C, Seq<Ls...>> {
    using type = dispatch<find_dispatch(sizeof...(Ls)), C>::template f<Ls...>;
};
// in case of nothing_ input give a nothing_ output
template <typename C>
struct unpack_impl<C, nothing_> {
    using type = nothing_;
};
template <typename C>
struct dispatch<1, unpack_<C>> {
    template <typename L>
    using f = unpack_impl<C, L>::type;
};

} // inline namespace unpack_implementation
inline namespace unpack_test {

} // inline namespace unpack_test

inline namespace transform {
// transform_ : 
export template <typename F = identity_, typename C = listify_>
struct transform_ {};
inline namespace transform_implementation {
template <std::size_t N, typename F, typename C>
struct dispatch<N, transform_<F, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<
                    typename dispatch<1, F>::template f<Ts>...>;
};
template <std::size_t N, template <typename...> class F, typename FC, typename C>
struct dispatch<N, transform_<lift_<F, FC>, C>> {
    template <typename... Ts>
    using f = dispatch<(N + (N > sizeof...(Ts))), C>::template f<F<Ts>...>;
};
} // inline namespace transform_impl
inline namespace transform_test {

} // inline namespace transform_test
} // inline namespace transform

// make_sequence_ :
export template <typename F = identity_, typename C = listify_>
struct make_sequence_ {};
namespace {
consteval std::size_t next_number(std::size_t current, std::size_t end) {
    return ((end - 2 * current) < 2) ?
                    end :
                    next_number(current,
                                end / 2); // note that std::size_t / 2 always rounds down
}
consteval std::size_t next_state(std::size_t current, std::size_t end) {
    return ((end - current) < 2) ? end - current :
                                    (2 + (next_number(current, end) - 2 * current));
}
template <std::size_t State>
struct make_seq_impl;
template <>
struct make_seq_impl<0> { // done
    template <std::size_t End, std::size_t... Is>
    using f = list_<sizet_<Is>...>;
};
template <>
struct make_seq_impl<1> { // done +1
    template <std::size_t End, std::size_t... Is>
    using f = list_<sizet_<Is>..., sizet_<End - 1>>;
};
template <>
struct make_seq_impl<2> { // double
    template <std::size_t End, std::size_t... Is>
    using f = make_seq_impl<next_state(2 * sizeof...(Is), End)>::template 
                f<End, Is..., (Is + sizeof...(Is))...>;
};
template <>
struct make_seq_impl<3> { // double +1
    template <std::size_t End, std::size_t... Is>
    using f = make_seq_impl<next_state(2 * sizeof...(Is) + 1, End)>::template f<
                    End, Is..., (Is + sizeof...(Is))..., (2 * sizeof...(Is))>;
};
} // namespace
inline namespace make_sequence_implementation {
template <typename F, typename C>
struct dispatch<1, make_sequence_<F, C>> {
    template <typename N>
    using f = dispatch<1, unpack_<transform_<F, C>>>::template f<
            typename make_seq_impl<next_state(0, N::value)>::template f<N::value>>;
};

// TODO: Benchmark alternate implemenation.
// template<typename... Vs>
// struct index_impl;
// template<std::size_t... Vs>
// struct index_impl<std::index_sequence<Vs...>> {
//     using f = list_<sizet_<Vs>...>;
// };
// template <typename F, typename C>
// struct dispatch<1, make_sequence_<F, C>> {
//     template <typename N>
//     using f = dispatch<1, unpack_<transform_<F, C>>>::template f<typename index_impl<std::make_index_sequence<N::value>>::template f>;
// };
} // inline namespace make_sequence_impl
inline namespace make_sequence_test {
template<typename T>
using and_one = sizet_<T::value + 1>;
template<typename T>
struct always_one {
    template<typename N>
    using f = sizet_<T::value>;
};
template<typename T> requires(std::same_as<T, list_<sizet_<0>, sizet_<1>, sizet_<2>>>)
struct ListZeroOneTwo;

template<typename T> requires(std::same_as<T, list_<sizet_<1>, sizet_<2>, sizet_<3>>>)
struct ListOneTwoThree;

// using make_sequence_test_1 = ListZeroOneTwo<call_<make_sequence_<>, sizet_<3>>>;
// using make_sequence_test_2 = ListOneTwoThree<call_<make_sequence_<lift_<and_one>>, sizet_<3>>>;
} // inline namespace make_sequence_test

// repeat_sequence_ :
export template<typename N = sizet_<0>, typename C = listify_>
struct repeat_sequence_{};
inline namespace repeat_sequence_implementation {
template <std::size_t, typename C>
struct repeat_seq_impl;
template <typename C>
struct repeat_seq_impl<0, C> {
    template <typename...>
    using f = dispatch<0, C>::template f<>;
};
template <typename C>
struct repeat_seq_impl<1, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 1, C>::template f<T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<2, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 2, C>::template f<T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<3, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 3, C>::template f<T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<4, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 4, C>::template f<T, T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<5, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 5, C>::template f<T, T, T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<6, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 6, C>::template f<T, T, T, T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<7, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 7, C>::template f<T, T, T, T, T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<8, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 8, C>::template f<T, T, T, T, T, T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<16, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 16, C>::template f<T, T, T, T, T, T, T, T,
                                                          T, T, T, T, T, T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<32, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 32, C>::template f<T, T, T, T, T, T, T, T,
                                                          T, T, T, T, T, T, T, T,
                                                          T, T, T, T, T, T, T, T,
                                                          T, T, T, T, T, T, T, T, Ts...>;
};
template <typename C>
struct repeat_seq_impl<64, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts) + 64, C>::template f<
            T, T, T, T, T, T, T, T,
            T, T, T, T, T, T, T, T,
            T, T, T, T, T, T, T, T,
            T, T, T, T, T, T, T, T,
            T, T, T, T, T, T, T, T,
            T, T, T, T, T, T, T, T,
            T, T, T, T, T, T, T, T,
            T, T, T, T, T, T, T, T, Ts...>;
};
template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
struct make_repeat : repeat_seq_impl<Step, repeat_sequence_<sizet_<(P - Step) + 1>, C>> {};
template <std::size_t P, typename C>
struct make_repeat<P, C, P> : repeat_seq_impl<P, C> {};
template <std::size_t N, typename P, typename C>
struct dispatch<N, repeat_sequence_<P, C>> : make_repeat<P::value, C> {};
} // inline namespace repeat_sequence_impl
inline namespace repeat_sequence_test {
// TODO: Implement repeat_sequence_test
// std::index_sequence<1, 1, 1, 1, 1, 1, 1, 1, 1, 1>{} = call_<repeat_sequence_<sizet_<10>, lift_<into_sequence>>, sizet_<1>>{};
// list_<sizet_<1>, sizet_<1>, sizet_<1>, sizet_<2>, sizet_<2>, sizet_<2>, sizet_<3>, sizet_<3>, sizet_<3>>{} = call_<transform_<repeat_sequence_<sizet_<3>>, join_<>>, sizet_<1>, sizet_<2>, sizet_<3>>{};
} // inline namespace repeate_sequence_test

// drop_ : Remove (N) values from the front of the input VPP.
// Input params: Parameter pack
// Closure params: N - Positive integer type
//                 C - Continuation; default listify_
// Functional description:
// input  - T0, T1, ..., T(M), T(M + 1), ..., TN
// apply  - (drop M values)
// result - T(M), T(M + 1), ..., TN
// Empty return type: list_<>
export template <typename N = sizet_<0>, typename C = listify_>
struct drop_ {};
inline namespace drop_implementation {
template <std::size_t, typename C>
struct drop_impl;
// TODO: Is this correct behavior for dropping nothing?
template <typename C>
struct drop_impl<0, C> {
    template <typename... Ts>
    using f = call_<C, Ts...>;
};
template <typename C>
struct drop_impl<1, C> {
    template <typename T, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<2, C> {
    template <typename T0, typename T1, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<3, C> {
    template <typename T0, typename T1, typename T2, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<4, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<5, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<6, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<7, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename T6, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<8, C> {
    template <typename T0, typename T1, typename T2, typename T3, typename T4,
              typename T5, typename T6, typename T7, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<16, C> {
    template<typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
             typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
             typename T10, typename T11, typename T12, typename T13, typename T14,
             typename T15, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<32, C> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15, typename T16, typename T17, typename T18, typename T19,
              typename T20, typename T21, typename T22, typename T23, typename T24,
              typename T25, typename T26, typename T27, typename T28, typename T29,
              typename T30, typename T31, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <typename C>
struct drop_impl<64, C> {
    template <typename T0,  typename T1,  typename T2,  typename T3,  typename T4,
              typename T5,  typename T6,  typename T7,  typename T8,  typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14,
              typename T15, typename T16, typename T17, typename T18, typename T19,
              typename T20, typename T21, typename T22, typename T23, typename T24,
              typename T25, typename T26, typename T27, typename T28, typename T29,
              typename T30, typename T31, typename T32, typename T33, typename T34,
              typename T35, typename T36, typename T37, typename T38, typename T39,
              typename T40, typename T41, typename T42, typename T43, typename T44,
              typename T45, typename T46, typename T47, typename T48, typename T49,
              typename T50, typename T51, typename T52, typename T53, typename T54,
              typename T55, typename T56, typename T57, typename T58, typename T59,
              typename T60, typename T61, typename T62, typename T63, typename... Ts>
    using f = dispatch<sizeof...(Ts), C>::template f<Ts...>;
};
template <std::size_t P, typename C, std::size_t Step = step_selector(P)>
struct make_drop : drop_impl<Step, drop_<sizet_<(P - Step)>, C>> { /* not done */
};
template <std::size_t P, typename C>
struct make_drop<P, C, P> : drop_impl<P, C> {};
template <std::size_t N, typename P, typename C>
struct dispatch<N, drop_<P, C>> : make_drop<P::value, C> {};
} // inline namespace drop_impl
inline namespace drop_test {
template<typename T> requires(std::same_as<T, list_<int_<1>>>)
struct DropOneOffOfList;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>>>)
struct DropZeroReturnsInputList;

using drop_test_1 = DropOneOffOfList<call_<drop_<uint_<1>>, int_<0>, int_<1>>>;

using drop_test_2 = DropZeroReturnsInputList<call_<drop_<uint_<0>>, int_<1>, int_<2>>>;
} // inline namespace drop_test

// take_ :
export template <typename N = sizet_<0>, typename C = listify_>
struct take_ {};
inline namespace take_implementation {
template <std::size_t N, typename P, typename C>
struct dispatch<N, take_<P, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)),
                    rotate_<P, drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>>::template f<Ts...>;
};
} // inline namespace take_impl
inline namespace take_test {
template<typename T> requires(std::same_as<T, list_<int_<1>>>)
struct TakeFirstElement_One;

template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>>>)
struct TakeFirstTwoElements_OneTwo;

using take_test_1 = TakeFirstElement_One<call_<take_<uint_<1>>, int_<1>, int_<2>, int_<3>>>;
using take_test_2 = TakeFirstTwoElements_OneTwo<call_<take_<uint_<2>>, int_<1>, int_<2>, int_<3>>>;

// UNDER CONSIDERATION: Taking more than the list results in compilation failure.
// UNDER CONSIDERATION: Taking from an empty input results in compilation failure.
// list_<>{} = call_<take_<uint_<4>>>{};

} // inline namespace take_test

// counted_ :
export template<typename StartIndex, typename Count, typename C = listify_>
struct counted_ {};
inline namespace counted_implementation {
template<std::size_t N, typename StartIndex, typename Count, typename C>
struct dispatch<N, counted_<StartIndex, Count, C>> {
    template<typename... Ts>
    using f = dispatch<sizeof...(Ts), drop_<StartIndex, take_<Count, C>>>::template f<Ts...>;
};
} // inline namespace counted_impl
inline namespace counted_test {
template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, int_<3>>>)
struct GetTheMiddle123;

using counted_test_1 = GetTheMiddle123<call_<counted_<int_<1>, int_<3>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<5>, int_<7>>>;
} // inline namespace counted_test

// is_ : 
export template <typename P, typename C = identity_>
struct is_ {};
inline namespace is_implementation {
template <typename P, typename C>
struct dispatch<1, is_<P, C>> {
    template <typename T>
    using f = dispatch<1, C>::template f<bool_<std::is_same_v<P, T>>>;
};
} // inline namespace is_implementation

// not_ : 
export template <typename C = identity_>
struct not_ {};
inline namespace not_implementation {
template <typename C>
struct dispatch<1, not_<C>> {
    template <typename T>
    using f = dispatch<1, C>::template f<bool_<(!T::value)>>;
};
} // inline namespace not_implementation

// foldey : implementation only
inline namespace foldey_implementation {
consteval std::size_t select_foldey_loop(std::size_t rest_size) {
    return static_cast<std::size_t>(rest_size < 8 ? (rest_size == 0 ? 1000 : 1001) : 1008);
}
// FIXME: Workaround employed after value isn't found when invoking F::template f<T0>::value
// in foldey<1001>. The value of the type is found after referring to it here, not in foldey<1001>.
template<typename WorkAroundT>
consteval std::size_t select_foldey(std::size_t chunk_size, std::size_t rest_size) {
    return WorkAroundT::value == std::numeric_limits<std::size_t>::max() ? select_foldey_loop(rest_size) :
                                    chunk_size - WorkAroundT::value;
}

template <std::size_t S>
struct foldey {
    template <typename F, std::size_t N, typename...>
    using f = sizet_<N - S>;
};
template <>
struct foldey<1000> {
    template <typename F, std::size_t N, typename... Ts>
    using f = nothing_;
};
// FIXME: Workaround for extracting value in F::template f<T0>. Pass type into now templated select_foldey.
template <>
struct foldey<1001> {
    template <typename F, std::size_t N, typename T0, typename... Ts> 
    using f = foldey<select_foldey<typename F::template f<T0>>(1, sizeof...(Ts))>::template f<F, N + 1, Ts...>;
};
template <>
struct foldey<1008> {
    template <typename F, std::size_t N, typename T0, typename T1, typename T2,
                typename T3, typename T4, typename T5, typename T6, typename T7,
                typename... Ts>
    using f = foldey<select_foldey(8, sizeof...(Ts),
                F::template
                  f<T0>::template
                    f<T1>::template
                      f<T2>::template
                        f<T3>::template
                          f<T4>::template
                            f<T5>::template
                              f<T6>::template
                                f<T7>::value)>::template
                                  f<F, N + 8, Ts...>;
};
template <>
struct foldey<1000000> {};
} // inline namespace foldey

// or_ : 
export template <typename F = identity_, typename C = identity_>
struct or_ {};
namespace {
template <bool Short, template <typename...> class F>
struct ory {
    template <typename T>
    using f                    = ory<F<T>::value, F>;
    static constexpr std::size_t value = -1;
};
} // namespace
inline namespace or_implementation {
template <template <typename...> class F>
struct ory<true, F> {
    template <typename T>
    using f                    = ory;
    static constexpr std::size_t value = 1;
};
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, or_<lift_<F>, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<
            call_<is_<nothing_, not_<identity_>>,
                    typename foldey<(select_foldey_loop(
                            sizeof...(Ts)))>::template f<ory<false, F>, 0, Ts...>>>;
};
template <template <typename...> class F, typename C>
struct dispatch<0, or_<lift_<F>, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<false_>;
};
template <std::size_t N, typename F, typename C>
struct dispatch<N, or_<F, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<
            call_<is_<nothing_, not_<identity_>>,
                    typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
                            ory<false, dispatch<1, F>::template f>, 0, Ts...>>>;
};
template <typename F, typename C>
struct dispatch<0, or_<F, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<false_>;
};
} // inline namespace or_implementation

// and_ : 
export template <typename F = identity_, typename C = identity_>
struct and_ {};
namespace {
template <bool Short, template <typename...> class F>
struct andy {
    template <typename T>
    using f                    = andy<(!F<T>::value), F>;
    static constexpr std::size_t value = -1;
};
} // namespace
inline namespace and_implementation {
template <template <typename...> class F>
struct andy<true, F> {
    template <typename T>
    using f                    = andy;
    static constexpr std::size_t value = 1;
};
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, and_<lift_<F>, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<
            call_<is_<nothing_>, typename foldey<(select_foldey_loop(sizeof...(
                                            Ts)))>::template f<andy<false, F>, 0, Ts...>>>;
};
template <template <typename...> class F, typename C>
struct dispatch<0, and_<lift_<F>, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<false_>;
};
template <std::size_t N, typename F, typename C>
struct dispatch<N, and_<F, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<
            call_<is_<nothing_>,
                    typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
                            andy<false, dispatch<1, F>::template f>, 0, Ts...>>>;
};
template <typename F, typename C>
struct dispatch<0, and_<F, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<false_>;
};
} // inline namespace and_implementation

// if_ : Given a predicate P, if true, return T, and if false, return F.
export template <typename P, typename T, typename F = always_<nothing_>>
struct if_ {};
namespace {
template <bool B>
struct if_impl;
template <>
struct if_impl<true> {
    template <typename T, typename U>
    using f = T;
};
template <>
struct if_impl<false> {
    template <typename T, typename U>
    using f = U;
};
} // namespace
inline namespace if_implementation {
template <typename P, typename T, typename F>
struct dispatch<1, if_<P, T, F>> {
    template <typename T0>
    using f = dispatch<1, typename if_impl<dispatch<1, P>::template
                    f<T0>::value>::template
                        f<T, F>>::template
                            f<T0>;
};
template <template <typename...> class P, typename T, typename F>
struct dispatch<1, if_<lift_<P>, T, F>> {
    template <typename T0>
    using f = dispatch<1, typename if_impl<P<T0>::value>::template
                    f<T, F>>::template
                        f<T0>;
};
template <std::size_t N, typename P, typename T, typename F>
struct dispatch<N, if_<P, T, F>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)),
                    typename if_impl<dispatch<find_dispatch(sizeof...(Ts)), P>::template
                        f<Ts...>::value>::template f<T, F>>::template f<Ts...>;
};
template <std::size_t N, template <typename...> class P, typename T, typename F>
struct dispatch<N, if_<lift_<P>, T, F>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)),
                    typename if_impl<P<Ts...>::value>::template
                        f<T, F>>::template f<Ts...>;
};
template <template <typename...> class P, typename T, typename F>
struct dispatch<2, if_<lift_<P>, T, F>> {
    template <typename T0, typename T1>
    using f = dispatch<2, typename if_impl<P<T0,T1>::value>::template
                    f<T, F>>::template f<T0, T1>;
};
template <template <typename...> class P>
struct dispatch<1, if_<lift_<P>, listify_, always_<list_<>>>> {
    template <typename U>
    using f = if_impl<P<U>::value>::template f<list_<U>, list_<>>;
};
} // inline namespace if_implementation

// less_ : 
export template <typename V = nothing_, typename C = identity_>
struct less_ {};
inline namespace less_implementation {
template <typename C>
struct dispatch<2, less_<C>> {
    template <typename T, typename U>
    using f = dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
};
template <typename U, typename C>
struct dispatch<1, less_<U, C>> {
    template<typename T>
    using f = dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
};
} // inline namespace less_implementation

// less_f_ : 
export template <typename F, typename C = identity_>
struct less_f_ {};
inline namespace less_f_implementation {
template <template<typename...> typename F, typename C>
struct dispatch<2, less_f_<lift_<F>, C>> {
    template<typename T, typename U>
    using f = dispatch<1, C>::template f<bool_<(F<T>::value < F<U>::value)>>;
};
} // inline namespace less_f_implementation

// less_eq_ : 
export template <typename V = nothing_, typename C = identity_>
struct less_eq_ {};
inline namespace less_eq_implementation {
template <typename C>
struct dispatch<2, less_eq_<C>> {
    template <typename T, typename U>
    using f = dispatch<1, C>::template f<bool_<(T::value)<=(U::value)>>;
};
template <typename U, typename C>
struct dispatch<1, less_eq_<U, C>> {
    template<typename T>
    using f = dispatch<1, C>::template f<bool_<(U::value)<=(T::value)>>;
};
} // inline namespace less_eq_implementation

// greater_ : 
export template <typename V = nothing_, typename C = identity_>
struct greater_ {};
inline namespace greater_implementation {
template <typename C>
struct dispatch<2, greater_<C>> {
    template <typename T, typename U>
    using f = dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
};
template <typename U, typename C>
struct dispatch<1, greater_<U, C>> {
    template<typename T>
    using f = dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
};
} // inline namespace greater_implementation

// range_lo_hi_ : 
export template <typename LV = nothing_, typename UV = nothing_, typename C = identity_>
struct range_lo_hi_ {};
inline namespace range_lo_hi_implementation {
template <typename Lower, typename Upper, typename C>
struct dispatch<1, range_lo_hi_<Lower, Upper, C>> {
    template<typename T>
    using f = dispatch<1, C>::template f<bool_<!((Lower::value < T::value) && (T::value < Upper::value))>>;
};
} // inline namespace range_lo_hi_implementation

// all_of_ : Given a unary predicate, return true_ / false_ on whether all elements
// in a VPP satisfy that predicate.
export template <typename F, typename C = identity_>
struct all_of_ {};
inline namespace all_of_implementation {
template <std::size_t N, typename F, typename C>
struct dispatch<N, all_of_<F, C>> : dispatch<N, and_<F, C>> {};
} // inline namespace all_of_implementation

// any_of_ : Given a unary predicate, return true_ / false_ on whether any elements
// in a VPP satisfy that predicate.
export template <typename F = identity_, typename C = identity_>
struct any_of_ {};
inline namespace any_of_implementation {
template <std::size_t N, typename F, typename C>
struct dispatch<N, any_of_<F, C>> : dispatch<N, or_<F, C>> {};
} // inline namespace any_of_implementation

// none_of_ : Given a predicate (F), return true_ / false_ if none
// of the elements in a VPP satisfy the predicate F.
export template <typename F, typename C = identity_>
struct none_of_ {};
inline namespace none_of_implementation {
template <std::size_t N, typename F, typename C>
struct dispatch<N, none_of_<F, C>> : dispatch<N, and_<F, not_<C>>> {};
} // inline namespace none_of_implementation

// contains_ : Given a type (V), return true_ / false_ on whether a given VPP
// contains the type V.
export template <typename T, typename C = identity_>
struct contains_ {};
inline namespace contains_implementation {
template <std::size_t N, typename T, typename C>
struct dispatch<N, contains_<T, C>> : dispatch<N, or_<is_<T>, C>> {};
} // inline namespace contains_implementation

// push_back_ :
export template <typename T, typename C = listify_>
struct push_back_ {};
inline namespace push_back_implementation {
template <std::size_t N, typename T, typename C>
struct dispatch<N, push_back_<T, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
};
} // push_back_implementation

// pop_front_ :
export template <typename C = listify_>
struct pop_front_ {};
inline namespace pop_front_implementation {
template <std::size_t N, typename C>
struct dispatch<N, pop_front_<C>> {
    template <typename T, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
};
// TODO: Should this be kept? This differs from the behavior of popping
// the front off of an empty list (which results in an empty list).
// This, however, will return a list_<nothing_>
template <typename C>
struct dispatch<0, pop_front_<C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<nothing_>;
};
} // inline namespace pop_front_implementation

// push_front_ :
export template <typename T, typename C = listify_>
struct push_front_ {};
inline namespace push_front_implementation {
template <std::size_t N, typename T, typename C>
struct dispatch<N, push_front_<T, C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<T, Ts...>;
};
} // inline namespace pop_back_implementation

// pop_back_ :
export template <typename C = listify_>
struct pop_back_ {};
inline namespace pop_back_implementation {
template<std::size_t N, typename C>
struct dispatch<N, pop_back_<C>> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), rotate_<sizet_<sizeof...(Ts) - 1>, pop_front_<
                    rotate_<sizet_<(sizeof...(Ts) - 1)>, C>>>>::template f<Ts...>;
};
template <typename C>
struct dispatch<0, pop_back_<C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<nothing_>;
};
} // inline namespace pop_back_implementation

// tee_ :
export template <typename... Fs>
struct tee_ {};
inline namespace tee_implementation {
template <typename N, typename L, typename C, typename... Fs>
struct tee_impl {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                typename dispatch<find_dispatch(sizeof...(Ts)), Fs>::template f<Ts...>...,
                typename dispatch<find_dispatch(sizeof...(Ts)), L>::template f<Ts...>>;
};
// specialization for case where last closure is a forward
template <typename N, typename C, typename... Fs>
struct tee_impl<N, identity_, C, Fs...> {
    template <typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Fs) + sizeof...(Ts)), C>::template
                f<dispatch<find_dispatch(sizeof...(Ts)), Fs>::template f<Ts...>...,
                        Ts...>;
};
template <typename L, typename C, typename... Fs>
struct tee_impl<sizet_<1>, L, C, Fs...> {
    template <typename T0>
    using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                typename dispatch<1, Fs>::template f<T0>...,
                typename dispatch<1, L>::template f<T0>>;
};
// specialization for case where last closure is a forward
template <typename C, typename... Fs>
struct tee_impl<sizet_<1>, identity_, C, Fs...> {
    template <typename T0>
    using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template f<
                typename dispatch<1, Fs>::template f<T0>..., T0>;
};
template <typename L, typename C, typename... Fs>
struct tee_impl<sizet_<2>, L, C, Fs...> {
    template <typename T0, typename T1>
    using f = dispatch<find_dispatch(sizeof...(Fs) + 1), C>::template
                    f<typename dispatch<2, Fs>::template f<T0, T1>...,
                    typename dispatch<2, L>::template f<T0, T1>>;
};
// specialization for case where last closure is a forward
template <typename C, typename... Fs>
struct tee_impl<sizet_<2>, identity_, C, Fs...> {
    template <typename T0, typename T1>
    using f = dispatch<find_dispatch(sizeof...(Fs) + 2), C>::template f<
                typename dispatch<2, Fs>::template f<T0, T1>..., T0, T1>;
};

// in case the continuation is an and_
template <bool b, typename C, typename... Fs>
struct tee_and_impl;
template <typename C, typename... Fs>
struct tee_and_impl<false, C, Fs...> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<false_>;
};
template <typename C, typename... Fs>
struct tee_and_impl<true, C, Fs...> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<true_>;
};
template <typename C, typename F, typename... Fs>
struct tee_and_impl<true, C, F, Fs...> {
    template <typename... Ts>
    using f = tee_and_impl<dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
            Fs...>::template f<Ts...>;
};
template <bool b, typename C, typename... Fs>
struct tee_and_impl_1;
template <typename C, typename... Fs>
struct tee_and_impl_1<false, C, Fs...> {
    template <typename T0>
    using f = dispatch<1, C>::template f<false_>;
};
template <typename C, typename... Fs>
struct tee_and_impl_1<true, C, Fs...> {
    template <typename T0>
    using f1 = dispatch<1, C>::template f<true_>;
};
template <typename C, typename F, typename... Fs>
struct tee_and_impl_1<true, C, F, Fs...> {
    template <typename T0>
    using f = tee_and_impl<dispatch<1, F>::template f<T0>::value, C,
                                    Fs...>::template f<T0>;
};
template <bool b, typename C, typename... Fs>
struct tee_and_impl_2;
template <typename C, typename... Fs>
struct tee_and_impl_2<false, C, Fs...> {
    template <typename T0, typename T1>
    using f = dispatch<1, C>::template f<false_>;
};
template <typename C, typename... Fs>
struct tee_and_impl_2<true, C, Fs...> {
    template <typename T0, typename T1>
    using f = dispatch<1, C>::template f<true_>;
};
template <typename C, typename F, typename... Fs>
struct tee_and_impl_2<true, C, F, Fs...> {
    template <typename T0, typename T1>
    using f = tee_and_impl<dispatch<2, F>::template f<T0, T1>::value, C,
                                    Fs...>::template f<T0, T1>;
};
template <typename N, typename L, typename C, typename... Fs>
struct tee_impl<N, L, and_<identity_, C>, Fs...> : tee_and_impl<true, C, Fs..., L> {};
template <typename L, typename C, typename... Fs>
struct tee_impl<sizet_<1>, L, and_<identity_, C>, Fs...>
        : tee_and_impl_1<true, C, Fs..., L> {};
template <typename C, typename... Fs>
struct tee_impl<sizet_<1>, identity_, and_<identity_, C>, Fs...>
        : tee_and_impl_1<true, C, Fs..., identity_> {};
template <typename L, typename C, typename... Fs>
struct tee_impl<sizet_<2>, L, and_<identity_, C>, Fs...>
        : tee_and_impl_2<true, C, Fs..., L> {};
template <typename C, typename... Fs>
struct tee_impl<sizet_<2>, identity_, and_<identity_, C>, Fs...>
        : tee_and_impl_2<true, C, Fs..., identity_> {};

// in case the continuation is an or_
template <bool b, typename C, typename... Fs>
struct tee_or_impl;
template <typename C, typename... Fs>
struct tee_or_impl<true, C, Fs...> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<true_>;
};
template <typename C, typename... Fs>
struct tee_or_impl<false, C, Fs...> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<false_>;
};
template <typename C, typename F, typename... Fs>
struct tee_or_impl<false, C, F, Fs...> {
    template <typename... Ts>
    using f = tee_or_impl<
            dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>::value, C,
            Fs...>::template f<Ts...>;
};
template <bool b, typename C, typename... Fs>
struct tee_or_impl_1;
template <typename C, typename... Fs>
struct tee_or_impl_1<true, C, Fs...> {
    template <typename T0>
    using f = dispatch<1, C>::template f<true_>;
};
template <typename C, typename... Fs>
struct tee_or_impl_1<false, C, Fs...> {
    template <typename T0>
    using f1 = dispatch<1, C>::template f<false_>;
};
template <typename C, typename F, typename... Fs>
struct tee_or_impl_1<false, C, F, Fs...> {
    template <typename T0>
    using f = tee_or_impl<dispatch<1, F>::template f<T0>::value, C,
                                    Fs...>::template f<T0>;
};
template <bool b, typename C, typename... Fs>
struct tee_or_impl_2;
template <typename C, typename... Fs>
struct tee_or_impl_2<true, C, Fs...> {
    template <typename T0, typename T1>
    using f = dispatch<1, C>::template f<true_>;
};
template <typename C, typename... Fs>
struct tee_or_impl_2<false, C, Fs...> {
    template <typename T0, typename T1>
    using f = dispatch<1, C>::template f<false_>;
};
template <typename C, typename F, typename... Fs>
struct tee_or_impl_2<false, C, F, Fs...> {
    template <typename T0, typename T1>
    using f = tee_or_impl<dispatch<2, F>::template f<T0, T1>::value, C,
                                    Fs...>::template f<T0, T1>;
};
template <typename N, typename L, typename C, typename... Fs>
struct tee_impl<N, L, or_<identity_, C>, Fs...> : tee_or_impl<false, C, Fs..., L> {};
template <typename L, typename C, typename... Fs>
struct tee_impl<sizet_<1>, L, or_<identity_, C>, Fs...>
        : tee_or_impl_1<false, C, Fs..., L> {};
template <typename C, typename... Fs>
struct tee_impl<sizet_<1>, identity_, or_<identity_, C>, Fs...>
        : tee_or_impl_1<false, C, Fs..., identity_> {};
template <typename L, typename C, typename... Fs>
struct tee_impl<sizet_<2>, L, or_<identity_, C>, Fs...>
        : tee_or_impl_2<false, C, Fs..., L> {};

template <std::size_t N, typename F0, typename F1, typename... Fs>
struct dispatch<N, tee_<F0, F1, Fs...>>
    : dispatch<find_dispatch(sizeof...(Fs) + 2),
                rotate_<sizet_<sizeof...(Fs)>, push_front_<sizet_<N>, lift_<tee_impl>>>>::
                template f<F0, F1, Fs...> {};
} // inline namespace tee_implementation
inline namespace tee_test {
// TODO: Narrow tests down.
// list_<list_<>>{}          = call_<tee_<listify_, listify_>>{};
// list_<list_<int>>{}       = call_<tee_<listify_, listify_>, int>{};
// list_<list_<int, bool>>{} = call_<tee_<listify_, listify_>, int, bool>{};

// true_{}  = call_<tee_<is_<int>, and_<>>, int>{};
// false_{} = call_<tee_<is_<int>, is_<int>, and_<>>, char>{};
// false_{} = call_<tee_<is_<int>, is_<int>, is_<int>, and_<>>, char>{};
// false_{} = call_<tee_<is_<int>, identity_, and_<>>,
//                     char>{}; // short circuiting should save from hard error
// false_{} = call_<tee_<is_<int>, identity_, is_<int>, and_<>>,
//                     char>{}; // short circuiting should save from hard error

// true_{}  = call_<tee_<is_<int>, or_<>>, int>{};
// false_{} = call_<tee_<is_<int>, is_<int>, or_<>>, char>{};
// false_{} = call_<tee_<is_<int>, is_<int>, is_<int>, or_<>>, char>{};
// true_{}  = call_<tee_<is_<int>, identity_, or_<>>,
//                 int>{}; // short circuiting should save from hard error
// true_{}  = call_<tee_<is_<int>, identity_, is_<int>, or_<>>,
//                 int>{}; // short circuiting should save from hard error
} // inline namespace tee_test

// chunk_ : Get every nth element in a parameter pack, starting
// at zero.
// Input params: Parameter pack
// Closure params: S - Positive integer type denoting the step of the stride.
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, T2, T3, T4, T5, ..., TN
// apply  -  (get every nth element)
// result -  T0, T(n), T(2n), T(3n), ..., T(m * n)
// Empty return type: list_<>
export template<typename S = sizet_<0>, typename C = listify_>
struct chunk_ {};
namespace {
consteval std::size_t chunk_div(std::size_t input_size, std::size_t chunk_length) {
    if((input_size % chunk_length < 1) && (input_size > chunk_length))
        return input_size / chunk_length;
    else if(input_size < chunk_length)
        return 1;
    else // remainder chunk
        return input_size / chunk_length + 1;
}
consteval std::size_t chunking_size(std::size_t current_index, std::size_t chunk_size, std::size_t val_count) {
    if(auto remainder = val_count % chunk_size; (remainder > 0) && ((current_index * chunk_size + remainder) == val_count))
        return remainder; // Return the last, unevenly chunked, elements.
    else
        return chunk_size;
}
// TODO: Move this to MakeSequence module.
template <std::size_t N>
using make_index_for_stride = make_seq_impl<next_state(0, N)>::template f<N>;
template<typename S, typename C, typename... Ts>
struct chunk_impl;
} // namespace
inline namespace chunk_implementation {
template<std::size_t N, typename S, typename C, typename... Ts>
struct dispatch<N, chunk_impl<S, list_<Ts...>, C>> {
    template<typename... Us>
    using f = dispatch<sizeof...(Us),
        tee_<counted_<sizet_<(Ts::value * S::value)>,
                      sizet_<chunking_size(Ts::value, S::value, sizeof...(Us))>>..., C>>::template f<Us...>;
};
template<std::size_t N, typename S, typename C>
struct dispatch<N, chunk_<S, C>> {
    template<typename... Ts>
    using f = dispatch<sizeof...(Ts),
        chunk_impl<S, make_index_for_stride<chunk_div(sizeof...(Ts), S::value)>, C>>::template f<Ts...>;
};
} // inline namespace chunk_impl
inline namespace chunk_test {
template<typename T> requires(std::same_as<T, list_<list_<int_<0>, int_<1>, int_<2>>,
                                                    list_<int_<3>, int_<4>, int_<5>>,
                                                    list_<int_<6>, int_<7>>>>)
struct ChunkEveryThreeElements;

using chunk_test_1 = ChunkEveryThreeElements<call_<chunk_<sizet_<3>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>, int_<6>, int_<7>>>;
} // inline namespace chunk_test

// size_ :
// Input params: Parameter pack
// Closure params: C - Continuation; default identity_
// Functional description:
// input  - T0, T1, ..., TN (Ts...)
// apply  - (get number of elements in parameter pack)
// result - sizet_<sizeof...(Ts)>
// Empty return type: sizet_<0>
export template <typename C = identity_>
struct size_ {};
inline namespace size_implementation {
template <std::size_t N, typename C>
struct dispatch<N, size_<C>> {
    template <typename... Ls>
    using f = dispatch<1, C>::template f<sizet_<sizeof...(Ls)>>;
};
} // inline namespace size_implementation

export template <typename C = listify_>
struct join_ {};
namespace {
template <std::size_t N>
struct join_loop;
template <template <typename...> class C, typename...>
struct joiner;
template <>
struct join_loop<1> {
    template <template <typename...> class C,
              typename T0  = list_<>, typename T1  = list_<>, typename T2  = list_<>,
              typename T3  = list_<>, typename T4  = list_<>, typename T5  = list_<>,
              typename T6  = list_<>, typename T7  = list_<>, typename T8  = list_<>,
              typename T9  = list_<>, typename T10 = list_<>, typename T11 = list_<>,
              typename T12 = list_<>, typename T13 = list_<>, typename T14 = list_<>,
              typename T15 = list_<>, typename T16 = list_<>, typename T17 = list_<>,
              typename T18 = list_<>, typename T19 = list_<>, typename T20 = list_<>,
              typename T21 = list_<>, typename T22 = list_<>, typename T23 = list_<>,
              typename T24 = list_<>, typename T25 = list_<>, typename T26 = list_<>,
              typename T27 = list_<>, typename T28 = list_<>, typename T29 = list_<>,
              typename T30 = list_<>, typename T31 = list_<>, typename... Ts>
    using f = join_loop<(sizeof...(Ts) > 8)>::template f<
            joiner<C, T0,  T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12, T13,
                      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
                      T28, T29, T30, T31>::template f, Ts...>;
};
template <>
struct join_loop<0> {
    template <template <typename...> class C,
              typename T0 = list_<>, typename T1 = list_<>, typename T2 = list_<>,
              typename T3 = list_<>, typename T4 = list_<>, typename T5 = list_<>,
              typename T6 = list_<>, typename T7 = list_<>, typename T8 = list_<>>
    using f = joiner<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
};
template <template <typename...> class C,
            typename... T0s, typename... T1s, typename... T2s, typename... T3s,
            typename... T4s, typename... T5s, typename... T6s, typename... T7s>
struct joiner<C, list_<T0s...>, list_<T1s...>, list_<T2s...>, list_<T3s...>,
                    list_<T4s...>, list_<T5s...>, list_<T6s...>, list_<T7s...>> {
    template <typename... Vs>
    using f = C<T0s..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., Vs...>;
};
template<template <typename...> class C,
         typename... T0s,  typename... T1s,  typename... T2s,  typename... T3s,
         typename... T4s,  typename... T5s,  typename... T6s,  typename... T7s,
         typename... T8s,  typename... T9s,  typename... T10s, typename... T11s,
         typename... T12s, typename... T13s, typename... T14s, typename... T15s,
         typename... T16s, typename... T17s, typename... T18s, typename... T19s,
         typename... T20s, typename... T21s, typename... T22s, typename... T23s,
         typename... T24s, typename... T25s, typename... T26s, typename... T27s,
         typename... T28s, typename... T29s, typename... T30s, typename... T31s>
struct joiner<C, list_<T0s...>,  list_<T1s...>,  list_<T2s...>,  list_<T3s...>,
                 list_<T4s...>,  list_<T5s...>,  list_<T6s...>,  list_<T7s...>,
                 list_<T8s...>,  list_<T9s...>,  list_<T10s...>, list_<T11s...>,
                 list_<T12s...>, list_<T13s...>, list_<T14s...>, list_<T15s...>,
                 list_<T16s...>, list_<T17s...>, list_<T18s...>, list_<T19s...>,
                 list_<T20s...>, list_<T21s...>, list_<T22s...>, list_<T23s...>,
                 list_<T24s...>, list_<T25s...>, list_<T26s...>, list_<T27s...>,
                 list_<T28s...>, list_<T29s...>, list_<T30s...>, list_<T31s...>> {
    template <typename... Vs>
    using f = C<T0s...,  T1s...,  T2s...,  T3s...,  T4s...,  T5s...,  T6s...,  T7s...,
                T8s...,  T9s...,  T10s..., T11s..., T12s..., T13s..., T14s..., T15s...,
                T16s..., T17s..., T18s..., T19s..., T20s..., T21s..., T22s..., T23s...,
                T24s..., T25s..., T26s..., T27s..., T28s..., T29s..., T30s..., T31s..., Vs...>;
};
} // namespace
inline namespace join_implementation {
template <std::size_t N, template <typename...> class C>
struct dispatch<N, join_<lift_<C>>> {
    template <typename... Ts>
    using f = join_loop<(sizeof...(Ts) > 8)>::template f<C, Ts...>;
};
template <std::size_t N, typename C>
struct dispatch<N, join_<C>> {
    template <typename... Ts>
    using f = join_loop<(
            sizeof...(Ts) > 8)>::template f<dispatch_unknown<C>::template f, Ts...>;
};
} // inline namespace join_implementation

export template<typename C = listify_>
struct join_seq_ {};
template<std::size_t... Is>
using IndexSeq = std::index_sequence<Is...>;
export template<typename... Ts>
using into_sequence = IndexSeq<Ts::value...>;
namespace {
template <template <typename...> class C, typename...>
struct seq_joiner {};
template <std::size_t N>
struct seq_join_loop {};
template <>
struct seq_join_loop<1> {
    template <template <typename...> class C,
              typename T0  = IndexSeq<>, typename T1  = IndexSeq<>, typename T2  = IndexSeq<>,
              typename T3  = IndexSeq<>, typename T4  = IndexSeq<>, typename T5  = IndexSeq<>,
              typename T6  = IndexSeq<>, typename T7  = IndexSeq<>, typename T8  = IndexSeq<>,
              typename T9  = IndexSeq<>, typename T10 = IndexSeq<>, typename T11 = IndexSeq<>,
              typename T12 = IndexSeq<>, typename T13 = IndexSeq<>, typename T14 = IndexSeq<>,
              typename T15 = IndexSeq<>, typename T16 = IndexSeq<>, typename T17 = IndexSeq<>,
              typename T18 = IndexSeq<>, typename T19 = IndexSeq<>, typename T20 = IndexSeq<>,
              typename T21 = IndexSeq<>, typename T22 = IndexSeq<>, typename T23 = IndexSeq<>,
              typename T24 = IndexSeq<>, typename T25 = IndexSeq<>, typename T26 = IndexSeq<>,
              typename T27 = IndexSeq<>, typename T28 = IndexSeq<>, typename T29 = IndexSeq<>,
              typename T30 = IndexSeq<>, typename T31 = IndexSeq<>, typename... Ts>
    using f = seq_join_loop<(sizeof...(Ts) > 8)>::template f<
            seq_joiner<C, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
                          T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
                          T28, T29, T30, T31>::template f, Ts...>;
};
template <>
struct seq_join_loop<0> {
    template <template <typename...> class C,
              typename T0 = IndexSeq<>, typename T1 = IndexSeq<>, typename T2 = IndexSeq<>,
              typename T3 = IndexSeq<>, typename T4 = IndexSeq<>, typename T5 = IndexSeq<>,
              typename T6 = IndexSeq<>, typename T7 = IndexSeq<>, typename T8 = IndexSeq<>>
    using f = seq_joiner<C, T0, T1, T2, T3, T4, T5, T6, T7>::template f<>;
};
} // namespace
inline namespace join_seq_implementation {
template <template <typename...> class C, std::size_t... T0s, std::size_t... T1s,
            std::size_t... T2s, std::size_t... T3s, std::size_t... T4s, std::size_t... T5s,
            std::size_t... T6s, std::size_t... T7s>
struct seq_joiner<C, IndexSeq<T0s...>, IndexSeq<T1s...>, IndexSeq<T2s...>, IndexSeq<T3s...>,
                IndexSeq<T4s...>, IndexSeq<T5s...>, IndexSeq<T6s...>, IndexSeq<T7s...>> {
    template <typename... Vs>
    using f = C<sizet_<T0s>..., sizet_<T1s>..., sizet_<T2s>..., sizet_<T3s>..., sizet_<T4s>..., sizet_<T5s>..., sizet_<T6s>..., sizet_<T7s>..., Vs...>;
};
template <template <typename...> class C,
          std::size_t... T0s,  std::size_t... T1s,  std::size_t... T2s,  std::size_t... T3s,
          std::size_t... T4s,  std::size_t... T5s,  std::size_t... T6s,  std::size_t... T7s,
          std::size_t... T8s,  std::size_t... T9s,  std::size_t... T10s, std::size_t... T11s,
          std::size_t... T12s, std::size_t... T13s, std::size_t... T14s, std::size_t... T15s,
          std::size_t... T16s, std::size_t... T17s, std::size_t... T18s, std::size_t... T19s,
          std::size_t... T20s, std::size_t... T21s, std::size_t... T22s, std::size_t... T23s,
          std::size_t... T24s, std::size_t... T25s, std::size_t... T26s, std::size_t... T27s,
          std::size_t... T28s, std::size_t... T29s, std::size_t... T30s, std::size_t... T31s>
struct seq_joiner<C, IndexSeq<T0s...>,  IndexSeq<T1s...>,  IndexSeq<T2s...>,  IndexSeq<T3s...>,
                     IndexSeq<T4s...>,  IndexSeq<T5s...>,  IndexSeq<T6s...>,  IndexSeq<T7s...>,
                     IndexSeq<T8s...>,  IndexSeq<T9s...>,  IndexSeq<T10s...>, IndexSeq<T11s...>,
                     IndexSeq<T12s...>, IndexSeq<T13s...>, IndexSeq<T14s...>, IndexSeq<T15s...>,
                     IndexSeq<T16s...>, IndexSeq<T17s...>, IndexSeq<T18s...>, IndexSeq<T19s...>,
                     IndexSeq<T20s...>, IndexSeq<T21s...>, IndexSeq<T22s...>, IndexSeq<T23s...>,
                     IndexSeq<T24s...>, IndexSeq<T25s...>, IndexSeq<T26s...>, IndexSeq<T27s...>,
                     IndexSeq<T28s...>, IndexSeq<T29s...>, IndexSeq<T30s...>, IndexSeq<T31s...>> {
    template <typename... Vs>
    using f = C<sizet_<T0s>...,  sizet_<T1s>...,  sizet_<T2s>...,  sizet_<T3s>...,
                sizet_<T4s>...,  sizet_<T5s>...,  sizet_<T6s>...,  sizet_<T7s>...,
                sizet_<T8s>...,  sizet_<T9s>...,  sizet_<T10s>..., sizet_<T11s>...,
                sizet_<T12s>..., sizet_<T13s>..., sizet_<T14s>..., sizet_<T15s>...,
                sizet_<T16s>..., sizet_<T17s>..., sizet_<T18s>..., sizet_<T19s>...,
                sizet_<T20s>..., sizet_<T21s>..., sizet_<T22s>..., sizet_<T23s>...,
                sizet_<T24s>..., sizet_<T25s>..., sizet_<T26s>..., sizet_<T27s>...,
                sizet_<T28s>..., sizet_<T29s>..., sizet_<T30s>..., sizet_<T31s>..., Vs...>;
};
template <std::size_t N, template <typename...> class C>
struct dispatch<N, join_seq_<lift_<C>>> {
    template <typename... Ts>
    using f = seq_join_loop<(sizeof...(Ts) > 8)>::template f<C, Ts...>;
};
template <std::size_t N, typename C>
struct dispatch<N, join_seq_<C>> {
    template <typename... Ts>
    using f = seq_join_loop<(sizeof...(Ts) > 8)>::template
                f<dispatch_unknown<C>::template f, Ts...>;
};
} // inline namespace join_seq_implementation

// count_if_ : Given a predicate F, check the variadic parameter pack passed in and count
// each time that the predicate holds true. Returns n counts as sizet_<n>.
export template <typename F, typename C = identity_>
struct count_if_ {};
inline namespace count_if_implementation {
template <std::size_t N, typename F, typename C>
struct dispatch<N, count_if_<F, C>>
    : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
                                join_<size_<C>>>> {};
} // inline namespace count_if_implementation

// find_if_ : 
export template <typename F, typename C = identity_>
struct find_if_ {};
namespace {
template <bool Found, std::size_t At, template <typename...> class F>
struct county {
    static constexpr auto value{std::numeric_limits<std::size_t>::max()};
    template <typename T>
    using f = county<F<T>::value, (At + 1), F>;
};
template <std::size_t At, template <typename...> class F>
struct county<true, At, F> {
    template <typename T>
    using f                    = county;
    static constexpr std::size_t value = At;
};
} // namespace
inline namespace find_if_implementation {
template <std::size_t N, typename F, typename C>
struct dispatch<N, find_if_<F, C>> {
    template <typename... Ts>
    using f = typename dispatch<1, C>::template f<
                    typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
                    county<false,
                            std::numeric_limits<std::size_t>::max(),
                            dispatch<1, F>::template f>, 0, Ts...>>;
};
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, find_if_<lift_<F>, C>> {
        template <typename... Ts>
        using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
                     sizeof...(Ts))>::template f<county<false,
                                                        std::numeric_limits<std::size_t>::max(),
                                                        F>, 0, Ts...>>;
};
} // inline namespace find_if_implementation

// find_if_not_ : 
export template <typename F, typename C = identity_>
struct find_if_not_ {};
namespace {
template <bool Found, std::size_t At, template <typename...> class F>
struct county_not {
    static constexpr auto value{std::numeric_limits<std::size_t>::max()};
    template <typename T>
    using f = county_not<F<T>::value, (At + 1), F>;
};
template <std::size_t At, template <typename...> class F>
struct county_not<false, At, F> {
    template <typename T>
    using f                    = county_not;
    static constexpr std::size_t value = At;
};
} // namespace
inline namespace find_if_not_implementation {
template <std::size_t N, typename F, typename C>
struct dispatch<N, find_if_not_<F, C>> {
    template <typename... Ts>
    using f = typename dispatch<1, C>::template f<
                    typename foldey<select_foldey_loop(sizeof...(Ts))>::template f<
                    county_not<true,
                            std::numeric_limits<std::size_t>::max(),
                            dispatch<1, F>::template f>, 0, Ts...>>;
};
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, find_if_not_<lift_<F>, C>> {
        template <typename... Ts>
        using f = typename dispatch<1, C>::template f<typename foldey<select_foldey_loop(
                     sizeof...(Ts))>::template f<county_not<true,
                                                        std::numeric_limits<std::size_t>::max(),
                                                        F>, 0, Ts...>>;
};
} // inline namespace find_if_not_implementation

// filter_ :
export template <typename F, typename C = listify_>
struct filter_ {};
namespace {
template <std::size_t N, template <typename...> class F, typename C>
struct filtery;
} // namespace
inline namespace filter_implementation {
template <template <typename...> class F, typename C>
struct filtery<0, F, C> {
    template <std::size_t N, typename T, typename U, typename... Ts>
    using f = filtery<(F<U>::value + 2 * (N == 1)), F,
                                C>::template f<(N - 1), U, Ts...>;
};
template <template <typename...> class F, typename C>
struct filtery<1, F, C> {
    template <std::size_t N, typename T, typename U, typename... Ts>
    using f = filtery<(F<U>::value + 2 * (N == 1)), F, C>::template
                    f<(N - 1), U, Ts..., T>;
};
template <template <typename...> class F, typename C>
struct filtery<2, F, C> { // all the way around, remove last
    template <std::size_t N, typename T, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), C>::template f<Ts...>;
};
template <template <typename...> class F, typename C>
struct filtery<3, F, C> { // all the way around, keep last
    template <std::size_t N, typename T, typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts) + 1), C>::template f<Ts..., T>;
};
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, filter_<lift_<F>, C>> {
    template <typename T, typename... Ts>
    using f = filtery<(F<T>::value + 2 * (sizeof...(Ts) == 0)), F,
                                C>::template f<(sizeof...(Ts)), T, Ts...>;
};
template <std::size_t N, typename F, typename C>
struct dispatch<N, filter_<F, C>> {
    template <typename T, typename... Ts>
    using f = filtery<
            (dispatch<1, F>::template f<T>::value + 2 * (sizeof...(Ts) == 0)),
            dispatch<1, F>::template f, C>::template f<(sizeof...(Ts)), T, Ts...>;
};
template <typename F, typename C>
struct dispatch<0, filter_<F, C>> {
    template <typename... Ts>
    using f = dispatch<0, C>::template f<>;
};
template <template <typename...> class F, typename C>
struct dispatch<0, filter_<lift_<F>, C>> {
    template <typename... Ts>
    using f = dispatch<0, C>::template f<>;
};
} // inline namespace filter_implementation

// remove_if_ : Given a predicate F, check the variadic parameter pack passed in
// and remove the value if the predicate holds true.
export template <typename F, typename C = listify_>
struct remove_if_ {};
inline namespace remove_if_implementation {
template<std::size_t N, typename F, typename C>
struct dispatch<N, remove_if_<F, C>>
        : dispatch<N, filter_<if_<F, always_<false_>, always_<true_>>, C>> {};
} // inline namespace_remove_if_implementation

// replace_if_ : Given a variadic parameter pack, replace every value that fulfills
// the predicate F with the value Input.
export template <typename Input, typename F, typename C = listify_>
struct replace_if_ {};
inline namespace replace_if_implementation {
template <std::size_t N, typename Input, typename F, typename C>
struct dispatch<N, replace_if_<Input, F, C>>
        : dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};
} // inline namespace replace_if_implementation

// clamp_ : Given a lower-bound type (L) and higher-bound type (H), and that both types
// are less than and greater than comparable, remove all types less than L and all types
// greater than H from a given VPP.
// The VPP values must also satisfy being less than and greater than comparable.
export template <typename L, typename H, typename C = identity_>
struct clamp_ {};
inline namespace clamp_implementation {
template <std::size_t N, typename L, typename H, typename C>
struct dispatch<N, clamp_<L, H, C>>
    : dispatch<N, remove_if_<range_lo_hi_<L, H, C>>> {};
} // inline namespace clamp_impl
inline namespace clamp_test {
template<typename T> requires(std::same_as<T, list_<uint_<4>>>)
struct ListWithOnlyFour;

using test_one = ListWithOnlyFour<call_<clamp_<uint_<3>, uint_<10>>, uint_<0>, uint_<1>, uint_<2>, uint_<3>, uint_<4>>>;
} // inline namespace clamp_test

// drop_last_ :
export template<typename N = sizet_<0>, typename C = listify_>
struct drop_last_ {};
inline namespace drop_last_implementation {
template<std::size_t N, typename DropN, typename C>
struct dispatch<N, drop_last_<DropN, C>> : dispatch<N, reverse_<drop_<DropN, reverse_<C>>>> {};
} // inline namespace drop_last_impl
inline namespace drop_last_test {
template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>>>)
struct DropThreeOffEnd;

using drop_last_test_1 = DropThreeOffEnd<call_<drop_last_<int_<3>>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>;
} // inline namespace drop_last_test

// take_last_ :
export template<typename N = sizet_<0>, typename C = listify_>
struct take_last_ {};
inline namespace take_last_implementation {
template<std::size_t N, typename P, typename C>
struct dispatch<N, take_last_<P, C>> {
    template<typename... Ts>
    using f = dispatch<find_dispatch(sizeof...(Ts)), drop_<sizet_<(sizeof...(Ts) - P::value)>, C>>::template f<Ts...>;
};
} // inline namespace take_last_impl
inline namespace take_last_test {
template<typename T> requires(std::same_as<T, list_<int_<4>, int_<5>>>)
struct LastTwoElements;

using take_last_test_1 = LastTwoElements<call_<take_last_<int_<2>>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>>>;
}

// each_ :
export template <typename... Fs>
struct each_ {};
inline namespace each_implementation {
template <typename F, typename C>
struct dispatch<1, each_<F, C>> {
    template <typename T>
    using f = dispatch<1, C>::template f<dispatch<1, F>::template f<T>>;
};
template <typename F0, typename F1, typename C>
struct dispatch<2, each_<F0, F1, C>> {
    template <typename T0, typename T1>
    using f = dispatch<2, C>::template f<dispatch<1, F0>::template f<T0>,
                                            dispatch<1, F1>::template f<T1>>;
};
template <typename F0, typename F1, typename F2, typename C>
struct dispatch<3, each_<F0, F1, F2, C>> {
    template <typename T0, typename T1, typename T2>
    using f = dispatch<3, C>::template f<dispatch<1, F0>::template f<T0>,
                                            dispatch<1, F1>::template f<T1>,
                                            dispatch<1, F2>::template f<T2>>;
};
template <typename F0, typename F1, typename F2, typename F3, typename C>
struct dispatch<4, each_<F0, F1, F2, F3, C>> {
    template <typename T0, typename T1, typename T2, typename T3>
    using f = dispatch<4, C>::template f<dispatch<1, F0>::template f<T0>,
                                            dispatch<1, F1>::template f<T1>,
                                            dispatch<1, F2>::template f<T2>,
                                            dispatch<1, F3>::template f<T3>>;
};
} // inline namespace each_impl
inline namespace each_test {
} // inline namespace each_test

inline namespace erase {
// erase_ : Given a VPP, remove the nth value in the pack.
// Reduces the size of the list by 1.
// Input params: Parameter pack
// Closure params: N - Positive integer type of index of element to remove
//                 C - Continuation; default listify_
// Functional description:
// input  -  T0, T1, ..., T(M - 1), TM, T(M + 1), ..., TN
// apply  -  (erase element at index M)
// result -  T0, T1, ..., T(M - 1), T(M + 1), ..., TN
// Empty return type: list_<>
export template <typename N = sizet_<0>, typename C = listify_>
struct erase_ {};
inline namespace erase_implementation {
template <std::size_t N, typename I, typename C>
struct dispatch<N, erase_<I, C>> {
    template <typename... Ts>
    using f = dispatch<N,
        rotate_<I,
            pop_front_<rotate_<sizet_<(sizeof...(Ts) - I::value - 1)>, C>>>>::template f<Ts...>;
};
template <typename I, typename C>
struct dispatch<0, erase_<I, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<nothing_>;
};
} // inline namespace erase_implementation
inline namespace erase_test { 
template<typename T> requires(std::same_as<T, list_<int_<2>, int_<3>>>)
struct EraseFirstElement;

// Erasing an element from a list with a single element will always result in empty list.
template<typename T> requires(std::same_as<T, list_<>>)
struct EraseSingleElement;

// UNDER RECONSIDERATION: Returns list_<nothing_> if no input is given.
template<typename T> requires(std::same_as<T, list_<nothing_>>)
struct EmptyPackReturnsNothingType;

using test_one   = EraseFirstElement<call_<erase_<sizet_<0>>, int_<1>, int_<2>, int_<3>>>;

using test_two   = EraseSingleElement<call_<erase_<sizet_<0>>, int_<0>>>;

using test_three = EmptyPackReturnsNothingType<call_<erase_<sizet_<0>>>>;
} // inline namespace erase_test
} // namespace erase

inline namespace index {
export template<typename I, typename C = identity_>
struct index_ {};
export template<typename I, typename C = identity_>
using unpack_index_ = unpack_<index_<I, C>>;
export template<typename C = identity_>
using front_ = index_<sizet_<0>, C>;
export template<typename C = identity_>
using i0_ = index_<sizet_<0>, C>;
export template<typename C = identity_>
using i1_ = index_<sizet_<1>, C>;
export template<typename C = identity_>
using i2_ = index_<sizet_<2>, C>;
export template<typename C = identity_>
using i3_ = index_<sizet_<3>, C>;
export template<typename C = identity_>
using i4_ = index_<sizet_<4>, C>;
export template<typename C = identity_>
using i5_ = index_<sizet_<5>, C>;
export template<typename C = identity_>
using i6_ = index_<sizet_<6>, C>;
export template<typename C = identity_>
using i7_ = index_<sizet_<7>, C>;
export template<typename C = identity_>
using ui0_ = unpack_<index_<sizet_<0>, C>>;
export template<typename C = identity_>
using ui1_ = unpack_<index_<sizet_<1>, C>>;
export template<typename C = identity_>
using ui2_ = unpack_<index_<sizet_<2>, C>>;
export template<typename C = identity_>
using ui3_ = unpack_<index_<sizet_<3>, C>>;
export template<typename C = identity_>
using ui4_ = unpack_<index_<sizet_<4>, C>>;
export template<typename C = identity_>
using ui5_ = unpack_<index_<sizet_<5>, C>>;
export template<typename C = identity_>
using ui6_ = unpack_<index_<sizet_<6>, C>>;
export template<typename C = identity_>
using ui7_ = unpack_<index_<sizet_<7>, C>>;
inline namespace index_implementation {
template <std::size_t N, typename I, typename C>
struct dispatch<N, index_<I, C>> : dispatch<N, drop_<I, front_<C>>> {};

template <std::size_t N, typename C>
struct dispatch<N, index_<nothing_, C>> {
    template <typename... Ts>
    using f = nothing_;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<0>, C>> {
    template <typename T0, typename... Ts>
    using f = dispatch<1, C>::template f<T0>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<1>, C>> {
    template <typename T0, typename T1, typename... Ts>
    using f = dispatch<1, C>::template f<T1>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<2>, C>> {
    template <typename T0, typename T1, typename T2, typename... Ts>
    using f = dispatch<1, C>::template f<T2>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<3>, C>> {
    template <typename T0, typename T1, typename T2, typename T3, typename... Ts>
    using f = dispatch<1, C>::template f<T3>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<4>, C>> {
    template<typename T0, typename T1, typename T2, typename T3,
                typename T4, typename... Ts>
    using f = dispatch<1, C>::template f<T4>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<5>, C>> {
    template<typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename... Ts>
    using f = dispatch<1, C>::template f<T5>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<6>, C>> {
    template<typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename... Ts>
    using f = dispatch<1, C>::template f<T6>;
};
template <std::size_t N, typename C>
struct dispatch<N, index_<sizet_<7>, C>> {
    template <typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename T7, typename... Ts>
    using f = dispatch<1, C>::template f<T7>;
};
} // inline namespace index_implementation
} // inline namespace index

} // namespace boost::tmp
