#include "polynomial_operations.h"
#include <algorithm>

CPolynomial PolynomialOps::add(const CPolynomial& lhs, const CPolynomial& rhs) {
    const int m = std::max(lhs.degree(), rhs.degree());
    std::vector coeffs(static_cast<size_t>(m) + 1, 0.0);
    for (int i = 0; i <= m; ++i) {
        coeffs[static_cast<size_t>(i)] = lhs[i] + rhs[i];
    }
    return CPolynomial(coeffs);
}

CPolynomial PolynomialOps::subtract(const CPolynomial& lhs, const CPolynomial& rhs) {
    const int m = std::max(lhs.degree(), rhs.degree());
    std::vector coeffs(static_cast<size_t>(m) + 1, 0.0);
    for (int i = 0; i <= m; ++i) {
        coeffs[static_cast<size_t>(i)] = lhs[i] - rhs[i];
    }
    return CPolynomial(coeffs);
}

CPolynomial PolynomialOps::derivative(const CPolynomial& poly) {
    const int n = poly.degree();
    if (n == 0) {
        return CPolynomial({0.0});
    }
    std::vector<double> deriv(static_cast<size_t>(n));
    for (int i = 1; i <= n; ++i) {
        deriv[static_cast<size_t>(i - 1)] = static_cast<double>(i) * poly[i];
    }
    return CPolynomial(deriv);
}

CPolynomial PolynomialOps::multiply(const CPolynomial& lhs, const CPolynomial& rhs) {
    const int m = lhs.degree();
    const int n = rhs.degree();
    std::vector coeffs(static_cast<size_t>(m + n) + 1, 0.0);
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            coeffs[static_cast<size_t>(i + j)] += lhs[i] * rhs[j];
        }
    }
    return CPolynomial(coeffs);
}

CPolynomial PolynomialOps::divide(const CPolynomial &lhs, const CPolynomial &rhs) {
    const int degA = lhs.degree();
    const int degB = rhs.degree();

    if (degB < 0 || (degB == 0 && std::abs(rhs[0]) < 1e-12)) {
        throw std::invalid_argument("PolynomialOps::divide: division by zero polynomial");
    }

    if (degA < degB) {
        return CPolynomial(std::vector{0.0});
    }

    int qDeg = degA - degB;
    std::vector quotient(qDeg + 1, 0.0);
    std::vector remainder(degA + 1, 0.0);

    for (int i = 0; i <= degA; ++i) {
        remainder[i] = lhs[i];
    }

    const double leadDen = rhs[degB];

    for (int k = qDeg; k >= 0; --k) {
        const double coeff = remainder[k + degB] / leadDen;
        quotient[k] = coeff;

        for (int j = 0; j <= degB; ++j) {
            remainder[k + j] -= coeff * rhs[j];
        }
    }

    return CPolynomial(quotient);
}

bool PolynomialOps::equal(const CPolynomial& lhs, const CPolynomial& rhs, const double tol) {
    int m = std::max(lhs.degree(), rhs.degree());
    for (int i = 0; i <= m; ++i) {
        if (std::abs(lhs[i] - rhs[i]) > tol) return false;
    }
    return true;
}
