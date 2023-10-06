#pragma once

#include <iostream>

namespace ct {

/// Defines a compile-time list type.
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

/// Represents concat (as1 @ as2 of 'a list * 'a list)
template<typename L1, typename L2>
struct concat;

template<int... Vs>
struct concat<nil, list<Vs...>> : list<Vs...> {};

template<int V, int... V1s, int... V2s>
struct concat<list<V, V1s...>, list<V2s...>>
    : cons<V, typename concat<list<V1s...>, list<V2s...>>::type> {};

/// A struct to print lists.
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

} // namespace ct
