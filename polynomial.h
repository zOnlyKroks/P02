#pragma once
#include <vector>
#include <map>
#include <iostream>

class CPolynomialIO;
class CPolynomialOperations;

class CPolynomial {
    std::vector<double> coefficients;
    char variable;

public:
    explicit CPolynomial(const std::vector<double>& param, bool reversed = false);
    CPolynomial(const double param[], int degree, bool reversed = false);

    [[nodiscard]] int degree() const;
    void changeVariable(char var);
    double operator[](int index) const;
    [[nodiscard]] double evaluateAt(double x) const;
    [[nodiscard]] std::map<double, double> evaluateAt(const std::vector<double> &x) const;

    friend class CPolynomialIO;
    friend class CPolynomialOperations;

    friend std::ostream& operator<<(std::ostream& os, const CPolynomial& poly);
};