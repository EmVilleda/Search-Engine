/* UserInterface interacts with the user to allow them to control the different functions of the search engine
 *
 * Functions of the DocParser class allow for setting/entering one of the three mode available on the
 * search engine: Maintenance Mode, Interactive Mode, and Stress Test Mode
*/
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <sstream>
#include <string>
#include "datacrunch.h"
using namespace std;

// the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */

class UserInterface
{
private:
    DataCrunch* dCrunch;

public:
    UserInterface();
    ~UserInterface();

    void setMode(string mode);

    void enterMaintenance();
    void enterInteractive();
    void enterStressTest();
};

#endif // USERINTERFACE_H
