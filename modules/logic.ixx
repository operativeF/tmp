//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Base.Logic;

import Boost.TMP.Algorithm.FindIf;

import Boost.TMP.Base.Call;
import Boost.TMP.Base.Comparison;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;

import Boost.TMP.Detail.Dispatch;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <typename C = identity_>
	struct not_ {};
	
	export template <typename F = identity_, typename C = identity_>
	struct or_ {};
	
	export template <typename F = identity_, typename C = identity_>
	struct and_ {};

	template <typename C>
	struct dispatch<1, not_<C>> {
		template <typename T>
		using f = typename dispatch<1, C>::template f<bool_<(!T::value)>>;
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
		using f = typename dispatch<1, C>::template f<
				call_<is_<nothing_>, typename foldey<(select_foldey_loop(sizeof...(
												Ts)))>::template f<andy<false, F>, 0, Ts...>>>;
	};
	template <template <typename...> class F, typename C>
	struct dispatch<0, and_<lift_<F>, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<bool_<false>>;
	};
	template <std::size_t N, typename F, typename C>
	struct dispatch<N, and_<F, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<
				call_<is_<nothing_>,
						typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
								andy<false, dispatch<1, F>::template f>, 0, Ts...>>>;
	};
	template <typename F, typename C>
	struct dispatch<0, and_<F, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<bool_<false>>;
	};

	template <std::size_t N, template <typename...> class F, typename C>
	struct dispatch<N, or_<lift_<F>, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<
				call_<is_<nothing_, not_<identity_>>,
						typename foldey<(select_foldey_loop(
								sizeof...(Ts)))>::template f<ory<false, F>, 0, Ts...>>>;
	};
	template <template <typename...> class F, typename C>
	struct dispatch<0, or_<lift_<F>, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<bool_<false>>;
	};
	template <std::size_t N, typename F, typename C>
	struct dispatch<N, or_<F, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<
				call_<is_<nothing_, not_<identity_>>,
						typename foldey<(select_foldey_loop(sizeof...(Ts)))>::template f<
								ory<false, dispatch<1, F>::template f>, 0, Ts...>>>;
	};
	template <typename F, typename C>
	struct dispatch<0, or_<F, C>> {
		template <typename... Ts>
		using f = typename dispatch<1, C>::template f<bool_<false>>;
	};
} // namespace boost::tmp
