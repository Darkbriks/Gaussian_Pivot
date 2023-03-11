#include "../Header/Utils.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

pivot find_pivot(const int n, linear_system system, const int line, string var)
/* This function finds the pivot of a system of linear equations.
 * The pivot is the biggest value of a variable in a column in terms of absolute value.
 *
 * The system must be of the form :
 *     a = 1 ; b = 2 ; c = 3 ; ... ; independent_term = 4
 *
 * PARAMETERS:
 *     @param n : number of equations in the system
 *     @param system : the system of linear equations
 *     @param line : the line where the pivot will be found
 *     @param var : the variable that will be used to find the pivot
 *     @return : the pivot
 */
{
    pivot pivot; // Create a pivot
    pivot.line = line; // Set the pivot line to the current line
    pivot.value = system.system[line].equation[var]; // Set the pivot value to the value of the variable in the current line
    
    for (int i = line + 1; i < n; i++) // For each line after the current line
    {
        if (abs(system.system[i].equation[var]) > abs(pivot.value)) // If the value of the variable is bigger than the current pivot
        {
            pivot.line = i; // Update the pivot line
            pivot.value = system.system[i].equation[var]; // Update the pivot value
        }
    }
    return pivot; // Return the pivot
}

void swap_lines(linear_system system, const int line_1, const int line_2)
/* This function swaps two lines of a system of linear equations.
 *
 * PARAMETERS:
 *     @param system : the system of linear equations
 *     @param line_1 : the first line to be swapped
 *     @param line_2 : the second line to be swapped
 */
{
    const linear_equation temp = system.system[line_1]; // Create a temporary line
    system.system[line_1] = system.system[line_2]; // Assign the second line to the first line
    system.system[line_2] = temp; // Assign the first line to the second line
}

linear_equation divide_line(linear_equation equation, const long double divider)
/* This function divides a line of a system of linear equations by a number.
 *
 * EXAMPLE:
 *      divide_line({{"a", 2}, {"b", 4}, {"c", 6}, {"independent_term", 8}}, 2) = {{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}
 *      divide_line({{"a", 2}, {"b", 4}, {"c", 6}, {"independent_term", 8}}, -2) = {{"a", -1}, {"b", -2}, {"c", -3}, {"independent_term", -4}}
 *
 * PARAMETERS:
 *     @param equation : the line to be divided
 *     @param divider : the number that will divide the line
 *     @return : the divided line
 */
{
    for (auto& var : equation.equation) // For each variable in the line
    {
        var.second /= divider; // Divide the variable by the divider
    }
    return equation; // Return the divided line
}

linear_equation multiply_line(linear_equation equation, const long double multiplier)
/* This function multiplies a line of a system of linear equations by a number.
 *
 * EXAMPLE:
 *      multiply_line({{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}, 2) = {{"a", 2}, {"b", 4}, {"c", 6}, {"independent_term", 8}}
 *      multiply_line({{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}, -2) = {{"a", -2}, {"b", -4}, {"c", -6}, {"independent_term", -8}}
 *
 * PARAMETERS:
 *     @param equation : the line to be multiplied
 *     @param multiplier : the number that will multiply the line
 *     @return : the multiplied line
 */
{
    for (auto& var : equation.equation) // For each variable in the line
    {
        var.second *= multiplier; // Multiply the variable by the multiplier
    }
    return equation; // Return the multiplied line
}

linear_equation add_lines(linear_equation equation_1, linear_equation equation_2)
/* This function adds two lines of a system of linear equations.
 *
 * EXAMPLE:
 *      add_lines({{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}, {{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}) = {{"a", 2}, {"b", 4}, {"c", 6}, {"independent_term", 8}}
 *      add_lines({{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}, {{"a", -1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}) = {{"a", 0}, {"b", 4}, {"c", 6}, {"independent_term", 8}}
 *
 * PARAMETERS:
 *     @param equation_1 : the first line to be added
 *     @param equation_2 : the second line to be added
 *     @return : the added line
 */
{
    for (auto& var : equation_1.equation) // For each variable in the first line
    {
        var.second += equation_2.equation[var.first]; // Add the value of the variable in the second line to the value of the variable in the first line
    }
    return equation_1; // Return the added line
}

linear_equation subtract_lines(linear_equation equation_1, linear_equation equation_2)
/* This function subtracts two lines of a system of linear equations.
 *
 * EXAMPLE:
 *      subtract_lines({{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}, {{"a", -2}, {"b", 4}, {"c", 6}, {"independent_term", 8}}) = {{"a", 3}, {"b", -2}, {"c", -3}, {"independent_term", -4}}
 *      subtract_lines({{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}, {{"a", 1}, {"b", 2}, {"c", 3}, {"independent_term", 4}}) = {{"a", 0}, {"b", 0}, {"c", 0}, {"independent_term", 0}}
 *
 * PARAMETERS:
 *     @param equation_1 : the first line to be subtracted
 *     @param equation_2 : the second line to be subtracted
 *     @return : the subtracted line
 */
{
    for (auto& var : equation_1.equation) // For each variable in the first line
    {
        var.second -= equation_2.equation[var.first]; // Subtract the value of the variable in the second line to the value of the variable in the first line
    }
    return equation_1; // Return the subtracted line
}

