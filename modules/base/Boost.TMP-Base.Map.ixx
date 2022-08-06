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
