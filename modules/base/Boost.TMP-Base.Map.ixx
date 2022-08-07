//  Copyright 2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Map;

import :Algorithm.FindIf;
import :Algorithm.Sort;
import :Base.Call;
import :Base.Dispatch;
import :Base.Lift;
import :Sequence.Index;
import :Sequence.ZipWithIndex;

#if _MSC_VER
import std;
#endif // _MSC_VER

namespace boost::tmp {

export template<typename... Elements>
struct MapType {
    template<typename InputPos>
    struct matches_input_pos {
        template<typename T>
        using f = bool_<(InputPos::value == T::value)>;
    };

    template<typename InputPos>
    using get_memory_pos = call_<find_if_<lift_<matches_input_pos<InputPos>::template f>>, typename Elements::init_pos...>;

    template<typename InputPos>
    using get_type_from_input_pos = call_<index_<get_memory_pos<InputPos>>, typename Elements::value...>;
};

export using mapify_ = lift_<MapType>;

export template <typename CompareF, typename C = mapify_>
struct map_ {};

export template<typename V, typename InitialPos, typename SortedPos>
struct map_element_ {
    using value = V;
    using init_pos = InitialPos;
    using sort_pos = SortedPos;
};

template<typename InitialPos, typename V>
struct element_ {
    using value = V;
    using init_pos = InitialPos;
};

template<typename T, typename U>
using make_map_element_ = map_element_<typename U::value, typename U::init_pos, T>;

template<std::size_t N, typename F, typename C>
struct dispatch<N, map_<F, C>>
{
    template<typename... Ts>
    using f = dispatch<N, zip_with_index_<lift_<element_>, sort_<F, zip_with_index_<lift_<make_map_element_>, C>>>>::template f<Ts...>;
};

template<std::size_t N, template<typename...> typename F, typename C>
struct dispatch<N, map_<lift_<F>, C>>
{
    template<typename... Ts>
    using f = dispatch<N, zip_with_index_<lift_<element_>, sort_<lift_<F>, zip_with_index_<lift_<make_map_element_>, C>>>>::template f<Ts...>;
};

} // namespace boost::tmp

namespace map_test {
    using namespace boost::tmp;

    // TODO: Implement map_test
    // template<typename T, typename U>
    // using less_than = bool_<(T::value::value < U::value::value)>;

    // template<typename T, typename U>
    // using greater_than_t = bool_<std::alignment_of_v<typename U::value> < std::alignment_of_v<typename T::value>>;

    // template<int V1, int V2>
    // struct two_ints {
    //     int a{V1};
    //     int b{V2};
    // };

    // template<int V1, int V2, int V3>
    // struct three_ints {
    //     int a{V1};
    //     int b{V2};
    //     int c{V3};
    // };

    // Map by element value
    // using ab_map = call_<map_<lift_<less_than>>, char_<'a'>, char_<'b'>>;
    // MapType<map_element_<char_<'a'>, sizet_<0>, sizet_<0>>, map_element_<char_<'b'>, sizet_<1>, sizet_<1>>>{} =
    //     ab_map{};
    
    // char_<'a'>{} = ab_map::get_type_from_input_pos<sizet_<0>>{};

    // // Map by type size; greatest size to least
    // using adv_map = call_<map_<lift_<greater_than_t>>, int_<1>, three_ints<1, 3, 5>, two_ints<1, 2>>;
    // MapType<map_element_<three_ints<1, 3, 5>, sizet_<1>, sizet_<0>>, map_element_<two_ints<1, 2>, sizet_<2>, sizet_<1>>, map_element_<int_<1>, sizet_<0>, sizet_<2>>>{} = adv_map{};

    // two_ints<1, 2>{} = adv_map::get_type_from_input_pos<sizet_<2>>{};
    // sizet_<1>{}      = adv_map::get_memory_pos<sizet_<2>>{};

} // namespace map_test
