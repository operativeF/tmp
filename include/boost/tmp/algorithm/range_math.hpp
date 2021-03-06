#ifndef BOOST_TMP_RANGE_MATH_HPP_INCLUDED
#define BOOST_TMP_RANGE_MATH_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/algorithm/fold_left.hpp>
#include <boost/tmp/algorithm/fold_right.hpp>
#include <boost/tmp/algorithm/sort.hpp>
#include <boost/tmp/algorithm/transform.hpp>
#include <boost/tmp/call.hpp>
#include <boost/tmp/identity.hpp>
#include <boost/tmp/if.hpp>
#include <boost/tmp/logic.hpp>
#include <boost/tmp/sequence/tee.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace boost {
	namespace tmp {
		template <typename C = identity_>
		struct accumulate_;

		template <typename C = identity_>
		struct decimate_right_;

		template <typename C = identity_>
		struct decimate_left_;

		template <typename C = identity_>
		struct sorted_decimate_;

		template <typename C = identity_>
		struct multiplicate_;

		namespace detail {
			template <typename T, typename U>
			using add_ = int_<(T::value + U::value)>;

			template <typename T, typename U>
			using subtract_ = int_<(T::value - U::value)>;

			template <typename T, typename U>
			using multiply_ = int_<(T::value * U::value)>;

			template <typename T, typename U>
			using less = bool_<(T::value < U::value)>;

			template <unsigned N, typename C>
			struct dispatch<N, accumulate_<C>> : dispatch<N, fold_right_<lift_<add_>, C>> {};

			template <unsigned N, typename C>
			struct dispatch<N, sorted_decimate_<C>>
			    : dispatch<N, sort_<lift_<less, C>, fold_right_<lift_<subtract_>, C>>> {};

			template <unsigned N, typename C>
			struct dispatch<N, decimate_right_<C>> : dispatch<N, fold_right_<lift_<subtract_>, C>> {
			};

			template <unsigned N, typename C>
			struct dispatch<N, decimate_left_<C>> : dispatch<N, fold_left_<lift_<subtract_>, C>> {};

			template <unsigned N, typename C>
			struct dispatch<N, multiplicate_<C>> : dispatch<N, fold_right_<lift_<multiply_>, C>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif // BOOST_TMP_RANGE_MATH_HPP_INCLUDED