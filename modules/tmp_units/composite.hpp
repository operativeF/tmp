#ifndef BOOST_TMP_UNITS_COMPOSITE_HPP_INCLUDED
#define BOOST_TMP_UNITS_COMPOSITE_HPP_INCLUDED

#include <boost/tmp.hpp>
#include <boost/tmp/identity.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>
#include <boost/tmp/detail/capabilities.hpp>
//#include <moleculize.hpp>
//#include <atomize.hpp>
//#include <units.hpp>

#include <type_traits>


namespace boost::tmp
{
	//template<typename T, typename U>
	//using isScalarOperation = call_<or_<lift_<std::is_arithmetic<T>>>, std::is_arithmetic<U>>;

	template<typename C = listify_>
	struct divide_units_ {};

	// Removes items that are common to both of the lists;
	// this must be done one at a time, or removal may be erroneous.
	// Algorithm:
	// for all units in list A
	// if a unit matches in list B, pop_front of both
	// else, rotate list B
	template<typename T, typename U, typename C = listify_>
	struct cancellate_ {};

	template<typename T, typename U, typename Operation, typename C = listify_>
	struct composite_ {};
	
	//using type = call_<decompose_<if_<is_<divided>, divide_units_<>, if_<is_<multiplied>, multiply_units_<>, unknown_operator_<>>>, input_list>;
	namespace detail
	{
		template <typename T, typename U>
		using push = call_<join_<>, T, U>;

		template<unsigned N, typename C>
		struct dispatch< N, divide_units_<C> > {
			template<typename L1, typename L2>
			using f = call_< tee_< tee_<ui0_<>, ui3_<>, listify_>, tee_<ui1_<>, ui2_<>, listify_>, C>, push<L1, L2> >;
		};
/*
		template<unsigned N, typename C>
		struct dispatch< N, cancellate_<C> > {
			template<typename L1>
			using f = call_<tee_<tee_<remove_if_<>>, tee_<remove_if_<>>, C>, L1>;
		};
*/
	} // namespace detail
} // namespace boost::tmp

#endif // BOOST_TMP_UNITS_DESCR_HPP_INCLUDED