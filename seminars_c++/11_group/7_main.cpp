#include <iostream>
#include "7_string.h"



int main() {
    String str('a', 10);
    String str1 = str; // copy ctor!

    String str2('1', 4);
    str2 = str; // str2.operator=(str)


    return 0;
}