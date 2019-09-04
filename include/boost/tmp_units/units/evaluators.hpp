#ifndef BOOST_TMP_EVALUATORS_HPP_INCLUDED
#define BOOST_TMP_EVALUATORS_HPP_INCLUDED

//  Copyright 2018-2019 Odin Holmes.
//						Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <cassert>
#include <ratio>

#include <boost/tmp/sequence/set.hpp>
#include <boost/tmp/vocabulary.hpp>
#include "type_dispatcher.hpp"

namespace boost::tmp::units
{
    // @TODO: Add selection for largest ratio of the two inputs.
    // @TODO: Add multiplication / division by scalar

	template<typename F, typename G>
	using multiplier_fin = call_<set_multiplier_<>, typename F::impl, typename G::impl>;

	template<typename T, typename U>
	using multi_type = typename dispatcher<multiplier_fin<T, U>>::template f<typename T::mod_ratio, decltype(U::value)>;

    template<typename F, typename G>
	using quotient_fin = call_<set_quotient_<>, typename F::impl, typename G::impl>;

    template<typename T, typename U>
    using div_type = typename dispatcher<quotient_fin<T, U>>::template f<typename T::mod_ratio, decltype(U::value)>;

    // Operations
    template<typename T>
	constexpr T operator+(T aVal, T bVal)
	{
		return aVal.value + bVal.value;
	}

	template<typename T>
	constexpr T operator-(T aVal, T bVal)
	{
		return aVal.value - bVal.value;
	}

	// @TODO: Need to add ratio conversions.
	template<typename T, typename U>
	constexpr auto operator*(T aVal, U bVal) -> multi_type<T, U>
	{
		return aVal.value * bVal.value;
	}

	// @TODO: Need to add ratio conversions.
	template<typename T, typename U>
	constexpr auto operator/(T aVal, U bVal) -> div_type<T, U>
	{
        static_assert(bVal.value != 0);
        return aVal.value / bVal.value;
	}

    template<typename T, typename U>
    constexpr bool operator==(T aVal, U bVal)
    {
        // Check if both have same underlying type
        static_assert(std::is_same_v<typename T::impl, typename U::impl>, "Underlying types need to be the same.");
        // If so, normalize to base unit if ratios are different
        auto aVal_ = convertTo<T>()(aVal);
        auto bVal_ = convertTo<T>()(bVal);

        return (aVal_.value == bVal_.value);
    }

	template<typename T, typename U>
    constexpr bool operator!=(T aVal, U bVal)
    {
        // Check if both have same underlying type
        static_assert(std::is_same_v<typename T::impl, typename U::impl>, "Underlying types need to be the same.");
        // If so, normalize to base unit if ratios are different
        auto aVal_ = convertTo<T>()(aVal);
        auto bVal_ = convertTo<T>()(bVal);

        return (aVal_.value != bVal_.value);
    }

	template<typename T, typename U>
    constexpr bool operator<(T aVal, U bVal)
    {
        // Check if both have same underlying type
        static_assert(std::is_same_v<typename T::impl, typename U::impl>, "Underlying types need to be the same.");
        // If so, normalize to base unit if ratios are different
        auto aVal_ = convertTo<T>()(aVal);
        auto bVal_ = convertTo<T>()(bVal);

        return (aVal_.value < bVal_.value);
    }

	template<typename T, typename U>
    constexpr bool operator>(T aVal, U bVal)
    {
        // Check if both have same underlying type
        static_assert(std::is_same_v<typename T::impl, typename U::impl>, "Underlying types need to be the same.");
        // If so, normalize to base unit if ratios are different
        auto aVal_ = convertTo<T>()(aVal);
        auto bVal_ = convertTo<T>()(bVal);

        return (aVal_.value > bVal_.value);
    }

	template<typename T, typename U>
    constexpr bool operator>=(T aVal, U bVal)
    {
        // Check if both have same underlying type
        static_assert(std::is_same_v<typename T::impl, typename U::impl>, "Underlying types need to be the same.");
        // If so, normalize to base unit if ratios are different
        auto aVal_ = convertTo<T>()(aVal);
        auto bVal_ = convertTo<T>()(bVal);

        return (aVal_.value >= bVal_.value);
    }

	template<typename T, typename U>
    constexpr bool operator<=(T aVal, U bVal)
    {
        // Check if both have same underlying type
        static_assert(std::is_same_v<typename T::impl, typename U::impl>, "Underlying types need to be the same.");
        // If so, normalize to base unit if ratios are different
        auto aVal_ = convertTo<T>()(aVal);
        auto bVal_ = convertTo<T>()(bVal);

        return (aVal_.value <= bVal_.value);
    }

} // namespace boost::tmp::units

#endif // BOOST_TMP_EVALUATORS_HPP_INCLUDED