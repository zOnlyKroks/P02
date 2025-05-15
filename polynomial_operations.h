#pragma once

#include "polynomial.h"
#include <vector>
#include <cmath>

namespace PolynomialOps {
    CPolynomial add(const CPolynomial& lhs, const CPolynomial& rhs);

    CPolynomial subtract(const CPolynomial& lhs, const CPolynomial& rhs);

    CPolynomial derivative(const CPolynomial& poly);

    CPolynomial multiply(const CPolynomial& lhs, const CPolynomial& rhs);

    CPolynomial divide(const CPolynomial& lhs, const CPolynomial& rhs);

    bool equal(const CPolynomial& lhs, const CPolynomial& rhs, double tol = 1e-12);
}

// Arithmetic operators
inline CPolynomial operator+(const CPolynomial& lhs, const CPolynomial& rhs) {
    return PolynomialOps::add(lhs, rhs);
}

inline CPolynomial operator-(const CPolynomial& lhs, const CPolynomial& rhs) {
    return PolynomialOps::subtract(lhs, rhs);
}

inline CPolynomial& operator+=(CPolynomial& lhs, const CPolynomial& rhs) {
    lhs = PolynomialOps::add(lhs, rhs);
    return lhs;
}

inline CPolynomial operator*(const CPolynomial& lhs, const CPolynomial& rhs) {
    return PolynomialOps::multiply(lhs, rhs);
}

inline CPolynomial& operator*=(CPolynomial& lhs, const CPolynomial& rhs) {
    lhs = PolynomialOps::multiply(lhs, rhs);
    return lhs;
}

inline CPolynomial& operator-=(CPolynomial& lhs, const CPolynomial& rhs) {
    lhs = PolynomialOps::subtract(lhs, rhs);
    return lhs;
}

inline bool operator==(const CPolynomial& lhs, const CPolynomial& rhs) {
    return PolynomialOps::equal(lhs, rhs);
}

inline bool operator!=(const CPolynomial& lhs, const CPolynomial& rhs) {
    return !PolynomialOps::equal(lhs, rhs);
}

inline CPolynomial operator~(const CPolynomial& poly) {
    return PolynomialOps::derivative(poly);
}