#ifndef BOOST_TMP_UNITS_MOLECULIZE_HPP_INCLUDED
#define BOOST_TMP_UNITS_MOLECULIZE_HPP_INCLUDED

//  Copyright 2019 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/identity.hpp>
#include <boost/tmp/sequence/drop.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace tmp {
    namespace units {
        
        template<typename T, typename C = listify_>
        struct moleculize_ {};

        namespace detail {

        } // namespace detail

    } // namespace units

} // namespace tmp

#endif