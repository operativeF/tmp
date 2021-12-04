//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Sequence.Erase;

import Boost.TMP.Sequence.Drop;
import Boost.TMP.Sequence.PopFront;
import Boost.TMP.Sequence.Rotate;

import Boost.TMP.Base.Vocabulary;

// \brief
// Given a variadic parameter pack, remove the nth value in the pack.
// Reduces the size of the list by 1 as a result.
export namespace boost::tmp {
		template <typename N = uint_<0>, typename C = listify_>
		struct erase_ {};

		namespace detail {
			template <unsigned N, typename I, typename C>
			struct dispatch<N, erase_<I, C>> {
				template <typename... Ts>
				using f = typename dispatch<
				        N,
				        rotate_<I, pop_front_<rotate_<uint_<(sizeof...(Ts) - I::value - 1)>, C>>>>::
				        template f<Ts...>;
			};
			template <typename I, typename C>
			struct dispatch<0, erase_<I, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<nothing_>;
			};
		} // namespace detail
} // export namespace boost::tmp
