#ifndef BOOST_TMP_REPEAT_HPP_INCLUDED
#define BOOST_TMP_REPEAT_HPP_INCLUDED

//  Copyright 2019 Odin Holmes.
//                 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/tmp/call.hpp>
#include <boost/tmp/vocabulary.hpp>
#include <boost/tmp/detail/dispatch.hpp>


namespace boost {
	namespace tmp {
		template <typename F, unsigned N, typename C = identity_>
		struct repeat_ {};

		namespace detail {
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<0, repeat_<lift_<F>, 0, lift_<C>>> {
                template<typename T>
                using f = C<T>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<1, repeat_<lift_<F>, 1, lift_<C>>> {
                template<typename T>
                using f = C<F<T>>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<2, repeat_<lift_<F>, 2, lift_<C>>> {
                template<typename T>
                using f = C<F<F<T>>>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<3, repeat_<lift_<F>, 3, lift_<C>>> {
                template<typename T>
                using f = C<F<F<F<T>>>>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<4, repeat_<lift_<F>, 4, lift_<C>>> {
                template<typename T>
                using f = C<F<F<F<F<T>>>>>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<5, repeat_<lift_<F>, 5, lift_<C>>> {
                template<typename T>
                using f = C<F<F<F<F<F<T>>>>>>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<6, repeat_<lift_<F>, 6, lift_<C>>> {
                template<typename T>
                using f = C<F<F<F<F<F<F<T>>>>>>>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<7, repeat_<lift_<F>, 7, lift_<C>>> {
                template<typename T>
                using f = C<F<F<F<F<F<F<F<T>>>>>>>>;
            };
            template<template<typename...> typename F, template<typename...> typename C>
            struct dispatch<8, repeat_<lift_<F>, 8, lift_<C>>> {
                template<typename T>
                using f = C<F<F<F<F<F<F<F<F<T>>>>>>>>>;
            };
            template <unsigned N, typename F, typename C>
			struct dispatch<N, repeat_<F, N, C>>
			    : dispatch<N, repeat_<lift_<dispatch<2, F>::template f>, N,
			                              lift_<dispatch<1, C>::template f>>> {};
			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, repeat_<lift_<F>, N, C>>
			    : dispatch<N, repeat_<lift_<F>, N, lift_<dispatch<1, C>::template f>>> {};
			template <unsigned N, typename F, template <typename...> class C>
			struct dispatch<N, repeat_<F, N, lift_<C>>>
			    : dispatch<N, repeat_<lift_<dispatch<2, F>::template f>, N, lift_<C>>> {};
		} // namespace detail
	} // namespace tmp
} // namespace boost

#endif // BOOST_TMP_REPEAT_HPP_INCLUDED