/* HashTable stores index data into unordered map structure that prevents storing conflicts
 *
 * Functions of the HashTable class allow for adding entries to table with unique keys
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <sstream>
#include "index.h"
#include "hashentry.h"
using namespace std;

// value represents the amount of buckets the hash table will use
#define TABLE_SIZE 2000000

class HashTable: public Index
{
private:
    HashEntry** table;

public:
    HashTable();

    // ===== Virtual functions =====
    virtual ~HashTable();
    void addEntry(long qKey, string wrd, int pgNum);
    void addEntryWithFreq(long qKey, string wrd, int pgNum, int freq);
    IndexEntry *findEntry(long qKey);
    void clearIndex();
    bool isIndexEmpty() const;
    void printContents(std::ofstream &indexFile);

    void makeEmpty();
};

#endif // HASHTABLE_H
