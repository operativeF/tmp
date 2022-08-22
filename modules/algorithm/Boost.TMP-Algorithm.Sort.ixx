//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Sort;

import :Algorithm.Fold;
import :Algorithm.Logic;
import :Algorithm.PushPop;
import :Algorithm.Unpack;
import :Base.Types;

#if _MSC_VER
import std;
#endif

// NOTE: Sort only works on lists, not parameter packs.
namespace boost::tmp {
// sort_ :
export template <typename F = less_<>, typename C = listify_>
struct sort_ {};

// sort_ : implementation
namespace impl {

namespace btree {
    // The binary tree as a list.
    template <typename... Ts>
    struct blist {};

    // A node in the binary tree, connecting to other nodes (L)eft and (R)ight, and (E)dge
    template <typename L, typename E, typename R>
    struct bnode {};
    template <typename T>
    struct bun;
    template <bool, template <typename...> class F>
    struct bpush;
    template <template <typename...> class F>
    struct bpush<false, F> {
        template <typename T, typename L, typename E, typename R>
        using n = bnode<L, E, typename bun<R>::template f<F, T>>;
        template<typename T, typename LL, typename LE, typename LR,
                    typename E, typename RL, typename RE, typename RR>
        using nn = bpush<F<T, RE>::value, F>::template nn_0<T, LL, LE, LR, E, RL, RE, RR>;
        template <typename T, typename LL, typename LE, typename LR, typename E,
                    typename RL, typename RE, typename RR>
        using nn_0 = bnode<bnode<bnode<LL, LE, LR>, E, RL>, RE,
                            typename bun<RR>::template f<F, T>>;
        template <typename T, typename LL, typename LE, typename LR,
                    typename E, typename RL, typename RE, typename RR>
        using nn_1 = bnode<bnode<LL, LE, typename bun<LR>::template f<F, T>>, E,
                            bnode<RL, RE, RR>>;
        template <typename T, typename E>
        using l1 = blist<E, T>;
        template <typename T, typename E0, typename E1>
        using l2_0 = bpush<F<T, E1>::value, F>::template l2_1<T, E0, E1>;
        template <typename T, typename E0, typename E1>
        using l2_1 = bnode<blist<E0>, E1, blist<T>>;
    };
    template <template <typename...> class F>
    struct bpush<true, F> {
        template <typename T, typename L, typename E, typename R>
        using n = bnode<typename bun<L>::template f<F, T>, E, R>;
        template <typename T, typename LL, typename LE, typename LR,
                    typename E, typename RL, typename RE, typename RR>
        using nn = bpush<F<T, LE>::value, F>::template nn_1<T, LL, LE, LR, E, RL, RE, RR>;
        template <typename T, typename LL, typename LE, typename LR,
                    typename E, typename RL, typename RE, typename RR>
        using nn_0 = bnode<bnode<LL, LE, LR>, E,
                            bnode<typename bun<RL>::template f<F, T>, RE, RR>>;
        template <typename T, typename LL, typename LE, typename LR,
                    typename E, typename RL, typename RE, typename RR>
        using nn_1 = bnode<typename bun<LL>::template f<F, T>, LE,
                            bnode<LR, E, bnode<RL, RE, RR>>>;
        template <typename T, typename E>
        using l1 = blist<T, E>;
        template <typename T, typename E0, typename E1>
        using l2_0 = bnode<blist<T>, E0, blist<E1>>;
        template <typename T, typename E0, typename E1>
        using l2_1 = bnode<blist<E0>, T, blist<E1>>;
    };

    template <>
    struct bun<blist<>> {
        template <template <typename...> class F, typename T>
        using f = blist<T>;
    };
    template <typename E>
    struct bun<blist<E>> {
        template <template <typename...> class F, typename T>
        using f = bpush<F<T, E>::value, F>::template l1<T, E>;
    };
    template <typename E0, typename E1>
    struct bun<blist<E0, E1>> {
        template <template <typename...> class F, typename T>
        using f = bpush<F<T, E0>::value, F>::template l2_0<T, E0, E1>;
    };

    // Push a node. The node postion (either Left or Right) from the Edge
    // is determined by the type bpush<F<T, E>::value, F>::template
    // and will dispatch the correct node position by calling each
    // version's respective n<T, L, E, R> function.
    template <typename L, typename E, typename R>
    struct bun<bnode<L, E, R>> {
        template <template <typename...> class F, typename T>
        using f = bpush<F<T, E>::value, F>::template n<T, L, E, R>;
    };
    template <typename LL, typename LE, typename LR, typename E, typename RL,
                typename RE, typename RR>
    struct bun<bnode<bnode<LL, LE, LR>, E, bnode<RL, RE, RR>>> {
        template <template <typename...> class F, typename T>
        using f = bpush<F<T, E>::value, F>::template nn<T, LL, LE, LR, E, RL,
                                                                    RE, RR>;
    };

