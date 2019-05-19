#ifndef BOOST_TMP_ANY_OF_HPP_INCLUDED
#define BOOST_TMP_ANY_OF_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/algorithm/find_if.hpp>
#include <boost/tmp/call.hpp>
#include <boost/tmp/identity.hpp>
#include <boost/tmp/if.hpp>
#include <boost/tmp/logic.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace boost {
	namespace tmp {
		template <typename F = identity_, typename C = identity_>
		struct any_of_;

		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, any_of_<F, C>>
			    : dispatch<N,
			               find_if_<F, if_<is_<nothing_>, always_<false_, C>, always_<true_, C>>>> {
			};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif