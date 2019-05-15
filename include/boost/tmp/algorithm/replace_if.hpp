#ifndef BOOST_TMP_REPLACE_IF_HPP_INCLUDED
#define BOOST_TMP_REPLACE_IF_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//                      Thomas Figueroa.
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

/// \brief Given a variadic parameter pack, replace every value that fulfills
/// the predicate F with the value Input.
namespace boost {
	namespace tmp {
		template <typename Input, typename F, typename C = listify_>
		struct replace_if_ {};
		namespace detail {
			template <unsigned N, typename Input, typename F, typename C>
			struct dispatch<N, replace_if_<Input, F, C>>
			    : dispatch<N, transform_<if_<F, always_<Input>, identity_>, C>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif