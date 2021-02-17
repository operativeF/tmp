#ifndef BOOST_TMP_DECAY_HPP_INCLUDED
#define BOOST_TMP_DECAY_HPP_INCLUDED

//  Copyright 2020 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt


#include <type_traits>

namespace boost {
	namespace tmp {

		template <typename T, typename U = typename std::remove_reference_t<T>>
		struct decay {
			using type = std::remove_cv_t<U>;
		};

		template <typename T, typename U>
		struct decay<T, U[]> {
			using type = U*;
		};
		template <typename T, typename U, std::size_t N>
		struct decay<T, U[N]> {
			using type = U*;
		};

		template <typename T, typename R, typename... A>
		struct decay<T, R(A...)> {
			using type = R(*)(A...);
		};
		template <typename T, typename R, typename... A>
		struct decay<T, R(A..., ...)> {
			using type = R(*)(A..., ...);
		};

	} // namespace tmp
} // namespace boost

#endif