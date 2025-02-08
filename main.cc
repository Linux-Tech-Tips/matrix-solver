/** Simple test main file */

#include "Rational.hh"

int main(void) {
    Rational r(-3.5f);
    std::puts(r.toString().c_str());
    return 0;
}
