#ifndef BOOST_TMP_UNITS_ATOMIZE_HPP_INCLUDED
#define BOOST_TMP_UNITS_ATOMIZE_HPP_INCLUDED

//  Copyright 2019 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/identity.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace tmp {
    namespace units {

        // Break apart units of both numerator and denominator
        template<typename C>
        struct atomize_ {};

        namespace detail {
            template<typename C>
            struct atomize_impl {
                
            };


        } // namespace detail

    } // namespace units

} // namespace tmp

#endif