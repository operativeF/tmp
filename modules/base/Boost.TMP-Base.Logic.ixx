//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#if defined(__GNUC__) || defined(__clang__)
#include <cstdint>
#endif // defined(__GNUC__ ) || defined(__clang__)

export module Boost.TMP:Base.Logic;

import :Base.Call;
import :Base.Comparison;
import :Base.Foldey;
import :Base.Identity;
import :Base.Lift;
import :Base.Vocabulary;

import :Detail.Dispatch;

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
