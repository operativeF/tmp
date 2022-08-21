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

export module Boost.TMP:Algorithm.Chunk;

import :Algorithm.Counted;
import :Algorithm.MakeSequence;
import :Algorithm.Tee;
import :Base.Types;

namespace boost::tmp {

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

// chunk_ : implementation
// TODO: Move this to MakeSequence module.
template <std::size_t N>
using make_index_for_stride = make_seq_impl<next_state(0, N)>::template f<N>;

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
template<typename S, typename C, typename... Ts>
struct chunk_impl {};
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

} // namespace boost::tmp

namespace chunk_test {
using namespace boost::tmp;

template<typename T> requires(std::same_as<T, list_<list_<int_<0>, int_<1>, int_<2>>,
                                                    list_<int_<3>, int_<4>, int_<5>>,
                                                    list_<int_<6>, int_<7>>>>)
struct ChunkEveryThreeElements;

using chunk_test_1 = ChunkEveryThreeElements<call_<chunk_<sizet_<3>>, int_<0>, int_<1>, int_<2>, int_<3>, int_<4>, int_<5>, int_<6>, int_<7>>>;

} // namespace chunk_test
