#include "hashtable.h"

HashTable::HashTable(): Index(){
    table = new HashEntry*[TABLE_SIZE];
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = NULL;
    }
}

HashTable::~HashTable()
{
    makeEmpty();
}

// =============== Virtual Functions (from Index) ===============
// adding entries when storing from documents to structure
void HashTable::addEntry(long qKey, string wrd, int pgNum)
{
    long hash = (abs(qKey) % TABLE_SIZE);

    while(table[hash] != NULL && table[hash]->getKey() != qKey)
    {
        hash = (hash + 1) % TABLE_SIZE;
    }

    if(table[hash] != NULL)
    {
        table[hash]->getIndexEntry()->addPageEntry(pgNum);
    }
    else
    {
        table[hash] = new HashEntry(qKey, wrd, pgNum);
    }
}

// adding entries when storing from file to structure
void HashTable::addEntryWithFreq(long qKey, string wrd, int pgNum, int freq)
{
    long hash = (abs(qKey) % TABLE_SIZE);

    while(table[hash] != NULL && table[hash]->getKey() != qKey)
    {
        hash = (hash + 1) % TABLE_SIZE;
    }

    if(table[hash] != NULL)
    {
        table[hash]->getIndexEntry()->addPageEntryWithFreq(pgNum, freq);
    }
    else
    {
        table[hash] = new HashEntry(qKey, wrd, pgNum, freq);
    }
}

IndexEntry *HashTable::findEntry(long qKey)
{
    long hash = (abs(qKey) % TABLE_SIZE);

    while(table[hash] != NULL && table[hash]->getKey() != qKey)
    {
        hash = (hash + 1) % TABLE_SIZE;
    }

    if(table[hash] == NULL)
    {
        return NULL;
    }
    else
    {
        return table[hash]->getIndexEntry();
    }
}

void HashTable::clearIndex()
{
    if(isIndexEmpty() == false)
    {
        makeEmpty();
    }
}

// determines if hash table is empty by checking if at least one index is not null
bool HashTable::isIndexEmpty() const
{
    HashEntry* check = NULL;
    int i = 0;

    while(check == NULL && i < TABLE_SIZE)
    {
        check = table[i];
        i++;
    }

    if(check != NULL)
    {
        return false;
    }

    return true;
}

void HashTable::printContents(std::ofstream &indexFile)
{
    for(int i = 0; i< TABLE_SIZE; i++)
    {
        if(table[i] != NULL)
        {
            indexFile << table[i]->getIndexEntry()->getWord() << " = ";
            stringstream pages;
            for(int j = 0; j < int(table[i]->getIndexEntry()->getPageList().size()); j++)
            {
                pages << "d" << table[i]->getIndexEntry()->getPageList()[j].getPageNum() << " [" << table[i]->getIndexEntry()->getPageList()[j].getFrequency() << "]";
                if(j+1 != int(table[i]->getIndexEntry()->getPageList().size()))
                {
                    pages << ", ";
                }
                if((pages.tellp() >= 130 && pages.tellp() < 145))
                {
                    if(j+1 != int(table[i]->getIndexEntry()->getPageList().size()))
                    {
                        pages << "\n\t";
                    }
                    indexFile << pages.str();
                    pages.str("");
                }
            }
            indexFile << pages.str() << " |" << endl;
        }
    }
}

// =============== Hash Table Functions ===============
// goes through each table index and deletes entry if its not null, then sets to null
void HashTable::makeEmpty()
{
    for(int i = 0; i< TABLE_SIZE; i++)
    {
        if(table[i] != NULL)
        {
            delete table[i];
            table[i] = NULL;
        }
    }
    delete [] table;
    table = NULL;
}
