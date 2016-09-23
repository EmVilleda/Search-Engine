#include "document.h"
#include "stemmer.h"

Document::Document(string text, int pg): textToClean(text), pageNum(pg){
}

Document::Document(string text, int pg, string title): pageNum(pg),  plainText(text), titleOfDoc(title){
}

void Document::setPageNum(int pg)
{
    pageNum = pg;
}

int Document::getPageNum() const
{
    return pageNum;
}

void Document::addToStrings(string s)
{
    docText.push_back(s);
}

// this pushes words onto the vector
void Document::cleanStrings()
{
    bool found20 = false;
    // here we should add on to the vector of stop words
    string line = " ";
    // open file
    ifstream stopFile("stopWords.txt");
    // put all words into text file
    while(getline(stopFile, line))
    {
        stopWords.push_back(line);
    }
       
    // take the text and parse it
    string temp = "";

    if(textToClean != "")
    {
        stringstream s(textToClean);
        // cout << "after assigning text to clean" << endl;

        while(s >> temp)
        {
            // clean the string and restore it
            temp = bleachString(temp);

            // here we check to see what the words are and whether they should be put on the vector
            // if temp is an empty string or a web address don't include it 
            //ALSO if the length of the string is longer than 30, then we don't want to include it
            if(temp != " " && temp != "" && temp.find("http") == std::string::npos && int(temp.size()) <= 20)
            {
                if(found20 == false && int(temp.size()) == 20)
                {
                    found20 = true;
                }
                // tranform all to lower case so we don't have multiples
                std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                // check to see if the iterator finds a match for the word
                vector<string>::iterator finder = find(stopWords.begin(), stopWords.end(), temp);
                if(finder == stopWords.end())
                {
                    // if there is not a match then we go ahead and stem it
                    // first go ahead and stem the worm
                    Stemmer::stem(temp);
                    // push on the word
                    docText.push_back(temp);
                }  
            }
        }
    }
}

// function returns an actual cleaned string, minus all the weird little non ascii characters
string Document::bleachString(string s)
{
    // create a buffer to go through the string
    const char* buffer = s.c_str();
    string tempString = "";
    int i = 0;

    while(i < int(s.length()))
    {
        if(buffer[i] >= 65 && buffer[i] <= 90)
        {
            // add onto the string
            tempString += buffer[i];
        }
        else if(buffer[i] >= 97 && buffer[i] <= 122)
        {
            // add onto the string
            tempString += buffer[i];
        }
        // for some reason, non ascii characters have this in them and so we have to account for it
        else if(buffer[i] == '&')
        {
            // parse the buffer until we reach the semicolon or the end (if we go past the end, we cause a seg fault)
            while(buffer[i] != ';' && i <= int(s.length()))
            {
                i++;
            }
        }
        i++;
    }

    // once we have cleaned the string then we return it
    return tempString;
}

vector<string> Document::getDocText()
{
    return docText;
}

int Document::sizeOfDocText()
{
    return docText.size();
}

string Document::getTitle()
{
    return titleOfDoc;
}

string Document::returnText()
{
    return plainText;
}
