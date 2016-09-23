#include "indexhandler.h"

// default cstr sets index to null
IndexHandler::IndexHandler(): index(NULL){
}

// dstr only deletes index if its not null
IndexHandler::~IndexHandler()
{
    if(index != NULL)
    {
        index->clearIndex();
    }
}

bool IndexHandler::isNull() const
{
    if(index == NULL)
    {
        return true;
    }
    return false;
}

// use folding on a string, summed 4 bytes at a time
// found on http://research.cs.vt.edu/AVresearch/hashing/strings.php
long IndexHandler::generateKey(string kweree)
{
    int intLength = kweree.length() / 4;

    long sum = 0;

    for (int i = 0; i < intLength; i++)
    {
        const char* c = kweree.substr(i * 4, (i * 4) + 4).c_str();
        long mult = 1;
        for (int j = 0; j < int(strlen(c)); j++)
        {
            sum += c[j] * mult;
            mult *= 256;
        }
    }

    const char* c = kweree.substr(intLength * 4).c_str();
    long mult = 1;
    for (int k = 0; k < int(strlen(c)); k++)
    {
        sum += c[k] * mult;
        mult *= 256;
    }

    return sum;
}

// writes contents of data structure to index file on disk
void IndexHandler::writeToIndex()
{
    ofstream indexFile;
    indexFile.open("index.txt", ios::out | ios::app);

    if(indexFile.is_open())
    {
        index->printContents(indexFile);
    }
    else
    {
        cout << BOLDRED << "!!ERROR: Could not open index file on disk" << RESET << endl;
    }
    indexFile.close();
}

// directly stores data from document parsing/cleaning to data structure
void IndexHandler::storeDocToStruct(string structType, vector<Document> &docs)
{
    // gotta decide when to delete index structure (and file while i'm at it)
    if(structType == "avl")
    {
        index = new AVLTree();
    }
    else
    {
        index = new HashTable();
    }

    for(int i = 0; i < int(docs.size()); i++)
    {
        // avoids going through documents that are empty
        if(docs[i].getDocText().empty() == false)
        {
            for(int j = 0; j < int(docs[i].getDocText().size()); j++)
            {
                // avoids adding "" to data structure
                if(docs[i].getDocText()[j].compare("") != 0)
                {
                    long genKey = generateKey(docs[i].getDocText()[j]);
                    index->addEntry(genKey, docs[i].getDocText()[j], docs[i].getPageNum());
                }
            }
        }
    }
}

// stores data from index file on disk to data structure
void IndexHandler::storeIndexToStruct(string structType, ifstream &indexFile)
{
    if(indexFile.is_open())
    {
        if(structType == "avl")
        {
            // delete first to avoid making a new index that already exists
            deleteIndex();
            index = new AVLTree();
        }
        else
        {
            // delete first to avoid making a new index that already exists
            deleteIndex();
            index = new HashTable();
        }

        string words;
        while(indexFile >> words)
        {
            string term = words;
            long genKey = generateKey(term);

            // avoid getting the '='
            indexFile >> words;
            // get the first document
            indexFile >> words;
            while(words != "|")
            {
                int pageNum = atoi(words.erase(0, 1).c_str());
                indexFile >> words;
                int frequency = atoi(words.erase(0, 1).c_str());
                index->addEntryWithFreq(genKey, term, pageNum, frequency);

                // get the next word
                indexFile >> words;
            }
        }
    }
    else
    {
        cout << BOLDRED << "!!ERROR: Could not open index file on disk\n" << RESET << endl;
    }
}

// deletes the index file and the data strucutre
void IndexHandler::deleteFileAndIndex()
{
    remove("index.txt");
    deleteIndex();
}

void IndexHandler::deleteIndex()
{
    // ensures that index won't be deleted if it hasn't been declared "new" yet
    if(index != NULL)
    {
        index->clearIndex();
        index = NULL;
    }
}

