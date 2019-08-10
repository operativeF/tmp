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
#include <boost/tmp/sequence/index.hpp>
#include <boost/tmp/sequence/push_front.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace boost {
	namespace tmp {
		template<typename C = listify_>
		struct make_set_ {};

		template<typename C = listify_>
		struct empty_set {};

		template<typename C = listify_>
		struct cardinality_ {};

		// Get all of the elements that are in both passed in lists.
		// Equation: A U B
		template<typename C = listify_>
		struct union_ {};

		// Get only the elements common to both passed in lists.
		// Equation:
		template<typename C = listify_>
		struct intersection_ {};

		// Get all of the elements that are unique to both lists.
		// Equation: A - B
		template<typename C = listify_>
		struct symmetric_difference_ {};

		template<typename C = listify_>
		struct relative_complement_A_ {};

		template<typename C = listify_>
		struct relative_complement_B_ {};

		template<typename F, typename C = listify_>
		struct subset_ {};

		template<typename C = listify_>
		struct power_set_ {};

		namespace detail {
			template <typename T>
			struct unique_magic_type;

			// Our starting point; gets dropped off at the end.
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

				static constexpr bool equals(unique_magic_type<T> *) {

				}

				using Tail::contains;
			};

			template <typename T, typename U>
			using is_in_set = bool_<T::contains(static_cast<detail::unique_magic_type<U> *>(0))>;

			using unique_push_if = if_<lift_<is_in_set>, front_<>, lift_<detail::unique_base>>;
			
			template <typename T, typename U>
			using less = bool_<(T::value < U::value)>;

			// TODO: Make sorting optional.
			template<unsigned N, typename C>
			struct dispatch<N, make_set_<C>> :
				dispatch<N, push_front_<detail::unique_super_base,
						fold_left_<detail::unique_push_if,
							flatten_<drop_<uint_<1>, sort_<lift_<less>, C>>>
						>
					>
				> {};
			
			template <typename T, typename U>
			using is_equal = call_<is_<T>, U>;

			template <typename T>
			using is_equal_pair = call_<unpack_<lift_<is_equal>>, T>;

			template<typename T, typename U>
			using productize = call_<product_<>, T, U>;

			template<unsigned N, typename C>
			struct dispatch<N, union_<C>> {
				template<typename T, typename U>
				using f =
				call_<
					join_<
						make_set_<C>
					>, T, U
				>;
			};

			template<unsigned N, typename C>
			struct dispatch<N, intersection_<C>> {
				template<typename T, typename U>
				using f =
				call_<
					unpack_<
						filter_<lift_<is_equal_pair>,
							join_<make_set_<>>
						>
					>,
					productize<T, U>
				>;
			};

		} // namespace detail

		/*
		using new_set = call_<product_<>, aalist, bblist>;

		using filt_set = call_<unpack_<filter_<lift_<is_equal_pair>>>, new_set>;

		using union_ = call_<flatten_<>, filt_set>;

		using union__ = call_<unpack_<make_set>, union_>;

		using union___ = call_<flatten_<>, union__>;

		using union____ = call_<unpack_<drop_<uint_<1>>>, union___>;
		*/

		using make_set = push_front_<detail::unique_super_base, fold_left_<detail::unique_push_if>>;
	} // namespace tmp
} // namespace boost

#endif