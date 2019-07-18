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
            using numer_ = T::numer;
            using denom_ = T::denom;

            using type = list_<numer_, denom_>;
        };

        template<typename... Ts>
        struct comp_unit_ {
            using numerator_ = list_<Ts::numer_...>;
            using denominator = list_<Ts::denom_...>;
            
            using type = list_<numerator_, denominator_>;
        };

        template<typename T, typename U, typename C = listify_>
        struct push_numer_ {};

        template<typename T, typename U, typename C = listify_>
        struct push_denom_ {};

        template<typename T, typename C = listify_>
        struct communitize_ {};

        namespace detail {


        } // namespace detail

    } // namespace units

} // namespace tmp

#endif