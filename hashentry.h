/* HashEntry holds the index data for the Hash Table structure
 *
 * Functions of the HashEntry class for creating new IndexEntry objects and accessing data
*/
#ifndef HASHENTRY_H
#define HASHENTRY_H
#include "indexentry.h"
using namespace std;

class HashEntry
{
friend class HashTable;
private:
    long key;
    IndexEntry* entry;

public:
    HashEntry();
    HashEntry(long ky, string wrd, int pgNum);
    HashEntry(long ky, string wrd, int pgNum, int freq);
    ~HashEntry();

    long getKey();
    IndexEntry *&getIndexEntry();
};

#endif // HASHENTRY_H
