#include "query.h"

// default cstr
Query::Query(): original(""), kweree(""), notInclude(""){
}

// overloaded cstr for single word queries
Query::Query(string kwr): original(""), kweree(kwr), notInclude(""){
}

// overloaded cstr for queries using any of the boolean operators
Query::Query(vector<string> a, vector<string> o, vector<string> n, string nI): original(""), kweree(""),
notInclude(nI), andList(a), orList(o), notList(n){
}

void Query::setOriginal(string origin)
{
    original = origin;
}

string Query::getOriginal()
{
    return original;
}

string Query::getKweree()
{
    return kweree;
}

string Query::getNotInclude()
{
    return notInclude;
}

vector<Page> &Query::getDocList()
{
    return docList;
}

// adds to the list of documents from the "inclusion" list given
void Query::addToList(vector<Page> &include)
{
    for(int i = 0; i < int(include.size()); i++)
    {
        // makes sure the document hasn't already been added
        vector<Page>::iterator finder = find(docList.begin(), docList.end(), include[i]);
        if(finder == docList.end())
        {
            docList.push_back(include[i]);
        }
    }
}

// removes documents that match the "exclusion" list given
void Query::removeFromList(vector<Page> &exclude)
{
    for(int i=0; i < int(exclude.size()); i++)
    {
        vector<Page>::iterator finder = find(docList.begin(), docList.end(), exclude[i]);
        if(finder != docList.end())
        {
            docList.erase(finder);
        }
    }
}

vector<string> &Query::getAndList()
{
    return andList;
}

vector<string> &Query::getOrList()
{
    return orList;
}

vector<string> &Query::getNotList()
{
    return notList;
}
