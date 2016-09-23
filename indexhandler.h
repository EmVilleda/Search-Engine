/* IndexHandler writes an index file to disk using data recieved from DocParser
 * Stores index data into an AVL Tree or Hash Table to complete query requests
 *
 * Functions of the DocParser class allow reading data from document parser to create index,
 * storing data into data structures, and traversing data structure to complete query requests
*/
#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include "index.h"
#include "avltree.h"
#include "hashtable.h"
#include "document.h"
#include "query.h"
using namespace std;

// the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */

class IndexHandler
{
private:
    Index* index;

public:
    IndexHandler();
    ~IndexHandler();

    bool isNull() const;

    // To be used in adding/searching for entries
    long generateKey(string kweree);

    // Functions to be utilized in Maintanence Mode
    void writeToIndex();
    void storeDocToStruct(string structType, vector<Document> &docs);
    void deleteFileAndIndex();
    void deleteIndex();

    // Functions to be utilized in Interactive Mode
    void storeIndexToStruct(string structType, ifstream &indexFile);
    void findResults(Query *&que);
    // the following three make up a radix sort algorithm
    void orderByRelevancy(Query *&que);
    int getMax(vector<Page> &qDocList);
    void countSort(vector<Page> &qDocList, int exp);
};

#endif // INDEXHANDLER_H
