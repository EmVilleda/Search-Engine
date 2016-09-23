/* AVLTree is one of the possible data structures for storing index data
 *
 * Functions of the AVLTree class allow for adding entries, searching for entries, and prining data
*/
#ifndef AVLTree_H
#define AVLTree_H
#include <iostream>
#include <sstream>
#include "index.h"
#include "avlnode.h"
using namespace std;

// values for determining which direction to traverse
#define EQ 0
#define LEFT -1
#define RIGHT 1

class AVLTree : public Index
{
private:
    AVLNode* root;

public:
    AVLTree();

    // ===== virtual functions =====
    virtual ~AVLTree();
    void addEntry(long qKey, string wrd, int pgNum);
    void addEntryWithFreq(long qKey, string wrd, int pgNum, int freq);
    IndexEntry *findEntry(long qKey);
    void clearIndex();
    bool isIndexEmpty() const;
    void printContents(ofstream &indexFile);

    void makeEmpty(AVLNode* &rt);
    int compare(long key1, long key2);

    // recursive insertion, search, and traversal
    void insert(AVLNode *&rt, long ky, string wrd, int pgNum);
    void insertWithFreq(AVLNode *&rt, long ky, string wrd, int pgNum, int freq);
    AVLNode *search(AVLNode *&rt, long ky);
    void traversal(AVLNode *&rt, std::ofstream &indexFile);

    // functions for maintaining tree balance
    int height(AVLNode* temp);
    int difference(AVLNode* temp);
    void rotateLeft(AVLNode *&parent);
    void doubleRotateLeft(AVLNode *&parent);
    void rotateRight(AVLNode *&parent);
    void doubleRotateRight(AVLNode *&parent);
    void balance(AVLNode *&temp);
};

#endif // AVLTree_H
