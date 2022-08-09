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

export module Boost.TMP:Sequence.Insert;

import :Base.Types;
import :Sequence.PushPop;
import :Sequence.Rotate;

#if _MSC_VER
import std;
#endif

///
// @BUG: This does not work as expected.
// Inserting will cause a permutation of the current list with the
// to-be-inserted value. Also, as long as N < size of input list, it'll compile.
// Attempting to insert a value in a position greater than the size of the list
// will result in an error, as the value goes negative.
namespace boost::tmp {
export template <typename N, typename V, typename C = listify_>
struct insert_ {};

template <std::size_t N, typename I, typename V, typename C>
struct dispatch<N, insert_<I, V, C>> {
    template <typename... Ts>
    using f = dispatch<N, rotate_<I, push_front_<V, rotate_<sizet_<(sizeof...(Ts) - I::value + 1)>,
                                                    C>>>>::template f<Ts...>;
};
template <typename I, typename V, typename C>
struct dispatch<0, insert_<I, V, C>> {
    template <typename... Ts>
    using f = dispatch<1, C>::template f<V>;
};
} // namespace boost::tmp

// TESTING:
namespace insert_test {
    using namespace boost::tmp;
    // Insert char_<'c'> at position 1
    template<typename T> requires(std::same_as<T, list_<int_<1>, char_<'c'>, int_<2>>>)
    struct Insert_C_AtPositionOne;

    // Insert char_<'c'> at position 0
    template<typename T> requires(std::same_as<T, list_<char_<'c'>, int_<1>, int_<2>>>)
    struct Insert_C_AtPositionZero;

    // Insert char_<'c'> at position 2
    template<typename T> requires(std::same_as<T, list_<int_<1>, int_<2>, char_<'c'>>>)
    struct Insert_C_AtPositionTwo;

    // Insert char_<'c'> into no list (returns a list_ with char_<'c'> in it)
    template<typename T> requires(std::same_as<T, list_<char_<'c'>>>)
    struct EmptyPackInsertionReturnsSingleElementList;

    using test_one   = Insert_C_AtPositionZero<call_<insert_<int_<0>, char_<'c'>>, int_<1>, int_<2>>>;
    using test_two   = Insert_C_AtPositionOne<call_<insert_<int_<1>, char_<'c'>>, int_<1>, int_<2>>>;
    using test_three = Insert_C_AtPositionTwo<call_<insert_<int_<2>, char_<'c'>>, int_<1>, int_<2>>>;
    using test_four  = EmptyPackInsertionReturnsSingleElementList<call_<insert_<int_<0>, char_<'c'>>>>;
} // namespace insert_test
