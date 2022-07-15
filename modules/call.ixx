//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Base.Call;

import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Vocabulary;

#ifdef __GNUC__
import <cstdint>;
import <type_traits>;
#elif __clang__
import std;
#elif _MSC_VER
import std.core;
#endif

namespace boost::tmp {
	namespace detail {
		template <bool B>
		struct maybe_test_impl {
			template <typename T>
			using f = T;
		};
		template <>
		struct maybe_test_impl<true> {};

		template <typename T>
		using maybe_impl =
			    typename maybe_test_impl<std::is_same_v<T, nothing_>>::template f<T>;

		template <typename F, typename... Ts> // workaround for old clang
		struct call_impl {
			using type = typename dispatch<find_dispatch(sizeof...(Ts)), F>::template f<Ts...>;
		};
	} // namespace detail

	export template <typename F, typename... Ts>
	using call_ = typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                    F>::template f<Ts...>;

	export template <typename T, typename... Ts>
	using call_t = typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                        T>::template f<Ts...>::type;

	export template <typename T, typename... Ts>
	constexpr auto call_v =
		    detail::dispatch<detail::find_dispatch(sizeof...(Ts)), T>::template f<Ts...>::value;

	export template <typename C = identity_>
	struct call_f_ {};

	namespace detail {
		template <std::size_t N, typename C>
		struct dispatch<N, call_f_<C>> {
			template <typename F, typename... Ts>
			using f = typename dispatch<1, C>::template f<typename dispatch<
				    detail::find_dispatch(sizeof...(Ts)), F>::template f<Ts...>>;
		};
	} // namespace detail

	export template <typename T, typename... Ts>
	using maybe_ =
		    detail::maybe_impl<typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                                    T>::template f<Ts...>>;

	export template <typename T, typename... Ts>
	using maybe_t =
		    detail::maybe_impl<typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                                    T>::template f<Ts...>::type>;

	export template <typename T, typename... Ts>
	constexpr auto maybe_v =
		    detail::maybe_impl<typename detail::dispatch<detail::find_dispatch(sizeof...(Ts)),
		                                                    T>::template f<Ts...>>::value;
} // namespace boost::tmp
