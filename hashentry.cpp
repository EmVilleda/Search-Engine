#include "hashentry.h"

// default cstr sets entry to null
HashEntry::HashEntry(): key(0), entry(NULL){
}

// overloaded cstr for creating entries when storing from documents to structure
HashEntry::HashEntry(long ky, string wrd, int pgNum): key(ky)
{
    entry = new IndexEntry(wrd, pgNum);
}

// overloaded cstr for creating entries when storing from files to structure
HashEntry::HashEntry(long ky, string wrd, int pgNum, int freq): key(ky){
    entry = new IndexEntry(wrd, pgNum, freq);
}

// overloaded dstr
HashEntry::~HashEntry()
{
    delete entry;
}

long HashEntry::getKey()
{
    return key;
}

IndexEntry *&HashEntry::getIndexEntry()
{
    return entry;
}
