#include <iostream>
#include <limits>

int main() {
    long long num;
    std::cout << "Enter a non-negative integer: ";
    while (!(std::cin >> num)) {
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // klafksdflsk hjadhfsjd hjsdh fs hd

    if (num < 0) {
        std::cout << "The number must be non-negative." << std::endl;
        return 1;
    }

    int sum = 0;
    while (num) {
        sum += num % 10;
        num /= 10;
    }

    std::cout << "Sum of digits: " << sum << std::endl;

    return 0;
}
