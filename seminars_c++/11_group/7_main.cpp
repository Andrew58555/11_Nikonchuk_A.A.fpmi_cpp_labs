#include <iostream>
#include "7_string.h"



int main() {
    String str('a', 10);
    String str1 = str; // copy ctor!

    String str2('1', 4);
    str2 = str; // str2.operator=(str)

    String test{'h', 'e', 'l', 'l', 'o'};

    std::cout << "operator[]: " << test[2] << '\n';
    test[2] = 'b';

    std::cout << "operator<<: " << test << '\n';

    return 0;
}
