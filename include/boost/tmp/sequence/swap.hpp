#ifndef BOOST_TMP_SWAP_HPP_INCLUDED
#define BOOST_TMP_SWAP_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

/// \brief Swaps two variadic parametic pack values. Must be only two values.
#include <boost/tmp/identity.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace boost {
	namespace tmp {
		template <typename C = listify_>
		struct swap_ {};
		namespace detail {
			template <typename C>
			struct dispatch<2, swap_<C>> {
				template <typename T, typename U>
				using f = typename dispatch<2, C>::template f<U, T>;
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif
