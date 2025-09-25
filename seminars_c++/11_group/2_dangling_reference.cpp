#include <iostream>

int& bad(int x) {
    int copy = x;
    // attempt to return a reference
    // to local variable
    return copy;
}


int main() {

    // bad(10) --- dangling referece
    int b = bad(10); // segfault

    return 0;
}
