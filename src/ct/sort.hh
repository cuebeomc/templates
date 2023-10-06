#pragma once

#include "list.hh"

namespace ct {

/// Comparison struct (<)
template<int V1, int V2>
struct lt {
    static constexpr bool value = V1 < V2;
};

/// Performs a split upon given element.
template<int V, typename L, typename L1, typename L2>
struct split;

/// Quicksorts given list.
template<typename L>
struct quicksort;

/// When nil, we quicksort left and right halves, and stick our pivot P in the middle.
template<int P, int... V1s, int... V2s>
struct split<P, nil, list<V1s...>, list<V2s...>>
    : concat<typename quicksort<list<V1s...>>::type,
             typename cons<P, typename quicksort<list<V2s...>>::type>::type> {};

/// We define a geq/lt specialization for split based on
/// the comparison of the first element in the list to our pivot.
template<int P, typename L, typename L1, typename L2, bool IsLt>
struct split_recursive;

template<int P, int V, int... Vs, int... V1s, int... V2s>
struct split_recursive<P, list<V, Vs...>, list<V1s...>, list<V2s...>, true>
    : split<P, list<Vs...>, list<V, V1s...>, list<V2s...>> {};

template<int P, int V, int... Vs, int... V1s, int... V2s>
struct split_recursive<P, list<V, Vs...>, list<V1s...>, list<V2s...>, false>
    : split<P, list<Vs...>, list<V1s...>, list<V, V2s...>> {};

template<int P, int V, int... Vs, int... V1s, int... V2s>
struct split<P, list<V, Vs...>, list<V1s...>, list<V2s...>>
    : split_recursive<P, list<V, Vs...>, list<V1s...>, list<V2s...>, lt<V, P>::value> {};

/// Finally, the quicksort specializations.
template<>
struct quicksort<nil> : nil {};

template<int V, int... Vs>
struct quicksort<list<V, Vs...>> : split<V, list<Vs...>, nil, nil> {};

} // namepace ct::list::utils
