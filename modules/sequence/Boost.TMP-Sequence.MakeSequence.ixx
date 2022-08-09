//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Sequence.MakeSequence;

import :Algorithm.Transform;
import :Base.Call;
import :Base.Types;
import :Sequence.Unpack;

#if _MSC_VER
import std;
#endif

// FIXME: make_seq_impl used elsewhere.
// TODO: Generalized to all integers.
namespace boost::tmp {
    export template <typename F = identity_, typename C = listify_>
    struct make_sequence_ {};
    
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

    export template <std::size_t State>
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
} // namespace boost::tmp

// TESTING:
namespace make_sequence_test {
    using namespace boost::tmp;

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

    using test_one = ListZeroOneTwo<call_<make_sequence_<>, sizet_<3>>>;
    using test_two = ListOneTwoThree<call_<make_sequence_<lift_<and_one>>, sizet_<3>>>;
} // namespace make_sequence_test
