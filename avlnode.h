/* AVLNode holds the data for the AVL Tree
 *
 * Functions of the AVLNode class allow for creating new IndexEntry objects and accessing data
*/
#ifndef AVLNODE_H
#define AVLNODE_H
#include "indexentry.h"
using namespace std;

class AVLNode
{
friend class AVLTree;
private:
    AVLNode* left;
    AVLNode* right;
    long key;
    IndexEntry* entry;

public:
    AVLNode();
    AVLNode(long ky, string wrd, int pgNum);
    AVLNode(long ky, string wrd, int pgNum, int freq);
    ~AVLNode();

    long getKey();
    IndexEntry *&getIndexEntry();
};

#endif // AVLNODE_H
