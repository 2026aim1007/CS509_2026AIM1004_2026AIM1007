#include "gradientDescent.h"
#include <iostream>
#include <cmath>

double evaluatePolynomial(const std::vector<double>& coeffs, double x) {
    double result = 0.0;
    double x_pow = 1.0; 
    
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result += coeffs[i] * x_pow;
        x_pow *= x; 
    }
    return result;
}

double evaluateDerivative(const std::vector<double>& coeffs, double x) {
    double result = 0.0;
    double x_pow = 1.0; 
    
    for (size_t i = 1; i < coeffs.size(); ++i) {
        result += coeffs[i] * i * x_pow;
        x_pow *= x;
    }
    return result;
}

void runGradientDescent( const std::vector<double>& coeffs, double initial_x, double learning_rate, double tolerance, int max_iterations, double& final_x, double& final_fx, int& actual_iterations, bool& converged) {
    double current_x = initial_x;
    converged = false;
    actual_iterations = 0;
    for (int i = 0; i < max_iterations; ++i) {
        actual_iterations++;
        double grad = evaluateDerivative(coeffs, current_x);
        if (std::abs(grad) <= tolerance) {
            converged = true;
            break;
        }
        current_x = current_x - learning_rate * grad;
    }
    final_x = current_x;
    final_fx = evaluatePolynomial(coeffs, current_x);
}