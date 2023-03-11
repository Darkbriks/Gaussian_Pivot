#include <iostream>
#include "Header/Utils.h"
#include "Header/Gaussian_Pivot.h"

using namespace std;

/* Example of equations :
 *      {"3a + 2b + -1c = 1", "a + -1b + 4c = 4", "2a + b + c + = 5"}
 *      {"a + 2b + -1c = 3", "2a + -3b + c = -9", "-3a + b + 4c = 14"}
 *      {"2a + 5b = 7", "a + 3b = 9"}
 */

int main()
{
    // Enter the system and number of equations
    //vector<string> list_equation = enter_system();
    //cout << endl << "How many equations are there : "; int n; cin >> n;

    // Format the system
    //linear_system linear_system = system_formatting(list_equation.data(), n, n);

    // Enter the system and number of equations
    linear_system linear_system = enter_system();
    display_system(linear_system);
    
    // Solve the system
    linear_system = gaussian_pivot(linear_system);
    linear_equation solution = solve_system(linear_system);

    // Print the solution
    display_equation(solution, true);
    
    // Wait for user input
    system("PAUSE");
    
    return 0;
}
