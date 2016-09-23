/* DataCrunch controls the 3 main search engine handlers that run the program
 * (DocParser, IndexHandler, and QueryHandler)
 *
 * Depends on user input to determine which process(es) of the search engine are necessary
*/
#ifndef DATACRUNCH_H
#define DATACRUNCH_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "docparser.h"
#include "indexhandler.h"
#include "queryhandler.h"
using namespace std;

// the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */

class DataCrunch
{
private:
    DocParser* dParser;
    IndexHandler* iHandler;
    QueryHandler* qHandler;

public:
    DataCrunch();
    ~DataCrunch();

    // Maitenance Mode
    void addToIndex();
    void clearIndex();

    void supplyDocuments();
    void loadDocToIndex();

    // Interactive Mode
    void loadFileToIndex();
    void searchQuery(string kweree);

    // Stress Test Mode
    void runCommands(string path);
};

#endif // DATACRUNCH_H