linear_equation equation_formatting(string equation, const int nb_variables)
/* Function to format a linear equation into a map.
 *
 * The equations must be written in the following form :
 *    2a + 3b + 4c = 5
 *    
 * It will be transformed into:
 *    {{"a", 2}, {"b", 3}, {"c", 4}, {"independent_term", 5}}
 *
 * VARIABLES:
 *      Variables must be a letter include between a and z and correspond to the position of the variable in the equation
 *      For example, variable a corresponds to the first term of the equation, variable b to the second term, etc.
 *
 *      If the equation contains less variables than the number of variables specified, the missing variables will be added with a coefficient equal to 0
 *      If the equation has more variables than the specified number of variables, the excess variables will be removed
 *      If the equation contains the same number of variables as the number of specific variables, no changes will be made
 *      If the variable is not a letter, it will be removed
 *      If the variable is not in alphabetical order, it may cause the program to malfunction and some coefficients may be replaced by 0 or be incorrectly assigned
 *      If a variable is located after the independent term, it will not be taken into account
 *
 * COEFFICIENTS:
 *      Coefficients of variables must be integers or decimals
 *      They must be written in the following form:
 *      2a; 3.5b; -4c
 *
 *      Coefficients of variables must be written before the variable
 *
 *      If a coefficient is equal to 1, it can be written in one of two following forms: a; 1a
 *      If the coefficient is negative, a plus sign must be added in front of the coefficient in addition to the minus sign, as follows: + -4c; + -4.5c
 *      If these conditions are not respected, the coefficient will not be considered correctly, and the program will not be able to solve the equation
 *
 * INDEPENDENT TERM:
 *      The equation can contain an independent term.
 *      If this is not specified, it will be considered as being equal to 0
 *
 *      The equation can contain an equal sign
 *      If this is not specified, the independent term will be considered equal to 0
 *
 *      If the independent term is not an integer or a decimal, it will not be taken into account
 *      If the independent term is present, it must be written after the equal sign in the following form: = 5; = -5; = 5.5
 *
 * EXAMPLES OF VALID EQUATIONS:
 *      2a + 3b + 4c = 5
 *      c = 2
 *      a
 *      b + -4c = 5
 *      "" (empty equation, returns an equation with all coefficients equal to 0 and an independent term equal to 0)
 *
 * EXAMPLES OF INVALID EQUATIONS:
 *      2a + 3b = 5 + 6c
 *      2b + 3a = 5
 *      2a - 3b + 4c = 5
 *
 * WARNING :
 *      AN INVALID EQUATION CAN BE TREATED AS A VALID EQUATION, AND DO NOT GENERATE AN ERROR, BUT THE PROGRAM WILL NOT BE ABLE TO SOLVE THE SYSTEM CORRECTLY PAY VERY CARE THAT ALL EQUATIONS ARE VALID
 *
 * PARAMETERS:
 *      @param equation : the equation to be formatted
 *      @param nb_variables : the number of variables in the equation
 *      @return : the formatted equation
 */
{
    if (equation.find("=") == string::npos) // If the equation does not contain an equal sign
    {
        equation += "="; // Add an equal sign at the end of the equation
    }
    
    if (equation.find("=") == equation.length() - 1) // If the equation contains an equal sign at the end
    {
        equation += "0"; // Add 0 at the end of the equation
    }
    
    linear_equation variables; // Map to store the variables and their coefficients
    
    equation.erase(remove(equation.begin(), equation.end(), ' '), equation.end()); // Remove all spaces in the equation
    
    const string independent_term = equation.substr(equation.find("=") + 1); // Get the independent term
    variables.equation["independent_term"] = stod(independent_term); // Add the independent term to the map
    
    equation = equation.substr(0, equation.find("=")); // Remove the independent term from the equation
    
    for (int i = 0; i < nb_variables; i++) // For each variable
    {
        string variable = "a"; // Create the variable name
        variable[0] += i; // Change the variable name according to the coefficient's position in the equation
        
        if (equation.find(variable) == string::npos) // If the variable is not in the equation
        {
            variables.equation[variable] = 0; // Add the variable to the map with a coefficient equal to 0
        }
        else // If the variable is in the equation
        {
            if (equation.find(variable) == 0) // If the variable is at the beginning of the equation
            {
                equation.insert(0, "1"); // Add a coefficient equal to 1
            }
            
            string coefficient = equation.substr(0, equation.find("x")); // Get the coefficient of the variable
            
            variables.equation[variable] = stod(coefficient); // Add the variable to the map with its coefficient
            
            equation.erase(0, equation.find("+") + 1); // Remove the variable and its coefficient from the equation
        }
    }
    variables.nb_variables = nb_variables; // Add the number of variables to the map
    return variables; // Return the formatted equation
}

