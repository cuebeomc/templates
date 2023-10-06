#include <iostream>

#include "ct/ct.hh"

int main() {
    using best_case_list = ct::list<32, 16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 14, 18, 22, 26, 30, 1,
                                    3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 48,
                                    40, 56, 36, 44, 52, 60, 34, 38, 42, 46, 50, 54, 58, 62, 33,
                                    35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63>;
    using test1 = ct::quicksort<best_case_list>;
    ct::list_printer<test1::type>::print();
}
