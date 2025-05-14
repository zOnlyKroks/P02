// CPolynomial.h
#pragma once
#include <algorithm>
#include <complex>
#include <vector>
#include <map>
#include <iostream>

class CPolynomial {
    std::vector<double> coefficients;
    char variable;

public:
    // Constructor with vector of coefficients
    explicit CPolynomial(const std::vector<double>& param, bool reversed = false) {
        variable = 'x';
        if (reversed) {
            coefficients = std::vector(param.rbegin(), param.rend());
        }
        else {
            coefficients = param;
        }
        // Remove trailing zeros
        while (coefficients.size() > 1 && coefficients.back() == 0) {
            coefficients.pop_back();
        }
    }

    // Constructor with array of coefficients and degree
    CPolynomial(const double param[], const int degree, const bool reversed = false) {
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
        // Remove trailing zeros
        while (coefficients.size() > 1 && coefficients.back() == 0) {
            coefficients.pop_back();
        }
    }

    // Get degree of polynomial
    [[nodiscard]] int degree() const {
        return coefficients.size() - 1;
    }

    // Change variable used for display
    void changeVariable(char var) {
        if (var >= 'a' && var <= 'z') {
            variable = var;
        }
    }

    // Test output to console
    void testOutput() const {
        bool first = true;
        for (int i = degree(); i >= 0; i--) {
            double coef = coefficients[i];
            if (coef == 0) continue;

            if (coef > 0 && !first) {
                std::cout << " + ";
            }
            else if (coef < 0) {
                std::cout << (first ? "" : " - ");
                coef = -coef;
            }

            if ((coef != 1 || i == 0) && coef != -1) {
                std::cout << coef;
            }

            if (i > 0) {
                std::cout << variable;
                if (i > 1) {
                    std::cout << "^" << i;
                }
            }

            first = false;
        }
        if (first) {
            // Polynomial is zero
            std::cout << "0";
        }
        std::cout << std::endl;
    }

    // Task A1: Implement access operator
    double operator[] (const int index) const {
        if (index >= 0 && index < coefficients.size()) {
            return coefficients[index];
        }
        return 0.0;
    }

    // Task A2: Implement evaluateAt method
    [[nodiscard]] double evaluateAt(const double x) const {
        double result = 0.0;
        for (int i = 0; i <= degree(); i++) {
            result += (*this)[i] * std::pow(x, i);
        }
        return result;
    }

    // Task A2: Overload evaluateAt method for vector of values
    [[nodiscard]] std::map<double, double> evaluateAt(const std::vector<double> x) const {
        std::map<double, double> results;
        for (double value : x) {
            results[value] = evaluateAt(value);
        }
        return results;
    }

    // Task A4: Implement addition operator
    CPolynomial operator+(const CPolynomial& rhs) const {
        const int maxDegree = std::max(degree(), rhs.degree());
        std::vector result(maxDegree + 1, 0.0);

        for (int i = 0; i <= maxDegree; i++) {
            result[i] = (*this)[i] + rhs[i];
        }

        return CPolynomial(result);
    }

    // Task A4: Implement subtraction operator
    CPolynomial operator-(const CPolynomial& rhs) const {
        const int maxDegree = std::max(degree(), rhs.degree());
        std::vector result(maxDegree + 1, 0.0);

        for (int i = 0; i <= maxDegree; i++) {
            result[i] = (*this)[i] - rhs[i];
        }

        return CPolynomial(result);
    }

    // Task A5: Implement += operator
    CPolynomial& operator+=(const CPolynomial& rhs) {
        *this = *this + rhs;
        return *this;
    }

    // Task A6: Implement equality operator
    bool operator==(const CPolynomial& rhs) const {
        if (degree() != rhs.degree()) {
            return false;
        }

        for (int i = 0; i <= degree(); i++) {
            if ((*this)[i] != rhs[i]) {
                return false;
            }
        }

        return true;
    }

    // Task A6: Implement inequality operator
    bool operator!=(const CPolynomial& rhs) const {
        return !(*this == rhs);
    }

    // Task A7: Implement derivative operator (~)
    CPolynomial operator~() const {
        if (degree() == 0) {
            return CPolynomial({0.0});
        }

        std::vector<double> derivCoeffs(degree());
        for (int i = 1; i <= degree(); i++) {
            derivCoeffs[i-1] = i * coefficients[i];
        }

        return CPolynomial(derivCoeffs);
    }

