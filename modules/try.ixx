//  Copyright 2018 Odin Holmes.
//            2021-2022 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#endif // __GNUC__

export module Boost.TMP.Base.Try;

import Boost.TMP.Base.Always;
import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Sequence.Unpack;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

namespace boost::tmp {
	export template <template <typename...> class F, typename C = identity_>
	struct try_ {};

	namespace detail {
		template <typename T>
		struct t_ {
			using type = T;
		};
		template <template <typename...> class F, typename... Ts>
		t_<F<Ts...>> try_f(lift_<F>, list_<Ts...>);
		t_<nothing_> try_f(...);

		template <std::size_t N, template <typename...> class F, typename C>
		struct dispatch<N, try_<F, C>> {
			template <typename... Ts>
			using f = typename dispatch<1, C>::template f<typename decltype(
				    try_f(lift_<F>{}, list_<Ts...>{}))::type>;
		};
	} // namespace detail
} // namespace boost::tmp