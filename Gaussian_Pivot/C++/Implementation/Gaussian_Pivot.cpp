#include "../Header/Gaussian_Pivot.h"
#include "../Header/Utils.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

linear_system gaussian_pivot(const linear_system system)
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
 *      @return : The system in triangular form
 */
{
    linear_system result = system; // Copy the system for not modifying the original system
    
    for (int i = 0; i < result.nb_equations - 1; i++) // For each line
    {
        string var = "a";
        var[0] += i;
        
        pivot pivot = find_pivot(result.nb_equations, result, i, var); // Find the pivot.
        // The pivot may not be required for this implementation of the gaussian pivot method, because no division is used. However, it is still used for the sake of consistency with the other implementations of the gaussian pivot method.
        
        if (pivot.line != i) // If the pivot is not on the current line...
        {
            swap_lines(result, i, pivot.line); // ...swap the current line with the line containing the pivot
        }
        
        for (int j = i + 1; j < result.nb_equations; j++) // For each line below the current line
        {
            result.system[j] = subtract_lines(multiply_line(result.system[j], result.system[i].equation[var]), multiply_line(result.system[i], result.system[j].equation[var])); // Multiply the current line by the coefficient of the variable of the current line in the line below and subtract the result from the line below
        }
    }
    return result; // Return the system in triangular form
}