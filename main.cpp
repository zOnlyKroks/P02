#include "polynomial.h"
#include "polynomial_io.h"
#include "polynomial_operations.h"

int main() {
    std::cout << "Testing Multi-Class Polynomial Implementation" << std::endl;

    // Test 1: Testing construction and basic functionality
    std::cout << "\nTest 1: Testing construction and basic functionality" << std::endl;
    double p[] = { 2.1, -4.5, 0, -3.3 }; // 2.1x^3 - 4.5x^2 + 0x - 3.3
    const CPolynomial poly(p, 3);
    PolynomialIO::print(poly);
    std::cout << "Degree: " << poly.degree() << std::endl;

    // Test A1: Accessing coefficients with []
    std::cout << "\nTest A1: Accessing coefficients with []" << std::endl;
    for (int i = 0; i < 4; i++) {
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