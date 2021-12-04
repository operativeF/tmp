//  Copyright 2018 Odin Holmes.
//            2021 Thomas Figueroa.
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

export module Boost.TMP.Base.Try;

import Boost.TMP.Base.Always;
import Boost.TMP.Detail.Dispatch;
import Boost.TMP.Base.Identity;
import Boost.TMP.Base.Lift;
import Boost.TMP.Base.Vocabulary;
import Boost.TMP.Sequence.Unpack;

export namespace boost::tmp {
		template <template <typename...> class F, typename C = identity_>
		struct try_ {};

		namespace detail {
			template <typename T>
			struct t_ {
				using type = T;
			};
			template <template <typename...> class F, typename... Ts>
			t_<F<Ts...>> try_f(lift_<F>, list_<Ts...>);
			t_<nothing_> try_f(...);

			template <unsigned N, template <typename...> class F, typename C>
			struct dispatch<N, try_<F, C>> {
				template <typename... Ts>
				using f = typename dispatch<1, C>::template f<typename decltype(
				        try_f(lift_<F>{}, list_<Ts...>{}))::type>;
			};
		} // namespace detail
} // export namespace boost::tmp
