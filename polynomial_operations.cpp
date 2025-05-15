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

bool PolynomialOps::equal(const CPolynomial& lhs, const CPolynomial& rhs, const double tol) {
    int m = std::max(lhs.degree(), rhs.degree());
    for (int i = 0; i <= m; ++i) {
        if (std::abs(lhs[i] - rhs[i]) > tol) return false;
    }
    return true;
}