    // Task A3: Implement output operator as friend
    friend std::ostream& operator<<(std::ostream& os, const CPolynomial& poly);
};

// Task A3: Implement output operator
std::ostream& operator<<(std::ostream& os, const CPolynomial& poly) {
    bool first = true;
    for (int i = poly.degree(); i >= 0; i--) {
        double coef = poly[i];
        if (coef == 0) continue;

        if (coef > 0 && !first) {
            os << " + ";
        }
        else if (coef < 0) {
            os << (first ? "" : " - ");
            coef = -coef;
        }

        if ((coef != 1 || i == 0) && coef != -1) {
            os << coef;
        }

        if (i > 0) {
            os << poly.variable;
            if (i > 1) {
                os << "^" << i;
            }
        }

        first = false;
    }
    if (first) {
        // Polynomial is zero
        os << "0";
    }
    return os;
}

// Main function to test functionality
int main() {
    std::cout << "Testing CPolynomial class" << std::endl;

    // Test 1: Testing construction and basic functionality
    std::cout << "\nTest 1: Testing construction and basic functionality" << std::endl;
    double p[] = { 2.1, -4.5, 0, -3.3 }; // 2.1x^3 - 4.5x^2 + 0x - 3.3
    const CPolynomial poly(p, 3);
    poly.testOutput();
    std::cout << "Degree: " << poly.degree() << std::endl;

    // Test A1: Accessing coefficients with []
    std::cout << "\nTest A1: Accessing coefficients with []" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "Coefficient " << i << ": " << poly[i] << "\n";
    }

    // Test A2: Evaluating polynomial at specific points
    std::cout << "\nTest A2: Evaluating polynomial at specific points" << std::endl;
    std::cout << "f(0) = " << poly.evaluateAt(0) << std::endl;
    std::cout << "f(1) = " << poly.evaluateAt(1) << std::endl;
    std::cout << "f(2) = " << poly.evaluateAt(2) << std::endl;

    // Test A2: Evaluating polynomial for vector of values
    std::cout << "\nTest A2: Evaluating polynomial for vector of values" << std::endl;
    const std::vector<double> values = { -1, 0, 1, 2, 3 };
    for (const std::map<double, double> results = poly.evaluateAt(values); const auto& pair : results) {
        std::cout << "f(" << pair.first << ") = " << pair.second << std::endl;
    }

    // Test A3: Testing output operator
    std::cout << "\nTest A3: Testing output operator" << std::endl;
    std::cout << "Polynomial: " << poly << std::endl;

    // Test A4.1: Testing addition operator
    std::cout << "\nTest A4.1: Testing addition operator" << std::endl;
    double p2[] = { 1, 2, 3 }; // x^2 + 2x + 3
    const CPolynomial poly2(p2, 2);
    std::cout << "Polynomial 1: " << poly << std::endl;
    std::cout << "Polynomial 2: " << poly2 << std::endl;
    std::cout << "Sum: " << (poly + poly2) << std::endl;

    // Test A4.2: Testing subtraction operator
    std::cout << "\nTest A4.2: Testing subtraction operator" << std::endl;
    std::cout << "Difference: " << (poly - poly2) << std::endl;

    // Test A5: Testing += operator
    std::cout << "\nTest A5: Testing += operator" << std::endl;
    CPolynomial poly3 = poly;
    std::cout << "Before +=: " << poly3 << std::endl;
    poly3 += poly2;
    std::cout << "After +=: " << poly3 << std::endl;

    // Test A6: Testing equality operators
    std::cout << "\nTest A6: Testing equality operators" << std::endl;
    const CPolynomial& poly4 = poly;
    std::cout << "poly == poly4: " << (poly == poly4) << std::endl;
    std::cout << "poly != poly4: " << (poly != poly4) << std::endl;
    std::cout << "poly == poly2: " << (poly == poly2) << std::endl;
    std::cout << "poly != poly2: " << (poly != poly2) << std::endl;

    // Test A7: Testing derivative operator
    std::cout << "\nTest A7: Testing derivative operator" << std::endl;
    std::cout << "Polynomial: " << poly << std::endl;
    std::cout << "Derivative: " << ~poly << std::endl;

    return 0;
}