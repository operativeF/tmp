//  Copyright 2018-2019 Odin Holmes.
//			  2020-2021 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Sequence.Set;

import Boost.TMP.Base.Call;
import Boost.TMP.Base.If;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Algorithm.Flatten;
import Boost.TMP.Algorithm.Filter;
import Boost.TMP.Algorithm.FoldLeft;
import Boost.TMP.Algorithm.Product;
import Boost.TMP.Algorithm.RemovePairs;
import Boost.TMP.Algorithm.Sort;

import Boost.TMP.Sequence.Drop;
import Boost.TMP.Sequence.Index;
import Boost.TMP.Sequence.Join;
import Boost.TMP.Sequence.PushFront;
import Boost.TMP.Sequence.Tee;
import Boost.TMP.Sequence.Unpack;

export namespace boost::tmp {
		template<typename C = listify_>
		struct make_set_ {};

		template<typename C = listify_>
		struct empty_set {};

		template<typename C = listify_>
		struct cardinality_ {};

		// Get all of the elements that are in both passed in lists (sets).
		template<typename C = listify_>
		struct set_union_ {};

		// Get only the elements common to both passed in lists (sets).
		template<typename C = listify_>
		struct set_intersection_ {};

		// Get all of the elements that are unique to both lists (sets).
		template<typename C = listify_>
		struct set_symmetric_difference_ {};

		template<typename C = listify_>
		struct set_difference_A_ {};

		template<typename C = listify_>
		struct set_difference_B_ {};

		template<typename F, typename C = listify_>
		struct subset_ {};

		template<typename C = listify_>
		struct power_set_ {};

		template<typename C = listify_>
		struct set_numer_ {};

		template<typename C = listify_>
		struct set_denom_ {};

		template<typename C = listify_>
		struct set_quotient_ {};

		namespace detail {
			template <typename T>
			struct unique_magic_type;

			// Our starting point; gets dropped off at the end.
			struct unique_super_base {
				static constexpr bool contains(void *) {
					return false;
				}
			};

			template <typename Tail, typename T>
			struct unique_base : Tail {
				static constexpr bool contains(unique_magic_type<T> *) {
					return true;
				}

				using Tail::contains;
			};

			template <typename T, typename U>
			using is_in_set = bool_<T::contains(static_cast<detail::unique_magic_type<U> *>(0))>;

			using unique_push_if = if_<lift_<is_in_set>, front_<>, lift_<detail::unique_base>>;

			template <typename T, typename U>
			using less = bool_<(T::value < U::value)>;

			// TODO: Make sorting optional.
			template<unsigned N, typename C>
			struct dispatch<N, make_set_<C>> :
				dispatch<N, push_front_<detail::unique_super_base,
						fold_left_<detail::unique_push_if,
							flatten_<
								drop_<uint_<1>,
									sort_<lift_<less>, C
									>
								>
							>
						>
					>
				> {};
			
			template <typename T, typename U>
			using is_equal = call_<is_<T>, U>;

			template <typename T>
			using is_equal_pair = call_<unpack_<lift_<is_equal>>, T>;

			template<typename T, typename U>
			using productize = call_<product_<>, T, U>;

			template<unsigned N, typename C>
			struct dispatch<N, set_union_<C>> {
				template<typename T, typename U>
				using f =
				call_<
					join_<
						make_set_<C>
					>, T, U
				>;
			};

			template<unsigned N, typename C>
			struct dispatch<N, set_intersection_<C>> {
				template<typename T, typename U>
				using f =
				call_<
					unpack_<
						filter_<lift_<is_equal_pair>,
							join_<make_set_<C>>
						>
					>,
					productize<T, U>
				>;
			};

			// Requires two sets be the input because
			// more than two unique values will not be handled correctly.
			template<unsigned N, typename C>
			struct dispatch<N, set_symmetric_difference_<C>> {
				template<typename T, typename U>
				using f =
				call_<
					join_<
						sort_<
							lift_<less>,
							remove_pairs_<C>
						>
					>,
					T, U
				>;
			};

			template<typename T, typename U>
			using diff_helper = call_<set_intersection_<>, T, U>;

			template<typename T, typename U>
			using diff_helper3 = call_<join_<>, diff_helper<T, U>, T, list_<>>;

			template<unsigned N, typename C>
			struct dispatch<N, set_difference_A_<C>> {
				template<typename T, typename U>
				using f =
				call_<
					unpack_<
						sort_<
							lift_<less>,
							remove_pairs_<C>
						>
					>,
					diff_helper3<T, U>
				>;
			};
			
			template<unsigned N, typename C>
			struct dispatch<N, set_difference_B_<C>> {
				template<typename T, typename U>
				using f =
				call_<
					unpack_<
						sort_<
							lift_<less>,
							remove_pairs_<C>
						>
					>,
					diff_helper3<U, T>
				>;
			};

			template<typename T, typename U>
			using comp_join = call_<join_<>, T, U>;

			template<unsigned N, typename C>
			struct dispatch<N, set_quotient_<C>> {
				template<typename T, typename U>
				using f =
				call_<
				unpack_<
					tee_<
						tee_<
							i0_<>,
							i2_<>,
							join_<>
						>,
						tee_<
							i1_<>,
							i3_<>,
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

		} // namespace detail

		using make_set = push_front_<detail::unique_super_base, fold_left_<detail::unique_push_if>>;
} // export namespace boost::tmp
