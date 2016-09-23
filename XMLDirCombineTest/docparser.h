#ifndef DOCPARSER_H
#define DOCPARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
//need to add in these files
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>

#include "docobject.h"

using namespace std;

class DocParser
{
private:

    vector<string> files;
    vector<DocObject> docObjects;

    string dir;
    string line;
    string oneDot;
    string twoDot;
    string check;
    string page;
    string title;
    string id;
    string revision;
    string text;

    int idNum;


public:
    DocParser();
    int getdir (string dir, vector<string> &files);
    void parseDocuments(string dirName);
    void printPageNumbers();
};

#endif // DOCPARSER_H