linear_system system_formatting(string list_equations[], const int nb_equations, const int nb_variables)
/* Function to format a system of linear equations into a vector of maps.
 *
 * The system must in form of an array of strings containing the linear equations
 *
 * EXAMPLES OF VALID SYSTEMS:
 *      string system[] = {"2a + 3b + 4c = 5", "a = 2", "b + -4c = 5"};
 *
 * WARNING : 
 *      BEFORE USING THIS FUNCTION, SEE THE DOCUMENTATION OF THE FUNCTION equation_formatting TO KNOW THE CONDITIONS TO RESPECT SO THAT THE EQUATIONS OF THE SYSTEM ARE VALID
 *
 * PARAMETERS:
 *      @param list_equations : the array of equations to be formatted
 *      @param nb_equations : the number of equations in the system
 *      @return : the formatted system
 */
{
    linear_system linear_system; // Vector to store the formatted equations
    
    for (int i = 0; i < nb_equations; i++) // For each equation
    {
        linear_equation equation = equation_formatting(list_equations[i], nb_variables); // Format the equation using the function equation_formatting
        linear_system.system.push_back(equation); // Add the formatted equation to the vector
    }
    linear_system.nb_equations = nb_equations; // Add the number of equations to the vector
    linear_system.nb_variables = nb_variables; // Add the number of variables to the vector
    return linear_system; // Return the formatted system
}

linear_equation solve_system(linear_system system)
/* Function to solve a system of linear equations.
 *
 * The system must be triangularized before being solved
 * You can use the function gaussian_pivot to triangularize the system
 *
 * The system must have only one solution, otherwise the function will not be able to solve it
 *
 * PARAMETERS:
 *      @param system : the system to be solved
 *      @param nb_equations : the number of equations in the system
 *      @return : the solution of the system
 */
{
    linear_equation solution; // Map to store the solution
    
    for (int i = 0; i < system.nb_equations; i++) // For each equation
    {
        string variable = "a"; // Create the variable name
        variable[0] += i; // Change the variable name according to the coefficient's position in the equation
        
        solution.equation[variable] = system.system[i].equation["independent_term"]; // Add the variable to the map with its coefficient
    }
    
    for (int i = system.nb_equations - 1; i >= 0; i--) // For each equation
    {
        string variable = "a"; // Create the variable name
        variable[0] += i; // Change the variable name according to the coefficient's position in the equation
        
        for (int j = system.nb_equations - 1; j > i; j--) // For each variable
        {
            string known_variable = "a"; // Create the variable name
            known_variable[0] += j; // Change the variable name according to the coefficient's position in the equation
            
            system.system[i].equation["independent_term"] -= system.system[i].equation[known_variable] * solution.equation[known_variable]; // Subtract the known variable from the independent term
            system.system[i].equation[known_variable] = 0; // Set the coefficient of the known variable to 0
        }
        solution.equation[variable] = system.system[i].equation["independent_term"] / system.system[i].equation[variable]; // Divide the independent term by the coefficient of the variable to get the value of the variable
    }
    return solution; // Return the solution
}

linear_system enter_system()
/* This function allows you to enter a system of linear equations and format it into a vector of maps.
 *
 * Each equations must be written in the following form :
 *    2a + 3b + 4c = 5
 *
 * For more information, see the documentation of the function equation_formatting
 *
 * PARAMETERS:
 *      @return : the system of linear equations in formating form
 */
{
    cout << "Name of the system : "; string name; getline(cin, name);
    cout << "Number of variables in the system : "; int nb_variables; cin >> nb_variables; cin.ignore();
    cout << "Enter each equation of the system of linear equations, one equation per line, and enter an empty line to stop" << endl;

    linear_system system; // Vector to store the formatted equations

    while (true)
    {
        string equation;
        getline(cin, equation);
        if (equation == "") {break;}
        system.system.push_back(equation_formatting(equation, nb_variables));
        system.nb_equations++;
    }

    system.nb_variables = nb_variables;
    system.name = name;
    return system;
}

void display_equation(linear_equation equation, const bool is_solution)
{
    if (is_solution)
    {
        cout << endl << "Solution : " << endl;
        for (auto it = equation.equation.begin(); it != equation.equation.end(); it++) // For each variable
        {
            cout << it->first << " = " << it->second << endl; // Display the variable and its value
        }
    }
    else
    {
        for (auto it = equation.equation.begin(); it != equation.equation.end(); it++) // For each variable
            {
            if (it->first == "independent_term") // If the variable is the independent term
                {
                cout << " = " << it->second; // Display the independent term
                }
            else // If the variable is not the independent term
                {
                cout << " + " << it->second << it->first; // Display the variable
                }
            }
    }
}

void display_system(const linear_system system)
{
    cout << "System " << system.name << " ; " << system.nb_equations << " equations ; " << system.nb_variables << " variables" << endl;
    for (int i = 0; i < system.nb_equations; i++) // For each equation
    {
        cout << "Equation " << i + 1 << " : "; // Display the equation number
        display_equation(system.system[i]); // Display the equation
        cout << endl;
    }
}
