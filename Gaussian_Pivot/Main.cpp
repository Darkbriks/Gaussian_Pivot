#include <iostream>
#include <string>
#include <map>
#include "Utils.h"
#include "Gaussian_Pivot.h"

using namespace std;

/* Example of equations :
 *      {"3a + 2b + -1c = 1", "a + -1b + 4c = 4", "2a + b + c + = 5"}
 *      {"a + 2b + -1c = 3", "2a + -3b + c = -9", "-3a + b + 4c = 14"}
 *      {"2a + 5b = 7", "a + 3b = 9"}
 */

int main()
{
    // Enter the system and number of equations
    vector<string> liste_equation = enter_system();
    cout << endl << "How many equations are there : "; int n; cin >> n;

    // Format the system
    vector<map<string, long double>> linear_system = system_formatting(liste_equation.data(), n);
    
    // Solve the system
    linear_system = gaussian_pivot(linear_system, n);
    map<string, long double> solution = solve_system(linear_system, n);

    // Print the solution
    cout << endl << "Solution : " << endl;
    for (auto it = solution.begin(); it != solution.end(); it++)
    {
        cout << it->first << " = " << it->second << endl;
    }

    // Wait for user input
    system("PAUSE");
    
    return 0;
}
