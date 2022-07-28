//  Copyright 2021 Thomas Figueroa.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

module;

#ifdef __GNUC__
#include <cstdint>
#include <type_traits>
#endif // __GNUC__

export module Boost.TMP:Base.Decay;

#if __clang__
import std;
#elif _MSC_VER
import std;
#endif

export namespace boost::tmp {
	template <typename T, typename U = typename std::remove_reference_t<T>>
	struct decay {
		using type = std::remove_cv_t<U>;
	};

	template <typename T, typename U>
	struct decay<T, U[]> {
		using type = U*;
	};
	template <typename T, typename U, std::size_t N>
	struct decay<T, U[N]> {
		using type = U*;
	};

	template <typename T, typename R, typename... A>
	struct decay<T, R(A...)> {
		using type = R(*)(A...);
	};
	template <typename T, typename R, typename... A>
	struct decay<T, R(A..., ...)> {
		using type = R(*)(A..., ...);
	};
} // export namespace boost::tmp
