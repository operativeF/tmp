#ifndef BOOST_TMP_UNITS_COMPOSITE_HPP_INCLUDED
#define BOOST_TMP_UNITS_COMPOSITE_HPP_INCLUDED

#include <boost/tmp.hpp>
#include <boost/tmp/identity.hpp>
#include <boost/tmp/sequence/unpack.hpp>
#include <boost/tmp/vocabulary.hpp>
#include <boost/tmp/detail/capabilities.hpp>
#include <boost/tmp_units/primaries.hpp>

#include <type_traits>


namespace boost::tmp
{
	using AdditionOp = uint_<1>;
	using SubOp = uint_<2>;
	using MultiOp = uint_<3>;
	using DivOp = uint_<4>;
	using NoOp = uint_<0>;

	template<typename N0, typename C = listify_>
	struct composite_ {};
	
	namespace detail
	{
		template<unsigned N, typename C>
		struct composite_impl;

		template<typename C>
		struct composite_impl<NoOp::value, C> {
			template<typename T, typename U>
			using f = T;
		};
		template<typename C>
		struct composite_impl<AdditionOp::value, C> {
			template<typename T, typename U>
			using f = T;
		};
		template<typename C>
		struct composite_impl<SubOp::value, C> {
			template<typename T, typename U>
			using f = T;
		};

		template<typename T, typename U>
		using comp_join = call_<join_<>, T, U>;

		template<typename T, typename U>
		using set_diff_a = call_<set_difference_A_<>, T, U>;

		template<typename T, typename U>
		using set_diff_b = call_<set_difference_B_<>, T, U>;	

		template<typename C>
		struct composite_impl<MultiOp::value, C> {
			template<typename T, typename U>
			using f = call_<
				unpack_<
					tee_<
						tee_<
							i0_<>,
							i1_<>,
							join_<>
						>,
						tee_<
							i2_<>,
							i3_<>,
							join_<>
						>, C
					>
				>, comp_join<T, U>
			>;
		};
		template<typename C>
		struct composite_impl<DivOp::value, C> {
			template<typename T, typename U>
			using f =
			call_<
				unpack_<
					tee_<
						tee_<
							i0_<>,
							i3_<>,
							join_<>
						>,
						tee_<
							i1_<>,
							i2_<>,
							join_<>
						>,
						tee_<
							set_difference_A_<>,
							set_difference_B_<>,
							C
						>
					>
				>, comp_join<T, U>
			>;
		};

		template<unsigned N, typename N0, typename C>
		struct dispatch<N, composite_<N0, C>> {
			template<typename T, typename U>
			using f = typename composite_impl<N0::value, C>::template f<T, U>;
		};
	} // namespace detail
} // namespace boost::tmp

#endif // BOOST_TMP_UNITS_DESCR_HPP_INCLUDED