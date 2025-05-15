#pragma once

#include "polynomial.h"
#include <vector>
#include <cmath>

namespace PolynomialOps {
    /** @brief Add two polynomials */
    CPolynomial add(const CPolynomial& lhs, const CPolynomial& rhs);

    /** @brief Subtract rhs from lhs */
    CPolynomial subtract(const CPolynomial& lhs, const CPolynomial& rhs);

    /** @brief Compute derivative of a polynomial */
    CPolynomial derivative(const CPolynomial& poly);

    /** @brief Compare two polynomials within tolerance */
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

inline CPolynomial& operator-=(CPolynomial& lhs, const CPolynomial& rhs) {
    lhs = PolynomialOps::subtract(lhs, rhs);
    return lhs;
}

// Equality operators
inline bool operator==(const CPolynomial& lhs, const CPolynomial& rhs) {
    return PolynomialOps::equal(lhs, rhs);
}

inline bool operator!=(const CPolynomial& lhs, const CPolynomial& rhs) {
    return !PolynomialOps::equal(lhs, rhs);
}

// Unary derivative operator
inline CPolynomial operator~(const CPolynomial& poly) {
    return PolynomialOps::derivative(poly);
}