    template <typename LLL, typename LLE, typename LLR, typename LE, typename LR,
                typename E, typename... Ts>
    struct bun<bnode<bnode<bnode<LLL, LLE, LLR>, LE, LR>, E, blist<Ts...>>> {
        template <template <typename...> class F, typename T>
        using f = bpush<F<T, LE>::value, F>::template nn<T, LLL, LLE, LLR, LE,
                                                                    LR, E, blist<Ts...>>;
    };

    template <typename... Ts, typename E, typename RL, typename RE, typename RRL,
                typename RRE, typename RRR>
    struct bun<bnode<blist<Ts...>, E, bnode<RL, RE, bnode<RRL, RRE, RRR>>>> {
        template <template <typename...> class F, typename T>
        using f = bpush<F<T, RE>::value, F>::template nn<T, blist<Ts...>, E, RL,
                                                            RE, RRL, RRE, RRR>;
    };

    // Prune branch

    // Remove leaf

    // Remove 

    template <typename LL, typename LE, typename LR, typename E, typename RL,
                typename RE, typename RR>
    struct join7;

    template <typename... LL, typename LE, typename... LR, typename E, typename... RL,
                typename RE, typename... RR>
    struct join7<blist<LL...>, LE, blist<LR...>, E, blist<RL...>, RE, blist<RR...>> {
        using type = blist<LL..., LE, LR..., E, RL..., RE, RR...>;
    };

    // Binary tree flattener metaclosures
    template <typename T>
    struct bflat;

    // Flatten single end node with Left, Edge, and Right
    template <typename L, typename E, typename R>
    struct bflat<bnode<L, E, R>> {
        using type = bflat<bnode<typename bflat<L>::type, E, typename bflat<R>::type>>::type;
    };

    // Flatten two nodes, Left and Right from Edge, and flatten their respective Left
    // and Right nodes with their Edges. Join the seven resulting types into
    // a blist, respecting their order.
    template <typename LL, typename LE, typename LR, typename E, typename RL,
                typename RE, typename RR>
    struct bflat<bnode<bnode<LL, LE, LR>, E, bnode<RL, RE, RR>>> {
        using type = join7<typename bflat<LL>::type, LE, typename bflat<LR>::type,
                                E, 
                                typename bflat<RL>::type, RE, typename bflat<RR>::type
                            >::type;
    };

    // From a node, combine the Left and Right chlidren 
    // into a single blist.
    template <typename... L, typename E, typename... R>
    struct bflat<bnode<blist<L...>, E, blist<R...>>> {
        using type = blist<L..., E, R...>;
    };

    // Final combination of all the resulting types.
    template <typename... T>
    struct bflat<blist<T...>> {
        using type = blist<T...>;
    };

    template <typename T>
    using collapse_t = btree::bflat<T>::type;
} // namespace btree

// Push elements to btree
template <typename F>
struct element_pusher {};
template <typename F>
struct dispatch<2, element_pusher<F>> {
    template <typename T, typename U>
    using f = btree::bun<T>::template f<dispatch<2, F>::template f, U>;
};
template <template <typename...> class F>
struct dispatch<2, element_pusher<lift_<F>>> {
    template <typename T, typename U>
    using f = btree::bun<T>::template f<F, U>;
};
template <template <typename...> class F>
struct pusher {
    template <typename T, typename U>
    using f = btree::bun<T>::template f<F, U>;
};
template <template <typename...> class F, typename C = identity_,
            typename Initial = btree::blist<>>
using make_binary_tree =
        push_front_<Initial, fold_left_<lift_<pusher<F>::template f>, C>>;
template <typename C>
using collapse_unpack = lift_<btree::collapse_t, unpack_<C>>;
template <std::size_t N, template <typename...> class F, typename C>
struct dispatch<N, sort_<lift_<F>, C>>
    : dispatch<N, make_binary_tree<F, collapse_unpack<C>, btree::blist<>>> {};
template <std::size_t N, typename F, typename C>
struct dispatch<N, sort_<F, C>>
    : dispatch<N, make_binary_tree<dispatch<2, F>::template f, collapse_unpack<C>,
                                    btree::blist<>>> {};

} // namespace impl

#ifdef TMP_COMPILE_TIME_TESTING
namespace test {

template<typename T> requires(std::same_as<T, list_<sizet_<0>, sizet_<1>, sizet_<2>>>)
struct ListZeroOneTwo;

template <typename T, typename U>
using less = bool_<(T::value < U::value)>;

using sort_test_1 = ListZeroOneTwo<call_<sort_<lift_<less>>, sizet_<1>, sizet_<0>, sizet_<2>>>;

} // namespace test
#endif // TMP_COMPILE_TIME_TESTING

} // namespace boost::tmp
