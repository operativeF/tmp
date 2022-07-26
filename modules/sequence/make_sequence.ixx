//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Sequence.MakeSequence;

import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Algorithm.Transform;
import Boost.TMP.Sequence.Unpack;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

// FIXME: make_seq_impl used elsewhere.
export namespace boost::tmp {
	template <typename F = identity_, typename C = listify_>
	struct make_sequence_ {};
	
	namespace detail {
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
			using f = typename make_seq_impl<next_state(
				    2 * sizeof...(Is), End)>::template f<End, Is..., (Is + sizeof...(Is))...>;
		};
		template <>
		struct make_seq_impl<3> { // double +1
			template <std::size_t End, std::size_t... Is>
			using f =
				    typename make_seq_impl<next_state(2 * sizeof...(Is) + 1, End)>::template f<
				            End, Is..., (Is + sizeof...(Is))..., (2 * sizeof...(Is))>;
		};

		template <typename F, typename C>
		struct dispatch<1, make_sequence_<F, C>> {
			template <typename N>
			using f = typename dispatch<1, unpack_<transform_<F, C>>>::template f<
				    typename make_seq_impl<next_state(0, N::value)>::template f<N::value>>;
		};
	} // namespace detail
} // namespace boost::tmp
