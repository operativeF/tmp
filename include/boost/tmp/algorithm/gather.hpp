#ifndef BOOST_TMP_PRODUCT_HPP_INCLUDED
#define BOOST_TMP_PRODUCT_HPP_INCLUDED

//  Copyright 2019 Odin Holmes.
//                 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/call.hpp>
#include <boost/tmp/vocabulary.hpp>
#include <boost/tmp/sequence/join.hpp>

namespace boost {
	namespace tmp {
        // Sorts, and then groups items into a list of lists of the same type.
        template<typename F, typename C = listify_>
        struct gather_;

		namespace detail {
            template <unsigned N, typename F, typename C>
			struct dispatch<N, gather_<F, C>>{};

		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif