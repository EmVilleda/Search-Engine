/* Final Project - Let's Search (Kwirē Search Engine) collaboration by Aurora Havens and Emely Villeda-Principe
 * CSE 2341 Data Structure
 *
 * Create a search engine that takes in XML documents to parse terms and store into an index
 * Allows users to then search for documents containing keywords  (in order of relevancy)
*/
#include <iostream>
#include "userinterface.h"
#include "datacrunch.h"
using namespace std;

// the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */

int main()
{
    UserInterface ui;

    cout << "***** To begin, input one of the following commands *****" << endl;
    cout << BOLDBLACK << "\t'mmode'" << RESET<< " - Enter Maintenance Mode" << endl;
    cout << BOLDBLACK << "\t'imode'" << RESET<< " - Enter Interactive Mode" << endl;
    cout << BOLDBLACK << "\t'stmode'" << RESET<< " - Enter Stress Test mode" << endl;
    cout << BOLDBLACK << "\t'exit'" << RESET<< " - Exit program" << endl;

    string mode;
    cout << ":: ";
    getline(cin, mode);
    cout << endl;

    while(mode != "exit")
    {
        ui.setMode(mode);

        cout << "***** Input one of the following commands *****" << endl;
        cout << BOLDBLACK << "\t'mmode'" << RESET<< " - Enter Maintenance Mode" << endl;
        cout << BOLDBLACK << "\t'imode'" << RESET<< " - Enter Interactive Mode" << endl;
        cout << BOLDBLACK << "\t'stmode'" << RESET<< " - Enter Stress Test mode" << endl;
        cout << BOLDBLACK << "\t'exit'" << RESET<< " - Exit program" << endl;
        cout << ":: ";
        getline(cin, mode);
        cout << endl;
    }
}

