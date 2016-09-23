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

#include "docparser.h"

using namespace std;
using namespace rapidxml;


int main()
{

    //create a docparser object
    DocParser *obj = new DocParser();
    obj->parseDocuments("WikiDump");

    //after this, we will need to check all of the pageNumbers in the vectorfile

    //page numbers is printing correctly, so we would have to have it clean the strings, and then print the page number and maybe
    //the first string
    obj->printPageNumbers();

    cout << "Hello World!" << endl;
    return 0;
}

