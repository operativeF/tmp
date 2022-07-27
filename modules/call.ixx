//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#include <type_traits>
#endif // __GNUC__

export module Boost.TMP.Base.Call;

import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Vocabulary;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
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

	export template <typename F, typename... Ts>
	using call_ = typename dispatch<find_dispatch(sizeof...(Ts)),
		                                    F>::template f<Ts...>;

	export template <typename T, typename... Ts>
	using call_t = typename dispatch<find_dispatch(sizeof...(Ts)),
		                                        T>::template f<Ts...>::type;

	export template <typename T, typename... Ts>
	constexpr auto call_v =
		    dispatch<find_dispatch(sizeof...(Ts)), T>::template f<Ts...>::value;

	export template <typename C = identity_>
	struct call_f_ {};

	template <std::size_t N, typename C>
	struct dispatch<N, call_f_<C>> {
		template <typename F, typename... Ts>
		using f = typename dispatch<1, C>::template f<typename dispatch<
				find_dispatch(sizeof...(Ts)), F>::template f<Ts...>>;
	};

	export template <typename T, typename... Ts>
	using maybe_ =
		    maybe_impl<typename dispatch<find_dispatch(sizeof...(Ts)),
		                                               T>::template f<Ts...>>;

	export template <typename T, typename... Ts>
	using maybe_t =
		    maybe_impl<typename dispatch<find_dispatch(sizeof...(Ts)),
		                                               T>::template f<Ts...>::type>;

	export template <typename T, typename... Ts>
	constexpr auto maybe_v =
		    maybe_impl<typename dispatch<find_dispatch(sizeof...(Ts)),
		                                               T>::template f<Ts...>>::value;
} // namespace boost::tmp
