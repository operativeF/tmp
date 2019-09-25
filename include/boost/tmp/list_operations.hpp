#ifndef BOOST_TMP_SLIST_HPP_INCLUDED
#define BOOST_TMP_SLIST_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/call.hpp>
#include <boost/tmp/identity.hpp>
#include <boost/tmp/if.hpp>
#include <boost/tmp/logic.hpp>
#include <boost/tmp/vocabulary.hpp>

#include <boost/tmp/algorithm/contains.hpp>
#include <boost/tmp/sequence/erase.hpp>

namespace boost {
	namespace tmp {
		namespace detail {

		template <typename T, typename U>
		using get_index_from_value = call_<unpack_<find_if_<is_<T>>>, U>;

		template <typename T, typename I>
		using erase_at = call_<unpack_<erase_<detail::get_index_from_value<I, T>>>, T>;

		template <typename T, typename U>
		using contains_swap = call_<unpack_<contains_<U>>, T>;

		} // namespace detail
		
		template <typename Num, typename Den>
		using divide_lists = call_<unpack_<push_front_<Num, fold_left_<if_<lift_<detail::contains_swap>, lift_<detail::erase_at>, front_<>>>>>, Den>;

		template <typename Num, typename Den>
		using full_divide_lists = list_<divide_lists<Num, Den>, divide_lists<Den, Num>>;

	} // namespace tmp
} // namespace boost

#endif