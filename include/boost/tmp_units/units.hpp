#ifndef BOOST_TMP_UNITS_HPP_INCLUDED
#define BOOST_TMP_UNITS_HPP_INCLUDED

//  Copyright 2019 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/sequence/set.hpp>
#include <boost/tmp/identity.hpp>
#include <boost/tmp/sequence/drop.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace tmp {
    namespace units {

        template<typename C = listify_>
        struct multiply_units_;

        template<typename C = listify_>
        struct divide_units_;

        namespace detail {

            template<unsigned N, typename C>
            struct dispatch<N, multiply_units_<C>> {
                template<typename T, typename U>
                using f = call_<>;
            };

        } // namespace detail

    } // namespace units

} // namespace tmp

#endif