#include <random>

double random_range(double lower, double upper) {
    static std::uniform_real_distribution<double> dist(lower, upper);
    static std::mt19937 gen;
    return dist(gen);
}

double random_range() { return random_range(0.0, 1.0); }