#pragma once

#include "polynomial.h"
#include <ostream>

class PolynomialIO {
public:
    static void print(const CPolynomial& poly);

    friend std::ostream& operator<<(std::ostream& os, const CPolynomial& poly) {
        format(os, poly);
        return os;
    }

private:
    static void format(std::ostream& os, const CPolynomial& poly);
};