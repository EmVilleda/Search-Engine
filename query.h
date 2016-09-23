/* Query holds the parts of a query, including boolean operators and keywords, to be sent
 * and interpreted by the IndexHandler
 *
 * Functions of the Query class will allow for storing the parts of the query into objects
 * that will be used to track the word's appearance in the index and list of documents
*/
#ifndef QUERY_H
#define QUERY_H
#include <string>
#include <vector>
#include "page.h"
using namespace std;

class Query
{
private:
    string original;
    string kweree;
    string notInclude;
    vector <Page> docList;
    vector<string> andList;
    vector<string> orList;
    vector<string> notList;

public:
    Query();
    Query(string kwr);
    //constructor with three vectors that are passed into by query handler
    Query(vector<string> a, vector<string> o, vector<string> n, string nI);

    void setOriginal(string origin);
    string getOriginal();

    string getKweree();
    string getNotInclude();
    vector<Page> &getDocList();
    void addToList(vector<Page> &include);
    void removeFromList(vector<Page> &exclude);

    vector<string> &getAndList();
    vector<string> &getOrList();
    vector<string> &getNotList();
};

#endif // QUERY_H
