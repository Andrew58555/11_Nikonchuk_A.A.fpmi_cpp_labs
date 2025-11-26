#include "7_string.h"


int main() {

    String s;
    String d('a', 4);
    String copy(d); 
    // copy: size_->5, data_->[a,a,a,a,\0]   

    copy = d;

    return 0;
}