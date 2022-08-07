//  Copyright 2018-2019 Odin Holmes.
//			  2020-2022 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Sequence.Set;

import :Algorithm.Flatten;
import :Algorithm.Filter;
import :Algorithm.FoldLeft;
import :Algorithm.Product;
import :Algorithm.RemovePairs;
import :Algorithm.Sort;
import :Base.Call;
import :Base.Comparison;
import :Base.If;
import :Base.Lift;
import :Base.ListOperations;
import :Base.Vocabulary;
import :Base.Dispatch;
import :Sequence.Drop;
import :Sequence.Index;
import :Sequence.Join;
import :Sequence.PushFront;
import :Sequence.Tee;
import :Sequence.Unpack;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template<typename C = listify_>
    struct make_set_ {};

    export template<typename C = listify_>
    struct empty_set {};

    export template<typename C = listify_>
    struct cardinality_ {};

    // Get all of the elements that are in both passed in lists (sets).
    export template<typename C = listify_>
    struct set_union_ {};

    // Get only the elements common to both passed in lists (sets).
    export template<typename C = listify_>
    struct set_intersection_ {};

    // Get all of the elements that are unique to both lists (sets).
    export template<typename C = listify_>
    struct set_symmetric_difference_ {};

    export template<typename C = listify_>
    struct set_difference_A_ {};

    export template<typename C = listify_>
    struct set_difference_B_ {};

    export template<typename F, typename C = listify_>
    struct subset_ {};

    export template<typename C = listify_>
    struct power_set_ {};

    export template<typename C = listify_>
    struct set_numer_ {};

    export template<typename C = listify_>
    struct set_denom_ {};

    export template<typename C = listify_>
    struct set_multiplier_ {};

    export template<typename C = listify_>
    struct set_divisor_ {};
        
    export template<typename C = listify_>
    struct set_quotient_ {};

    template <typename T>
    struct unique_magic_type;

    // Our starting point; gets dropped off at the end.
    struct unique_super_base {
        static consteval bool contains(void *) {
            return false;
        }
    };

    template <typename Tail, typename T>
    struct unique_base : Tail {
        static consteval bool contains(unique_magic_type<T> *) {
            return true;
        }

        using Tail::contains;
    };

    template <typename T, typename U>
    using is_in_set = bool_<T::contains(static_cast<unique_magic_type<U> *>(0))>;

    using unique_push_if = if_<lift_<is_in_set>, front_<>, lift_<unique_base>>;

    template <typename T, typename U>
    using less = bool_<(T::value < U::value)>;

    // TODO: Make sorting optional.
    template<std::size_t N, typename C>
    struct dispatch<N, make_set_<C>> :
        dispatch<N, push_front_<unique_super_base,
                fold_left_<unique_push_if,
                    flatten_<
                        drop_<sizet_<1>,
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

    template<std::size_t N, typename C>
    struct dispatch<N, set_union_<C>> {
        template<typename T, typename U>
        using f =
        call_<
            join_<
                make_set_<C>
            >, T, U
        >;
    };

    template<std::size_t N, typename C>
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
    template<std::size_t N, typename C>
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

    template<std::size_t N, typename C>
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
        
    template<std::size_t N, typename C>
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
    struct dispatch<N, set_multiplier_<C>> {
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
                lift_<full_divide_lists, C>
            >
        >, comp_join<T, U>
        >;
    };

    template<unsigned N, typename C>
    struct dispatch<N, set_divisor_<C>> {
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
                lift_<full_divide_lists, C>
            >
        >, comp_join<T, U>
        >;
    };

    template<std::size_t N, typename C>
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

    export using make_set = push_front_<unique_super_base, fold_left_<unique_push_if>>;
} // namespace boost::tmp

namespace set_test {
    using namespace boost::tmp;

    // TODO: Implement set_test

    // using aalist = list_<uint_<1>, uint_<2>, uint_<3>, uint_<9>, uint_<3>>;
    // using bblist = list_<uint_<2>, uint_<1>, uint_<7>, uint_<4>, uint_<3>>;
    // using cclist = list_<uint_<1>, uint_<2>, uint_<3>, uint_<9>, uint_<3>>;
    // using ddlist = list_<>;

    // using union_set = call_<set_union_<>, aalist, bblist>;

    // using intersect_set = call_<set_intersection_<>, aalist, bblist>;

    // using sym_set = call_<set_symmetric_difference_<>, aalist, bblist>;

    // using diff_a = call_<set_difference_A_<>, aalist, bblist>;

    // using diff_b = call_<set_difference_B_<>, aalist, bblist>;

    // using quotient = list_<diff_a, diff_b>;

    // using diff_c = call_<set_difference_A_<>, cclist, ddlist>;

    // using diff_d = call_<set_difference_B_<>, cclist, ddlist>;

    // using quotient_b = list_<diff_c, diff_d>;

    // quotient{} = list_<list_<uint_<3>, uint_<9>>, list_<uint_<4>, uint_<7>>>{};
    // sym_set{} = list_<uint_<3>, uint_<4>, uint_<7>, uint_<9>>{};
    // union_set{} = list_<uint_<1>, uint_<2>, uint_<3>, uint_<4>, uint_<7>, uint_<9>>{};
    // intersect_set{} = list_<uint_<1>, uint_<2>, uint_<3>>{};
} // namespace set_test
