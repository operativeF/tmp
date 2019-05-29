#ifndef BOOST_TMP_SET_HPP_INCLUDED
#define BOOST_TMP_SET_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/algorithm/fold_left.hpp>
#include <boost/tmp/if.hpp>
#include <boost/tmp/sequence/push_front.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace boost {
	namespace tmp {
		namespace detail {
			template <typename T>
			struct unique_magic_type;

			struct unique_super_base {
				static constexpr bool contains(void *) {
					return false;
				}
			};

			template <typename Tail, typename T>
			struct unique_base : Tail {
				static constexpr bool contains(unique_magic_type<T> *) {
					return true;
				}
				using Tail::contains;
			};

			template <typename T, typename U>
			using is_in_set = bool_<T::contains(static_cast<detail::unique_magic_type<U> *>(0))>;
			using unique_push_if = if_<lift_<is_in_set>, front_<>, lift_<detail::unique_base>>;

		} // namespace detail
		using make_unique =
		        push_front_<detail::unique_super_base, fold_left_<detail::unique_push_if>>;
	} // namespace tmp
} // namespace boost

#endif