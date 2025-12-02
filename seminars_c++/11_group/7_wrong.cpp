#include <iostream>
#include <cstdlib>

class Dynamic {
    int *p;
public:
    Dynamic(int i);
    ~Dynamic() { 
        delete p;
        std::cout << "освобождение памяти\n";
    }

    Dynamic(const Dynamic& other)
      : p(new int()) {
        *p = *other.p;
    }

    int get () { return *p; }
};

Dynamic::Dynamic(int i) {
    p = new int(i);
}

// Возвращает отрицательное значение *ob.p
int GetNegative(Dynamic ob) {
    return -ob.get();
}

int main() {
    Dynamic o(-10);
    std::cout << o.get() << "\n";
    std::cout << GetNegative(o) << "\n";

    Dynamic o2(20);
    std::cout << o2.get() << "\n";
    std::cout << GetNegative(o2) << "\n";
    
    std::cout << o.get() << "\n";
    std::cout << GetNegative(o) << "\n";
    
    return 0 ;
}
