#ifndef BOOST_TMP_UNITS_PRIMARIES_HPP_INCLUDED
#define BOOST_TMP_UNITS_PRIMARIES_HPP_INCLUDED

#include <boost/tmp/identity.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>

namespace boost::tmp::units
{
    struct length {};
    struct distance {};
    struct time {};
    struct mass {};

	using primaries = list_<
        list_<list_<length>>, // Base length
        list_<list_<length, length>>, // Area
        list_<list_<length, length, length>>, // Volume
        list_<list_<length>, list_<time>>, // Velocity
        list_<list_<distance>, list_<time>>, // Speed
        list_<list_<length>, list_<time, time>> // Acceleration
        >;
} // namespace boost::tmp::units

#endif // BOOST_TMP_UNITS_DESCR_HPP_INCLUDED