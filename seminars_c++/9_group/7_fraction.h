#include <iostream>

struct Fraction {
    int num_;
    unsigned denom_;

    //Fraction() {
    //    num_ = 0;
    //    denom_ = 1;
    //}

    Fraction(int n = 0, unsigned m = 1);
    
    // argument list
    Fraction(const Fraction&);

    ~Fraction();

    void PrintFraction();
    
    // f1 = f2 = f3 = ...
    Fraction& operator=(const Fraction&);
};

