/* test_Exercise3.cpp
 *
 * author: Ben Smith
 * date: 11/05/2015
 * Uses a standard online algorithm to compute the mean and variance
 * of a sequence of calls to the GaussianRandom function in randomsample.cpp .
 */

#include <iostream>
#include <stdlib.h>
#include <climits>
#include "randomsample.hpp"

int main(int argc, char **argv) {
  // Test the GaussianRandom function in randomsample.cpp.
  // Expected results : mean 0.0, variance 1.0 .

  if (argc != 2) {
    // Note: the first command-line argument in argv is always
    // the name of the program.  We want an additional argument,
    // specifying the number of trials to take, so we need argc = 2.
    std::cerr << "Invalid number of arguments.  Usage:" << std::endl;
    std::cerr << "    " << argv[0] << " ntrials" << std::endl;
    std::cerr << "where ntrials is the number of trials." << std::endl;
    exit(1);
  }

  int n = atoi(argv[1]);

  if (n < 2) {
    std::cerr << "Error: Number of trials should be between 2 and " << INT_MAX
              << std::endl;
    exit(1);
  }

  double mean = 0.0;
  double M2 = 0.0;
  for (int i = 0; i < n; i++) {
    double x = GaussianRandom();
    double delta = x - mean;
    mean += delta / n;
    M2 += delta * (x - mean);
  }

  double variance = M2 / (n - 1);

  std::cout << n << " calls to GaussianRandom( )" << std::endl;
  std::cout << "-> Mean (should be approximately 0.0): " << mean << std::endl;
  std::cout << "-> Variance (should be approximately 1.0): " << variance
            << std::endl;

  exit(0);
}
