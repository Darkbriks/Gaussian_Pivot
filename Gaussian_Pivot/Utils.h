#ifndef UTILS
#define UTILS

#include <map>
#include <string>
#include <vector>

struct pivot{int line; long double value;};

pivot find_pivot(int n, std::map<std::string, long double> system[], int line, std::string var);

void swap_lines(std::map<std::string, long double> system[], int line_1, int line_2);

std::map<std::string, long double> divide_line(std::map<std::string, long double> equation, long double divider);

std::map<std::string, long double> multiply_line(std::map<std::string, long double> equation, long double multiplier);

std::map<std::string, long double> add_lines(std::map<std::string, long double> equation_1, std::map<std::string, long double> equation_2);
    
std::map<std::string, long double> subtract_lines(std::map<std::string, long double> equation_1, std::map<std::string, long double> equation_2);

std::map<std::string, long double> equation_formatting(std::string equation, int nb_variables);

std::vector<std::map<std::string, long double>> system_formatting(std::string list_equations[], int nb_equations);

std::map<std::string, long double> solve_system(std::vector<std::map<std::string, long double>> system, int nb_equations);

std::vector<std::string> enter_system();

std::vector<std::map<std::string, long double>> enter_system_formatting(); // TODO : check why it doesn't work when trying to solve the system with gaussian pivot

int compute_nb_variables(std::string equation); // TODO : test

int compute_nb_variables(std::vector<std::map<std::string, long double>> system); // TODO : test

int compute_nb_equations(std::string list_equations[]); // TODO : implement

int compute_nb_equations(std::vector<std::map<std::string, long double>> system); // TODO : implement

void display_system(std::map<std::string, long double> solution); // TODO : implement

void display_system(std::vector<std::map<std::string, long double>> system); // TODO : implement


#endif