void IndexHandler::findResults(Query *&que)
{
    // checks whether the query was a single term
    // in this case, it doesn't have to bother checking for "and", "or", and "not"
    if(index != NULL)
    {
        if(que->getKweree() != "")
        {
            long searchKey = generateKey(que->getKweree());
            IndexEntry* result = index->findEntry(searchKey);

            if(result != NULL)
            {
                que->addToList(result->getPageList());
            }
            else
            {
                cout << BOLDRED << "!!NOTE: Could not find documents containing requested term\n" << RESET << endl;
                return;
            }
        }
        else
        {
            // checks whether query included AND boolean keyword
            // mininum of 2 words required to use AND
            // in this case it has to only add documents that appear in both matches' list
            if(que->getAndList().empty() == false)
            {
                long searchKey1 = generateKey(que->getAndList()[0]);
                IndexEntry* result1 = index->findEntry(searchKey1);

                long searchKey2 = generateKey(que->getAndList()[1]);
                IndexEntry* result2 = index->findEntry(searchKey2);

                // both results have to have come back
                if(result1 != NULL && result2 != NULL)
                {
                    vector<Page> inclusiveList;
                    for(int i = 0; i < int(result1->getPageList().size()); i++)
                    {
                        vector<Page>::iterator check = find(result2->getPageList().begin(), result2->getPageList().end(), result1->getPageList()[i]);
                        // if both have the same page number, add it to the inclusive list
                        if(check != result2->getPageList().end())
                        {
                            // make a copy page object that totals the frequencies of the two terms in the doc
                            Page resultsAdded(result1->getPageList()[i]);
                            int addedFreqs = check->getFrequency();
                            resultsAdded.totalFrequencies(addedFreqs);
                            inclusiveList.push_back(resultsAdded);
                        }
                    }

                    // checking if the AND list has more than 2 words
                    if(int(que->getAndList().size()) > 2)
                    {
                        for(int i = 2; i < int(que->getAndList().size()); i++)
                        {
                            long nextSearchKey = generateKey(que->getAndList()[i]);
                            IndexEntry* nextResult = index->findEntry(nextSearchKey);

                            if(nextResult != NULL)
                            {
                                for(int j = 0; j < int(inclusiveList.size()); j++)
                                {

                                    vector<Page>::iterator nextCheck = find(nextResult->getPageList().begin(), nextResult->getPageList().end(), inclusiveList[j]);
                                    // if both have the same page number, add to that page's frequency
                                    if(nextCheck != nextResult->getPageList().end())
                                    {
                                        // make a new page object that totals the frequencies of the two terms in the doc
                                        int addedFreqs = nextCheck->getFrequency();
                                        inclusiveList[j].totalFrequencies(addedFreqs);
                                    }
                                    // otherwise,the page number no longer qualifies
                                    else
                                    {
                                        vector<Page>::iterator remove = find(inclusiveList.begin(), inclusiveList.end(), inclusiveList[j]);
                                        inclusiveList.erase(remove);
                                    }
                                }
                            }
                            else
                            {
                                cout << BOLDRED << "!!NOTE: One or more terms could not be found in index\n" << RESET << endl;
                                return;
                            }
                        }
                    }

                    if(inclusiveList.empty() == false)
                    {
                        que->addToList(inclusiveList);
                    }
                    else
                    {
                        cout << BOLDRED << "!!NOTE: Could not find documents containing both AND terms\n" << RESET <<endl;
                        return;
                    }
                }
                else
                {
                    cout << BOLDRED << "!!NOTE: One or more terms could not be found in index\n" << RESET <<endl;
                    return;
                }
            }
            // checks whether query included OR boolean keyword
            // in this case it has to add documents that appear in either matches' list
            else if(que->getOrList().empty() == false)
            {
                long searchKey1 = generateKey(que->getOrList()[0]);
                IndexEntry* result1 = index->findEntry(searchKey1);

                long searchKey2 = generateKey(que->getOrList()[1]);
                IndexEntry* result2 = index->findEntry(searchKey2);

                vector<Page> inclusiveList;
                // it doesn't matter if both matches don't come up
                if(result1 != NULL)
                {
                    for(int i = 0; i < int(result1->getPageList().size()); i++)
                    {
                        Page resultsAdded(result1->getPageList()[i]);
                        inclusiveList.push_back(resultsAdded);
                    }
                }

                if(result2 != NULL)
                {
                    for(int i = 0; i < int(result2->getPageList().size()); i++)
                    {
                        // if the list already has one of the page numbers in it, don't add it again
                        vector<Page>::iterator check = find(inclusiveList.begin(), inclusiveList.end(), result2->getPageList()[i]);
                        if(check != inclusiveList.end())
                        {
                            int addedFreqs = result2->getPageList()[i].getFrequency();
                            check->totalFrequencies(addedFreqs);
                        }
                        else
                        {
                            Page resultsAdded(result2->getPageList()[i]);
                            inclusiveList.push_back(resultsAdded);
                        }
                    }
                }

                if(int(que->getOrList().size()) > 2)
                {
                    for(int i = 2; i < int(que->getAndList().size()); i++)
                    {
                        long nextSearchKey = generateKey(que->getAndList()[i]);
                        IndexEntry* nextResult = index->findEntry(nextSearchKey);

                        if(nextResult != NULL)
                        {
                            for(int j = 0; j < int(nextResult->getPageList().size()); j++)
                            {
                                // if it is in the list, add to the total frequency
                                vector<Page>::iterator nextCheck = find(inclusiveList.begin(), inclusiveList.end(), nextResult->getPageList()[j]);
                                if(nextCheck != inclusiveList.end())
                                {
                                    int addedFreqs = nextResult->getPageList()[j].getFrequency();
                                    nextCheck->totalFrequencies(addedFreqs);
                                }
                                // if it isn't in the list, then go ahead and add the new page number
                                else
                                {
                                    Page resultsAdded(nextResult->getPageList()[j]);
                                    inclusiveList.push_back(resultsAdded);
                                }
                            }
                        }
                    }
                }

                if(inclusiveList.empty() == false)
                {
                    que->addToList(inclusiveList);
                }
                else
                {
                    cout << BOLDRED << "!!NOTE: Could not find documents containing either OR terms\n" << RESET <<endl;
                    return;
                }
            }

            // checks whether query included NOT boolean keyword
            // in this case it has to exclude documents that appear in the matches' list
            // since NOT can be used with the other two prefixes in a query, has to be its own condition
            if(que->getNotList().empty() == false)
            {
                if(que->getNotInclude() != "")
                {
                    long searchKey = generateKey(que->getNotInclude());
                    IndexEntry* result = index->findEntry(searchKey);

                    if(result != NULL)
                    {
                        que->addToList(result->getPageList());
                    }
                    else
                    {
                        cout << BOLDRED << "!!NOTE: Could not find documents containing requested term\n" << RESET << endl;
                        return;
                    }
                }

                for(int i = 0; i < int(que->getNotList().size()); i++)
                {
                    long searchKey = generateKey(que->getNotList()[i]);
                    IndexEntry* result = index->findEntry(searchKey);

                    if(result != NULL)
                    {
                        que->removeFromList(result->getPageList());
                    }
                    else
                    {
                        cout << BOLDRED << "!!NOTE: Term not in index structure - Nothing to exclude\n" << RESET <<endl;
                        return;
                    }
                }
            }
        }
    }
    else
    {
        cout << BOLDRED << "!!ERROR: Unable to complete request - Must load data structure before you can search\n" << RESET <<endl;
        return;
    }

    // if no errors are encountered that force a return, the que doc list was filled and can be ordered
    orderByRelevancy(que);
}

