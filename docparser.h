/* DocParser parses through relevant data contained in a given XMLDocument file
 * Prepares data for storing in Document objects and passing into IndexHandler
 *
 * Functions of the DocParser class allow removing stop/stem words from documents,
 * storing relevant data into Document objects, and passing cleaned data for index handling
*/
#ifndef DOCPARSER_H
#define DOCPARSER_H
#include <iostream>
#include <sstream>
#include <fstream>
// necessary files for XML document parsing
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string>
#include <vector>
#include "document.h"
#include "page.h"
using namespace rapidxml;
using namespace std;

// the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */

class DocParser
{
private:
    vector<string> files;
    // vector of documents that are parsed and wil be cleaned
    vector<Document> docObjects;
    // copy of docObjects that persistently holds parsed documents until index file is deleted
    vector<Document> docObjectsCopy;

    // strings that holds keywords in XML documents
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

    int getdir(string dir, vector<string> &files);
    void parseDocuments(string dirName);
    void cleanDocObjects();
    vector<Document> &getDocObjects();

    // Functions to be utilized in Interactive Mode (search)
    void printResults(vector<Page> &pages);
    void printPage(int pageNumber);
    void printSelectedPage(int pageNum, string dirName);
    
    // need to empty dParser vector<Document> after each add in maintenance mode
    void emptyVectors();
};

#endif // DOCPARSER_H
