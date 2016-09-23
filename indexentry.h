/* IndexEntry holds the term and list of pages related to the term
 *
 * Functions of the IndexEntry class allow for adding data to an index entry
*/
#ifndef INDEXENTRY_H
#define INDEXENTRY_H
#include <string>
#include <vector>
#include "page.h"
using namespace std;

class IndexEntry
{
private:
    string word;
    vector<Page> pageList;

public:
    IndexEntry();
    IndexEntry(string wrd, int pgEntry);
    IndexEntry(string wrd, int pgEntry, int freq);

    void setWord(string wrd);
    string getWord();

    void addPageEntry(int pgEntry);
    void addPageEntryWithFreq(int pgEntry, int freq);
    vector<Page> &getPageList();
};

#endif // INDEXENTRY_H
