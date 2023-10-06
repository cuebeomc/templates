#include <iostream>

namespace qs {

/// List type.
template<int... Vs>
struct list {
    using type = list;
};
using nil = list<>;

/// Represents cons (a :: as of 'a * 'a list)
template<int V, typename L>
struct cons;

template<int V, int... Vs>
struct cons<V, list<Vs...>> : list<V, Vs...> {};

template<typename T>
struct list_printer_impl;

template<>
struct list_printer_impl<nil> {
    static void print() {
        std::cout << "()";
    }
};

template<int V, int... Vs>
struct list_printer_impl<list<V, Vs...>> {
    static void print() {
        std::cout << V << ", ";
        list_printer_impl<list<Vs...>>::print();
    }
};

template<typename T>
struct list_printer;

template<int... Vs>
struct list_printer<list<Vs...>> {
    static void print() {
        std::cout << "(";
        list_printer_impl<list<Vs...>>::print();
        std::cout << ")" << std::endl;
    }
};

/// Represents concat (as1 @ as2 of 'a list * 'a list)
template<typename L1, typename L2>
struct concat;

template<int... Vs>
struct concat<nil, list<Vs...>> : list<Vs...> {};

template<int V, int... V1s, int... V2s>
struct concat<list<V, V1s...>, list<V2s...>>
    : cons<V, typename concat<list<V1s...>, list<V2s...>>::type> {};

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

/// When nil, we quicksort left and right halves, and stick V in the middle.
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

}  // namespace qs
