#ifndef UTILS
#define UTILS

#include <map>
#include <string>
#include <vector>

struct pivot{int line = 0; long double value = 0;};
struct linear_equation{std::map<std::string, long double> equation = {}; int nb_variables = 0;};
struct linear_system{std::vector<linear_equation> system = {}; int nb_equations = 0; int nb_variables = 0; std::string name = "S";};


pivot find_pivot(int n, linear_system system, int line, std::string var);

void swap_lines(linear_system system, int line_1, int line_2);

linear_equation divide_line(linear_equation equation, long double divider);

linear_equation multiply_line(linear_equation equation, long double multiplier);

linear_equation add_lines(linear_equation equation_1, linear_equation equation_2);
    
linear_equation subtract_lines(linear_equation equation_1, linear_equation equation_2);

linear_equation equation_formatting(std::string equation, int nb_variables);

linear_system system_formatting(std::string list_equations[], int nb_equations, int nb_variables);

linear_equation solve_system(linear_system system);

linear_system enter_system();

void display_equation(linear_equation equation, bool is_solution = false);

void display_system(linear_system system);

#endif