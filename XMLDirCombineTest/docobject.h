#ifndef DOCOBJECT_H
#define DOCOBJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class DocObject
{
private:
    //string of words found in this document
    vector<string> myDoc;
    int pageNum;
    string textToClean;

public:
    DocObject(string text, int p);
    void setPageNum(int p);
    int getPageNum();
    void addToStrings(string s);
    void cleanStrings();
    string bleachString(string s);
    void returnFirstString();

};

#endif // DOCOBJECT_H
