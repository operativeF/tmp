//  Copyright 2018 Odin Holmes.
//            2020-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Algorithm.RangeMath;

import Boost.TMP.Algorithm.FoldLeft;
import Boost.TMP.Algorithm.FoldRight;
import Boost.TMP.Algorithm.Sort;
import Boost.TMP.Algorithm.Transform;

import Boost.TMP.Detail.Dispatch;

import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Sequence.Tee;
import Boost.TMP.Sequence.Unpack;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename C = identity_>
	struct accumulate_ {};

	export template <typename C = identity_>
	struct decimate_right_ {};

	export template <typename C = identity_>
	struct decimate_left_ {};

	export template <typename C = identity_>
	struct sorted_decimate_ {};

	export template <typename C = identity_>
	struct multiplicate_ {};

	namespace detail {
		template <typename T, typename U>
		using add_ = int_<(T::value + U::value)>;

		template <typename T, typename U>
		using subtract_ = int_<(T::value - U::value)>;

		template <typename T, typename U>
		using multiply_ = int_<(T::value * U::value)>;

		template <typename T, typename U>
		using less = bool_<(T::value < U::value)>;

		template <std::size_t N, typename C>
		struct dispatch<N, accumulate_<C>> : dispatch<N, fold_right_<lift_<add_>, C>> {};

		template <std::size_t N, typename C>
		struct dispatch<N, sorted_decimate_<C>>
			: dispatch<N, sort_<lift_<less, C>, fold_right_<lift_<subtract_>, C>>> {};

		template <std::size_t N, typename C>
		struct dispatch<N, decimate_right_<C>> : dispatch<N, fold_right_<lift_<subtract_>, C>> {
		};

		template <std::size_t N, typename C>
		struct dispatch<N, decimate_left_<C>> : dispatch<N, fold_left_<lift_<subtract_>, C>> {};

		template <std::size_t N, typename C>
		struct dispatch<N, multiplicate_<C>> : dispatch<N, fold_right_<lift_<multiply_>, C>> {};
	} // namespace detail
} // namespace boost::tmp
