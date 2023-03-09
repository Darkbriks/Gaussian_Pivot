#ifndef GAUSSIAN_PIVOT
#define GAUSSIAN_PIVOT

#include <map>
#include <string>
#include <vector>

// Gaussian pivot using multiplication between lines
std::vector<std::map<std::string, long double>> gaussian_pivot(std::vector<std::map<std::string, long double>> system, int nb_equations);

#endif