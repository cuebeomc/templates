#include <iostream>

#include "quicksort.hh"

int main() {
    using test1 =
            qs::quicksort<qs::list<20, 19, 21, 18, 22, 17, 23, 16, 24, 15, 26, 14, 27, 13, 28, 12,
                                   29, 11, 30, 10, 31, 9, 32, 8, 33, 7, 34, 6, 35, 5, 36, 4, 37, 3, 38, 2, 39, 1, 40>>;

    qs::list_printer<test1::type>::print();
}
