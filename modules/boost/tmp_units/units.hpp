#ifndef BOOST_TMP_UNITS_HPP_INCLUDED
#define BOOST_TMP_UNITS_HPP_INCLUDED

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

        template<typename T>
        struct unit_ {
            using numer_ = list_<>;
            using denom_ = list_<>;

            using list_type = list_<numer_, denom_>;

            using type = composite_lu_<list_type>;
            using primitive_unit = call_<primitize_<>, list_type>;
        };

        // Equivalent to multiplying the units
        template<typename T, typename U, typename C = listify_>
        struct push_numer_ {};

        // Equivalent to multiplying the units
        template<typename T, typename U, typename C = listify_>
        struct push_denom_ {};

        // Remove units that are in both the numerator and denominator,
        // returning the resulting sequence. Done after a decomposition.
        template<typename T, typename C = listify_>
        struct cancellate_ {};

        namespace detail {

            template<typename T, typename U, typename C>
            struct push_numer_impl

        } // namespace detail

    } // namespace units

} // namespace tmp

#endif