#ifndef BOOST_TMP_COUNT_IF_HPP_INCLUDED
#define BOOST_TMP_COUNT_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/algorithm/transform.hpp>
#include <boost/tmp/call.hpp>
#include <boost/tmp/detail/dispatch.hpp>
#include <boost/tmp/if.hpp>
#include <boost/tmp/sequence/join.hpp>
#include <boost/tmp/sequence/size.hpp>
#include <boost/tmp/vocabulary.hpp>

/// \brief Given a predicate F, check the variadic parameter pack passed in and count
/// each time that the predicate holds true. Returns n counts as uint_<n>.
/// \example
///
namespace boost {
	namespace tmp {
		template <typename F, typename C = identity_>
		struct count_if_ {};
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, count_if_<F, C>>
			    : dispatch<N, transform_<if_<F, always_<list_<void>>, always_<list_<>>>,
			                             join_<size_<C>>>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif