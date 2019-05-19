#ifndef BOOST_TMP_NONE_OF_HPP_INCLUDED
#define BOOST_TMP_NONE_OF_HPP_INCLUDED

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
#include <boost/tmp/algorithm/find_if.hpp>
#include <boost/tmp/algorithm/transform.hpp>

namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct none_of_;

		// @TODO: Make this shorting.
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, none_of_<F, C>>
                : dispatch<N, and_<F, not_<C>>> {};
		} // namespace detail
    } // namespace tmp
} // namespace boost

#endif