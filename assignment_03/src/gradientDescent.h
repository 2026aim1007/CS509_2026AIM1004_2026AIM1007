#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>

double evaluatePolynomial(const std::vector<double>& coeffs, double x);
double evaluateDerivative(const std::vector<double>& coeffs, double x);

void runGradientDescent(
    const std::vector<double>& coeffs,
    double initial_x,
    double learning_rate,
    double tolerance,
    int max_iterations,
    double& final_x,
    double& final_fx,
    int& actual_iterations,
    bool& converged
);

#endif