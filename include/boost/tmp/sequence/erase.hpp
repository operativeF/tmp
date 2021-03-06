#ifndef BOOST_TMP_ERASE_HPP_INCLUDED
#define BOOST_TMP_ERASE_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/sequence/drop.hpp>
#include <boost/tmp/sequence/pop_front.hpp>
#include <boost/tmp/sequence/rotate.hpp>
#include <boost/tmp/vocabulary.hpp>

// \brief
// Given a variadic parameter pack, remove the nth value in the pack.
// Reduces the size of the list by 1 as a result.
namespace boost {
	namespace tmp {
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
	} // namespace tmp
} // namespace boost

#endif