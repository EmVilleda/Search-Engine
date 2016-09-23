#include "queryhandler.h"
#include "stemmer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

QueryHandler::QueryHandler(): notInclude(""), que(NULL){
}

QueryHandler::~QueryHandler(){
    if(que != NULL)
    {
        delete que;
    }
}

void QueryHandler::getWords(string line)
{
    // bools that act as switch cases
    bool andBool = false;
    bool orBool = false;
    bool notBool = false;

    // strings to check for
    string andString = "and";
    string orString = "or";
    string notString = "not";

    // strings to check by
    string temp = "";

    // need to make sure that the input query is not empty
    if(line != "")
    {
        // create string stream of line
        stringstream s(line);
        while(s >> temp)
        {
            // here we need to change the words to lower case to prevent continuous
            std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            // push the temp onto the vector
            allWords.push_back(temp);
        }

        // at this point, full vector so add to and words
        // a few cases to account for
        if(allWords.size() == 1)
        {
            // if there is only one word, then push it into the single que
            // go ahead and stem the word
            Stemmer::stem(allWords[0]); 
            que = new Query(allWords[0]);
            que->setOriginal(line);
            return;
        }
        else
        {
            // for loop with three bools that get switched on and off
            for(int i = 0; i < int(allWords.size()); i++)
            {
                // first word cannot be NOT boolean operator
                if(allWords[0].compare(notString) == 0)
                {
                    cout << BOLDRED << "!!ERROR: Illegal use of boolean operator 'NOT' (Cannot go in the front of a query)" << RESET << endl;

                    // create empty Query to avoid segfaulting
                    que = new Query();
                    return;
                }
                else if(allWords[i].compare(andString) == 0)
                {
                    andBool = true;
                    orBool = false;
                    notBool = false;
                }
                else if(allWords[i].compare(orString) == 0)
                {
                    orBool = true;
                    andBool = false;
                    notBool = false;
                }
                else if(allWords[i].compare(notString) == 0)
                {
                    notBool = true;
                    andBool = false;
                    orBool = false;
                }
                // check the boolean conditions
                else if(andBool == true && allWords[i].compare(andString) != 0)
                {
                    addToAnd(allWords[i]);
                }
                else if(orBool == true && allWords[i].compare(orString) != 0)
                {
                    addToOr(allWords[i]);
                }
                else if(notBool == true && allWords[i].compare(notString) != 0)
                {
                    addToNot(allWords[i]);
                }
                // here we need to check if the booleans are not initilaized
                // if all the bools are false then put the word in and words
                else if(notBool == false && orBool == false && andBool == false)
                {
                    notInclude = allWords[i];
                }
            }

            // initialization of the query object
            que = new Query(andWords, orWords, notWords, notInclude);
            que->setOriginal(line);
        }  
    }
    // if a query has not been entered
    else
    {
        cout << BOLDRED << "!!ERROR: No query was entered" << RESET << endl;

        // create empty Query to avoid segfaulting
        que = new Query();
        return;
    }
}

void QueryHandler::addToAnd(string s)
{
// here would be where we would stem the word, so making query handler a friend of the stem
// class would work

    Stemmer::stem(s);
    andWords.push_back(s);
}

void QueryHandler::addToOr(string s)
{
    Stemmer::stem(s);
    orWords.push_back(s);
}

void QueryHandler::addToNot(string s)
{
    Stemmer::stem(s);
    notWords.push_back(s);
}

Query *&QueryHandler::getQue()
{
    return que;
}

void QueryHandler::emptyVectors()
{
    // this function goes ahead and empties all the vectors so that we can start with a clean slate
    // clear an words
    andWords.clear();
    orWords.clear();
    notWords.clear();
    
    // clear all words function
    allWords.clear();
    
    // clear the include docs
    includeDocs.clear();
    
    // clear the exclude docs
    excludeDocs.clear();
    
    // reset the string
    notInclude = "";
    
    delete que;
    que = NULL;
}
