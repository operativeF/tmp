#ifndef BOOST_TMP_WHILE_HPP_INCLUDED
#define BOOST_TMP_WHILE_HPP_INCLUDED

//  Copyright 2019 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp.hpp>
#include "test_util.hpp"

namespace boost
{
    namespace tmp
    {

    struct continue_ {};

    template<typename F, typename C = listify_>
    struct while_ {};

    namespace detail {

        template<typename F, typename C>
        struct dispatch<1, while_<F, C>> {};

        template<unsigned N, typename F, typename C>
        struct dispatch<N, while_<F, C>> {
            using f = call_<if_<F, find_if_<is_<continue_, if_<is_<greater_<int_<0>>>, while_<F, C>, join_<C>>>>, join_<C>>, C>;
        };

    } // namespace detail

    } // namespace tmp
} // namespace boost

#endif // BOOST_TMP_WHILE_HPP_INCLUDED