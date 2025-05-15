#include "polynomial_io.h"
#include <iostream>

void PolynomialIO::print(const CPolynomial& poly) {
    std::cout << poly << std::endl;
}

void PolynomialIO::format(std::ostream& os, const CPolynomial& poly) {
    bool first = true;
    for (int i = poly.degree(); i >= 0; --i) {
        double c = poly[i];
        if (std::abs(c) < 1e-12) continue;
        if (!first) os << (c >= 0 ? " + " : " - ");
        os << std::abs(c);
        if (i > 0) os << "x";
        if (i > 1) os << "^" << i;
        first = false;
    }
    if (first) os << "0";
}