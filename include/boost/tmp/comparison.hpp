#ifndef BOOST_TMP_COMPARISON_HPP_INCLUDED
#define BOOST_TMP_COMPARISON_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <type_traits>

#include <boost/tmp/vocabulary.hpp>

namespace boost {
	namespace tmp {
		template <typename P, typename C = identity_>
		struct is_ {};

		template <typename V = nothing_, typename C = identity_>
		struct less_ {};

		template <typename V = nothing_, typename C = identity_>
		struct greater_ {};

		template<typename V = nothing_, typename C = identity_>
		struct bounded_open {};

		template<typename V = nothing_, typename C = identity_>
		struct bounded_closed {};

		template<typename V = nothing_, typename C = identity_>
		struct bounded_clopen_lo {};

		template<typename V = nothing_, typename C = identity_>
		struct bounded_clopen_hi {};

		namespace detail {
			template <typename P, typename C>
			struct dispatch<1, is_<P, C>> {
				template <typename T>
				using f = typename dispatch<1, C>::template f<bool_<std::is_same<P, T>::value>>;
			};

			// NOTE: Internal compiler error occurs when no parentheses are used around the values.
			// Error is C1001; compiler file msc1.cpp, line 1596
			template <typename C>
			struct dispatch<2, less_<C>> {
				template <typename T, typename U>
				using f = typename dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
			};

			template <typename U, typename C>
			struct dispatch<1, less_<U, C>> {
				template<typename T>
				using f = typename dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
			};

			template <typename C>
			struct dispatch<2, greater_<C>> {
				template <typename T, typename U>
				using f = typename dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
			};

			template <typename U, typename C>
			struct dispatch<1, greater_<U, C>> {
				template<typename T>
				using f = typename dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost
#endif
