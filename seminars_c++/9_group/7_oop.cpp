#include "7_fraction.h"


int main() {

    int x = 0;
    double y = 3.14;
    
    Fraction f{3, 2}; // aggregate initialization
    //Fraction f(3, 2);
    //Fraction f = Fraction(3, 2);

    //PrintFraction(f);
    f.PrintFraction();

    Fraction f1;
    f1.PrintFraction();
    
    Fraction f2(3);
    f2.PrintFraction();

    //Fraction f2_copy = f2;
    Fraction f2_copy(f2);
    //Fraction f2_copy = Fraction(f2);
    f2_copy.PrintFraction();

    f1 = f2_copy;
    f1.PrintFraction();

    return 0;
}
