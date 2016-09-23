/* Index serves as the interface for the data structure that will hold the index data
 * Data Structure will either be an AVL Tree or Hash Table
 *
 * Functions of the Index interface will allow the IndexHandler to add new index entries
 * (an entry contains a word with a list of documents containing it) and search/retrieve entries
*/
#ifndef INDEX_H
#define INDEX_H
#include <fstream>
#include "indexentry.h"
using namespace std;

class Index
{
public:
    Index() {}
    virtual ~Index() {}
    virtual void addEntry(long qKey, string wrd, int pgNum) = 0;
    virtual void addEntryWithFreq(long qKey, string wrd, int pgNum, int freq) = 0;
    virtual IndexEntry *findEntry(long qKey) = 0;
    virtual void clearIndex() = 0;
    virtual bool isIndexEmpty() const = 0;
    virtual void printContents(std::ofstream &indexFile) = 0;
};

#endif // INDEX_H
