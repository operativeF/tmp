#ifndef BOOST_TMP_UNITS_DESCR_HPP_INCLUDED
#define BOOST_TMP_UNITS_DESCR_HPP_INCLUDED

//  Copyright 2019 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <units.hpp>

#include <boost/tmp/identity.hpp>
#include <boost/tmp/sequence/drop.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace tmp {
    namespace units {

        // Basic units
        struct length_ {};
        struct mass_ {};
        struct volume_ {};
        struct time_ {};
        struct temperature_ {};
        struct luminous_intensity_ {};

        struct Length {
            using numer_ = boost::tmp::list_<length_>;
            using denom_ = boost::tmp::list_<>;

            using type = boost::tmp::list_<numer_, denom_>;
        };
        struct Area {
            using numer_ = boost::tmp::list_<length_, length_>;
            using denom_ = boost::tmp::list_<>;

            using type = boost::tmp::list_<numer_, denom_>;
        };

        
        struct Volume {

            template<typename T>
            struct isConvertableToLVolume {};

            template<typename T>
            struct isConvertableToSVolume {};

            using numer_s = boost::tmp::list_<length_, length_, length_>;
            using numer_l = boost::tmp::list_<volume_>;
            using denom_ = boost::tmp::list_<>;

            // Volume in units of a liquid / gas
            using type_l = boost::tmp::list_<numer_l, denom_>;

            // Volume in units of a solid
            using type_s = boost::tmp::list_<numer_s, denom_>;
        };

        namespace detail {
            template<typename C = listify_>
            struct unpack_unit_ : T {};
        } // namespace detail
    } // namespace units

} // namespace tmp

#endif // BOOST_TMP_UNITS_DESCR_HPP_INCLUDED