#include <iostream>


int main() {

    int a, b;
    std::cout << "Enter two integers a and b: ";
    
    // !(std::cin >> a >> b) check for successful input
    if (!(std::cin >> a >> b) || b == 0) {
        std::cout << "You entered chepuha! :(\n";
        std::exit(1);
    }

    int p = a / b;
    int q = a % b;
    std::cout << "p = " << p << ", q = " << q << '\n';

    return 0;
}
