#ifndef BOOST_TMP_CLAMP_HPP_INCLUDED
#define BOOST_TMP_CLAMP_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/call.hpp>
#include <boost/tmp/comparison.hpp>
#include <boost/tmp/identity.hpp>
#include <boost/tmp/if.hpp>
#include <boost/tmp/logic.hpp>
#include <boost/tmp/vocabulary.hpp>
#include <boost/tmp/algorithm/filter.hpp>
#include <boost/tmp/sequence/tee.hpp>
#include <boost/tmp/algorithm/remove_if.hpp>

namespace boost {
	namespace tmp {
		template <typename L, typename H, typename C = identity_>
		struct clamp_;

		namespace detail {
			template <unsigned N, typename L, typename H, typename C>
			struct dispatch<N, clamp_<L, H, C>> : dispatch<N, tee_<filter_<less_<L>, filter_<greater_<H> > >, C>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif