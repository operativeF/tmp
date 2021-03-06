#ifndef BOOST_TMP_REMOVE_IF_HPP_INCLUDED
#define BOOST_TMP_REMOVE_IF_HPP_INCLUDED

//  Copyright 2018 Odin Holmes.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/algorithm/transform.hpp>
#include <boost/tmp/always.hpp>
#include <boost/tmp/call.hpp>
#include <boost/tmp/detail/dispatch.hpp>
#include <boost/tmp/if.hpp>
#include <boost/tmp/sequence/join.hpp>
#include <boost/tmp/vocabulary.hpp>

/// \brief Given a predicate F, check the variadic parameter pack passed in
/// and remove the value if the predicate holds true.
namespace boost {
	namespace tmp {
		template <typename F, typename C = listify_>
		struct remove_if_ {};
		namespace detail {
			template <unsigned N, typename F, typename C>
			struct dispatch<N, remove_if_<F, C>>
			    : dispatch<N, transform_<if_<F, always_<list_<>>, listify_>, join_<C>>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif