//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <concepts>
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Algorithm.Logic;

import :Base.Foldey;
import :Base.Types;

import :TestHelpers;

#if _MSC_VER
import std;
#endif

namespace boost::tmp {
    export template <typename C = identity_>
    struct not_ {};
    
    export template <typename F = identity_, typename C = identity_>
    struct or_ {};
    
    export template <typename F = identity_, typename C = identity_>
    struct and_ {};

    // Given a predicate P, if true, return T, and if false, return F.
    export template <typename P, typename T, typename F = always_<nothing_>>
    struct if_ {};

    export template <typename P, typename C = identity_>
    struct is_ {};

    template <typename P, typename C>
    struct dispatch<1, is_<P, C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<bool_<std::is_same_v<P, T>>>;
    };
    
    export template <typename V = nothing_, typename C = identity_>
    struct less_ {};

    export template <typename F, typename C = identity_>
    struct less_f_ {};

    export template <typename V = nothing_, typename C = identity_>
    struct less_eq_ {};

    export template <typename V = nothing_, typename C = identity_>
    struct greater_ {};

    export template <typename LV = nothing_, typename UV = nothing_, typename C = identity_>
    struct range_lo_hi_ {};

    // Given a unary predicate, return true_ / false_ on whether all elements
    // in a VPP satisfy that predicate.
    export template <typename F, typename C = identity_>
    struct all_of_ {};

    // Given a unary predicate, return true_ / false_ on whether any elements
    // in a VPP satisfy that predicate.
    export template <typename F = identity_, typename C = identity_>
    struct any_of_ {};

    // Given a predicate (F), return true_ / false_ if none
    // of the elements in a VPP satisfy the predicate F.
    export template <typename F, typename C = identity_>
    struct none_of_ {};

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, none_of_<F, C>> : dispatch<N, and_<F, not_<C>>> {};

    // Given a type (V), return true_ / false_ on whether a given VPP
    // contains the type V.
    export template <typename T, typename C = identity_>
    struct contains_ {};

    template <std::size_t N, typename T, typename C>
    struct dispatch<N, contains_<T, C>> : dispatch<N, or_<is_<T>, C>> {};

    template <typename C>
    struct dispatch<1, not_<C>> {
        template <typename T>
        using f = dispatch<1, C>::template f<bool_<(!T::value)>>;
    };

    template <bool Short, template <typename...> class F>
    struct andy {
        template <typename T>
        using f                    = andy<(!F<T>::value), F>;
        static constexpr std::size_t value = -1;
    };
    template <template <typename...> class F>
    struct andy<true, F> {
        template <typename T>
        using f                    = andy;
        static constexpr std::size_t value = 1;
    };
    template <bool Short, template <typename...> class F>
    struct ory {
        template <typename T>
        using f                    = ory<F<T>::value, F>;
        static constexpr std::size_t value = -1;
    };
    template <template <typename...> class F>
    struct ory<true, F> {
        template <typename T>
        using f                    = ory;
        static constexpr std::size_t value = 1;
    };

    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, and_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_>, typename foldey<(select_foldey_loop(sizeof...(
                                                Ts)))>::template f<andy<false, F>, 0, Ts...>>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<0, and_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, and_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_>,
                        typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
                                andy<false, dispatch<1, F>::template f>, 0, Ts...>>>;
    };
    template <typename F, typename C>
    struct dispatch<0, and_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };

    template <std::size_t N, template <typename...> class F, typename C>
    struct dispatch<N, or_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_, not_<identity_>>,
                        typename foldey<(select_foldey_loop(
                                sizeof...(Ts)))>::template f<ory<false, F>, 0, Ts...>>>;
    };
    template <template <typename...> class F, typename C>
    struct dispatch<0, or_<lift_<F>, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };
    template <std::size_t N, typename F, typename C>
    struct dispatch<N, or_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<
                call_<is_<nothing_, not_<identity_>>,
                        typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
                                ory<false, dispatch<1, F>::template f>, 0, Ts...>>>;
    };
    template <typename F, typename C>
    struct dispatch<0, or_<F, C>> {
        template <typename... Ts>
        using f = dispatch<1, C>::template f<false_>;
    };

    template <bool B>
    struct if_impl;

    template <>
    struct if_impl<true> {
        template <typename T, typename U>
        using f = T;
    };

    template <>
    struct if_impl<false> {
        template <typename T, typename U>
        using f = U;
    };

    template <typename P, typename T, typename F>
    struct dispatch<1, if_<P, T, F>> {
        template <typename T0>
        using f = dispatch<1, typename if_impl<dispatch<1, P>::template
                      f<T0>::value>::template
                          f<T, F>>::template
                              f<T0>;
    };

    template <template <typename...> class P, typename T, typename F>
    struct dispatch<1, if_<lift_<P>, T, F>> {
        template <typename T0>
        using f = dispatch<1, typename if_impl<P<T0>::value>::template
                      f<T, F>>::template
                          f<T0>;
    };

    template <std::size_t N, typename P, typename T, typename F>
    struct dispatch<N, if_<P, T, F>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)),
                      typename if_impl<dispatch<find_dispatch(sizeof...(Ts)), P>::template
                          f<Ts...>::value>::template f<T, F>>::template f<Ts...>;
    };
    template <std::size_t N, template <typename...> class P, typename T, typename F>
    struct dispatch<N, if_<lift_<P>, T, F>> {
        template <typename... Ts>
        using f = dispatch<find_dispatch(sizeof...(Ts)),
                      typename if_impl<P<Ts...>::value>::template
                          f<T, F>>::template f<Ts...>;
    };
    template <template <typename...> class P, typename T, typename F>
    struct dispatch<2, if_<lift_<P>, T, F>> {
        template <typename T0, typename T1>
        using f = dispatch<2, typename if_impl<P<T0,T1>::value>::template
                      f<T, F>>::template f<T0, T1>;
    };
    template <template <typename...> class P>
    struct dispatch<1, if_<lift_<P>, listify_, always_<list_<>>>> {
        template <typename U>
        using f = if_impl<P<U>::value>::template f<list_<U>, list_<>>;
    };

    // NOTE: Internal compiler error occurs when no parentheses are used around the values.
    // Error is C1001; compiler file msc1.cpp, line 1596
    template <typename C>
    struct dispatch<2, less_<C>> {
        template <typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
    };

    template <typename U, typename C>
    struct dispatch<1, less_<U, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
    };

    template <template<typename...> typename F, typename C>
    struct dispatch<2, less_f_<lift_<F>, C>> {
        template<typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(F<T>::value < F<U>::value)>>;
    };

    template <typename Lower, typename Upper, typename C>
    struct dispatch<1, range_lo_hi_<Lower, Upper, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<!((Lower::value < T::value) && (T::value < Upper::value))>>;
    };

    template <typename C>
    struct dispatch<2, less_eq_<C>> {
        template <typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(T::value)<=(U::value)>>;
    };

    template <typename U, typename C>
    struct dispatch<1, less_eq_<U, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<(U::value)<=(T::value)>>;
    };

    template <typename C>
    struct dispatch<2, greater_<C>> {
        template <typename T, typename U>
        using f = dispatch<1, C>::template f<bool_<(U::value)<(T::value)>>;
    };

    template <typename U, typename C>
    struct dispatch<1, greater_<U, C>> {
        template<typename T>
        using f = dispatch<1, C>::template f<bool_<(T::value)<(U::value)>>;
    };

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, all_of_<F, C>> : dispatch<N, and_<F, C>> {};

    template <std::size_t N, typename F, typename C>
    struct dispatch<N, any_of_<F, C>> : dispatch<N, or_<F, C>> {};
} // namespace boost::tmp

