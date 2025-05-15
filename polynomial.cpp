#include "polynomial.h"
#include <cmath>
#include <algorithm>

CPolynomial::CPolynomial(const std::vector<double>& param, const bool reversed) {
    variable = 'x';
    if (reversed) {
        coefficients = std::vector(param.rbegin(), param.rend());
    }
    else {
        coefficients = param;
    }
    while (coefficients.size() > 1 && coefficients.back() == 0) {
        coefficients.pop_back();
    }
}

CPolynomial::CPolynomial(const double param[], const int degree, const bool reversed) {
    variable = 'x';
    if (reversed) {
        coefficients = std::vector<double>(degree + 1);
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = param[degree - i];
        }
    }
    else {
        coefficients = std::vector(param, param + degree + 1);
        std::ranges::reverse(coefficients.begin(), coefficients.end());
    }

    while (coefficients.size() > 1 && coefficients.back() == 0) {
        coefficients.pop_back();
    }
}

int CPolynomial::degree() const {
    return static_cast<int>(coefficients.size()) - 1;
}

void CPolynomial::changeVariable(const char var) {
    if (var >= 'a' && var <= 'z') {
        variable = var;
    }
}

double CPolynomial::operator[](int index) const {
    if (index >= 0 && index < static_cast<int>(coefficients.size()))
        return coefficients[index];
    return 0.0;
}

double CPolynomial::evaluateAt(const double x) const {
    double result = 0.0;
    for (int i = 0; i <= degree(); i++) {
        result += (*this)[i] * std::pow(x, i);
    }
    return result;
}

std::map<double, double> CPolynomial::evaluateAt(const std::vector<double>& x) const {
    std::map<double, double> results;
    for (double value : x) {
        results[value] = evaluateAt(value);
    }
    return results;
}