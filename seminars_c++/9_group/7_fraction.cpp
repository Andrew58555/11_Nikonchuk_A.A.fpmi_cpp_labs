#include "7_fraction.h"

Fraction::Fraction(int n, unsigned m)
  : num_(n), denom_(m) {
    //num_ = n;
    //denom_ = m;
}

// argument list
Fraction::Fraction(const Fraction& other) 
  : num_(other.num_), denom_(other.denom_) {
    //num_ = other.num_;
    //denom_ = other.denom_;
}

Fraction::~Fraction() {
    std::cout << "~Fraction()\n";
}

void Fraction::PrintFraction() {
    std::cout << num_ << "/" << denom_ << '\n';
}

Fraction& Fraction::operator=(const Fraction& rhs){
    // f2 = f2
    if (this == &rhs) {
        return *this;
    }
    
    num_ = rhs.num_;
    denom_ = rhs.denom_;

    return *this;
}




