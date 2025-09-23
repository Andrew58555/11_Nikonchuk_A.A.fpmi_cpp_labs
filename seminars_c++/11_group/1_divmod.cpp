#include <iostream>


int main() {

    int a, b, p, q;
    std::cout << "Enter two integers a and b: ";
    
    if (!(std::cin >> a >> b) || b == 0) {
        // if (b == 0)
        std::cout << "Error!";
        std::exit(1);
    }

    p = a / b;
    q = a % b;
    std::cout << "p = " << p << ", q = " << q << '\n';

    return 0;
}
