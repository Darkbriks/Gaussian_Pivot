#include "Gaussian_Pivot.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<map<string, long double>> gaussian_pivot(const vector<map<string, long double>> system, const int nb_equations)
/* This function takes a system of equations and returns the system in triangular form using the gaussian pivot method.
 *
 * The system is a vector of maps. Each map represents an equation. The keys are the variables and the values are the coefficients.
 *
 * The function not solve the system, it only returns the system in triangular form.
 * For solving the system, consider using the solve_system function in Utils.h
 *
 * EXAMPLE :
 *
 *
 * PARAMETERS :
 *      @system : The system of equations to solve
 *      @nb_equations : The number of equations in the system
 *      @return : The system in triangular form
 */
{
    vector<map<string, long double>> result = system; // Copy the system for not modifying the original system
    
    for (int i = 0; i < nb_equations - 1; i++) // For each line
    {
        string var = "a";
        var[0] += i;
        
        pivot pivot = find_pivot(nb_equations, result.data(), i, var); // Find the pivot.
        // The pivot may not be required for this implementation of the gaussian pivot method, because no division is used. However, it is still used for the sake of consistency with the other implementations of the gaussian pivot method.
        
        if (pivot.line != i) // If the pivot is not on the current line...
        {
            swap_lines(result.data(), i, pivot.line); // ...swap the current line with the line containing the pivot
        }
        
        for (int j = i + 1; j < nb_equations; j++) // For each line below the current line
        {
            result[j] = subtract_lines(multiply_line(result[j], result[i][var]), multiply_line(result[i], result[j][var])); // Multiply the current line by the coefficient of the variable of the current line in the line below and subtract the result from the line below
        }
    }
    return result; // Return the system in triangular form
}