namespace logic_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, false_>)
    struct AllNumbersOdd;

    template<typename T> requires(std::same_as<T, true_>)
    struct AllNumbersEven;

    template<typename T> requires(std::same_as<T, true_>)
    struct OneNumberEven;

    template<typename T> requires(std::same_as<T, true_>)
    struct OneNumberOdd;

    using test_one = AllNumbersOdd<call_<and_<lift_<utils::is_even>>, int_<1>, int_<1>, int_<1>>>;

    using test_two = AllNumbersEven<call_<and_<lift_<utils::is_even>>, int_<2>, int_<2>, int_<2>>>;

    using test_three = OneNumberEven<call_<or_<lift_<utils::is_even>>, int_<1>, int_<2>, int_<1>>>;

    using test_four = OneNumberOdd<call_<or_<lift_<utils::is_even>>, int_<2>, int_<1>, int_<2>>>;

} // namespace logic_test

// TODO: Move into logic_test
namespace contains_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, false_>)
    struct DoesNotContainType;

    template<typename T> requires(std::same_as<T, true_>)
    struct ContainsType;

    using test_one   = DoesNotContainType<call_<contains_<int_<0>>, int_<1>>>;

    using test_two   = ContainsType<call_<contains_<int_<2>>, int_<0>, int_<1>, int_<2>>>;

    using test_three = DoesNotContainType<call_<contains_<int_<1>>>>;
    
} // namespace contains_test

// TODO: Move into logic_test
namespace comparison_test {
    using namespace boost::tmp;

    // template<int A, int B>
    // struct two_ints {
    //     int a{A};
    //     int b{B};
    // };

    // false_{} = call_<less_f_<lift_<std::alignment_of>>, two_ints<1, 2>, char_<'c'>>{};
    // true_{}  = call_<less_f_<lift_<std::alignment_of>>, char_<'c'>,     two_ints<1, 2>>{};
} // namespace comparison_test

// TODO: Move into logic_test
namespace none_of_test {
    using namespace boost::tmp;

    template<typename T> requires(std::same_as<T, false_>)
    struct NoneOfTheNumbersAreOdd;

    template<typename T> requires(std::same_as<T, true_>)
    struct NoneOfTheNumbersAreEven;

    // Conversely, all of the numbers are even.
    using test_one = NoneOfTheNumbersAreOdd<call_<none_of_<lift_<utils::is_even>>, int_<2>, int_<100>, int_<4>, int_<500>>>;

    // Conversely, all of the numbers are odd.
    using test_two = NoneOfTheNumbersAreEven<call_<none_of_<lift_<utils::is_even>>, int_<1>, int_<3>>>;
} // namespace none_of_test
