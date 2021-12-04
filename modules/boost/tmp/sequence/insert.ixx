//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Sequence.Insert;

import Boost.TMP.Sequence.Drop;
import Boost.TMP.Sequence.PushFront;
import Boost.TMP.Sequence.Rotate;

import Boost.TMP.Base.Vocabulary;

///
// @BUG: This does not work as expected.
// Inserting will cause a permutation of the current list with the
// to-be-inserted value. Also, as long as N < size of input list, it'll compile.
// Attempting to insert a value in a position greater than the size of the list
// will result in an error, as the value goes negative.
export namespace boost::tmp {
		template <typename N = uint_<0>, typename V = nothing_, typename C = listify_>
		struct insert_ {};

		namespace detail {
			template <unsigned N, typename I, typename V, typename C>
			struct dispatch<N, insert_<I, V, C>> {
				template <typename... Ts>
				using f = typename dispatch<
				        N, rotate_<I, push_front_<V, rotate_<uint_<(sizeof...(Ts) - I::value - 1)>,
				                                             C>>>>::template f<Ts...>;
			};
			template <typename I, typename V, typename C>
			struct dispatch<0, insert_<I, V, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<V>;
			};
		} // namespace detail
} // export namespace boost::tmp
