#include "indexentry.h"

// default cstr
IndexEntry::IndexEntry(): word(""){
}

// cstr for creating entries when storing from documents to structure
IndexEntry::IndexEntry(string wrd, int pgEntry): word(wrd){
    pageList.push_back(Page(pgEntry));
}

// cstr for creating entries when storing from file to structure
IndexEntry::IndexEntry(string wrd, int pgEntry, int freq): word(wrd){
    pageList.push_back(Page(pgEntry, freq));
}

void IndexEntry::setWord(string wrd)
{
    word = wrd;
}

string IndexEntry::getWord()
{
    return word;
}

// adding entries when storing from documents to structure
void IndexEntry::addPageEntry(int pgEntry)
{
    // create a Page object to be compared against
    // overloaded == bool operator makes Page comparison only get pageNum, not frequency
    Page compare(pgEntry);

    // look in pageList for a Page object with the same pageNum value
    vector<Page>::iterator finder = find(pageList.begin(), pageList.end(), compare);
    // if there isn't a match, add the new page number to the list
    if(finder == pageList.end())
    {
        pageList.push_back(Page(pgEntry));
    }
    // if there is a match, increase the frequency
    else
    {
        finder->increaseFrequency();
    }
}

// adding entries when storing from file to structure
void IndexEntry::addPageEntryWithFreq(int pgEntry, int freq)
{
    pageList.push_back(Page(pgEntry, freq));
}

vector<Page> &IndexEntry::getPageList()
{
    return pageList;
}
