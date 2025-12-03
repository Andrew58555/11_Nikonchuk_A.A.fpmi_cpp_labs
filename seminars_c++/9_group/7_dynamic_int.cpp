#include <iostream>
#include <cstdlib>

class DynamicInt {
    int *p;
public:
    DynamicInt(int i);
    ~DynamicInt() { 
        delete p;
        std::cout << "освобождение памяти\n";
    }

    DynamicInt(const DynamicInt& other)
      : p(new int()) {
    
        *p = *other.p;
    }

    int get () { return *p; }
};

DynamicInt::DynamicInt(int i) {
    p = new int(i);
}

// Возвращает отрицательное значение *ob.p
int GetNegative(DynamicInt ob) {
    return -ob.get();
}

int main() {
    DynamicInt obj1(-10);
    std::cout << obj1.get() << "\n";
    std::cout << GetNegative(obj1) << "\n";

    DynamicInt obj2(20);
    std::cout << obj2.get() << "\n";
    std::cout << GetNegative(obj2) << "\n";
    
    std::cout << obj1.get() << "\n";
    std::cout << GetNegative(obj1) << "\n";
    
    return 0 ;
}
