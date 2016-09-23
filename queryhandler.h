/* QueryHandler parses user query requests to determine what the IndexHandler
 * should search for (accounts for user utilizing boolean operators in query)
 *
 * Functions of the QueryHandler class allow reading user query requests, storing parts
 * of request into attributes of a Query object, and send to IndexHandler for searching
*/
#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "query.h"
using namespace std;

// the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */

class QueryHandler
{
private:
    // vectors containing strings based on boolean assignment
    vector<string> andWords;
    vector<string> orWords;
    vector<string> notWords;
    vector<string> allWords;
    string notInclude;
    
    // vectors containing document numbers
    vector<int> includeDocs;
    vector<int> excludeDocs;
    
    Query* que;

public:
    QueryHandler();
    ~QueryHandler();

    void getWords(string line);
    void addToAnd(string s);
    void addToOr(string s);
    void addToNot(string s);
    void emptyVectors();
    
    Query *&getQue();
};

#endif // QUERYHANDLER_H
