//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP:Base.Map;

import :Algorithm.Sort;
import :Base.Dispatch;
import :Base.Lift;
import :Base.List;
import :Sequence.Unpack;
import :Sequence.ZipWithIndex;

import std;

namespace boost::tmp {

export template <typename CompareF, typename C = listify_>
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
