#include "7_string.h"

// Class o(5);
// Class o = 5;


int main() {

    String s;
    String d('a', 4);
    String copy(d); 
    // copy: size_->5, data_->[a,a,a,a,\0]   

    copy = d;

    String l{'h', 'e', 'l', 'l', 'o'};
    std::cout << l[2] << '\n';
    l[2] = 'b'; // l.operator[](2);
    std::cout << l[2] << '\n';

    const String cs{'h', 'e', 'l', 'l', 'o'};
    std::cout << cs[2] << '\n';

    std::cout << l << std::endl;

    return 0;
}