// radix sort created by following this explanation: www.geeksforgeeks.org/radix-sort/
void IndexHandler::orderByRelevancy(Query *&que)
{
    // find the maximum number to know number of digits
    int max = getMax(que->getDocList());

    // do counting sort for every digit; instead of passing digit number, exp is passed
    // exp is 10^i where i is current digit number
    for (int exp = 1; max/exp > 0; exp *= 10)
    {
        countSort(que->getDocList(), exp);
    }
    // since countSort orders least to greatest, must reverse
    reverse(que->getDocList().begin(), que->getDocList().end());

    // after sorting, get rid of least relevant documents until only the top 15 remain
    while(int(que->getDocList().size()) > 15)
    {
        que->getDocList().pop_back();
    }
}

int IndexHandler::getMax(vector<Page> &qDocList)
{
    // initially assigns the frequency total of the first page as the max
    int max = qDocList[0].getFrequency();
    for (int i = 1; i < int(qDocList.size()); i++)
    {
        // if there is a bigger frequency total, then store it as the new max
        if (qDocList[i].getFrequency() > max)
            max = qDocList[i].getFrequency();
    }
    return max;
}

void IndexHandler::countSort(vector<Page> &qDocList, int exp)
{
    // output vector the size of the query doc list
    vector<Page> output (qDocList.size());
    int i, count[10] = {0};

    // store count of occurrences in count[]
    for (i = 0; i < int(qDocList.size()); i++)
        count[(qDocList[i].getFrequency()/exp)%10]++;

    // change count[i] so that count[i] now contains actual position of this digit in output[]
    for (i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // build the output array
    for (i = int(qDocList.size()) - 1; i >= 0; i--)
    {
        output[count[(qDocList[i].getFrequency()/exp)%10] - 1] = qDocList[i];
        count[(qDocList[i].getFrequency()/exp)%10]--;
    }

    // copy the output array to wordHolder, so that wordHolder now
    // contains sorted strings according to size length
    for (i = 0; i < int(qDocList.size()); i++)
    {
        qDocList[i] = output[i];
    }
}
