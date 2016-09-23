/* Document stores the relevant information of an XML Document for use in index handling
 *
 * Functions of the Document class allow for retrieving the different types of information,
 * such as the document author, title, text, and number (relative to the whole dump file)
*/
#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Document
{
private:
    vector<string> docText;     // words found in this document
    string textToClean;         // text needing cleaning
    int pageNum;                // current document number

    string plainText;
    string titleOfDoc;

    vector<string> stopWords;

public:
    // cstr for vector<Document> to be parsed
    Document(string text, int pg);
    // cst for copy vector<Document> for query printing
    Document(string text, int pg, string title);

    void setPageNum(int pg);
    int getPageNum() const;
    
    //functions needed to get the title and text so that it prints
    string getTitle();
    string returnText();

    void addToStrings(string s);
    void cleanStrings();
    string bleachString(string s);

    vector<string> getDocText();
    int sizeOfDocText();
};

// overloaded comparision operator to be able to compare Doc object when using iterator
inline bool operator==(const Document& lhs, const Document& rhs)
{
    // only need to check if pageNumbers match to count as a match
    if(lhs.getPageNum() == rhs.getPageNum())
    {
        return true;
    }

    return false;
}

#endif // DOCUMENT_H
