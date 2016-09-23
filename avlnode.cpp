#include "avlnode.h"

// default cstr sets pointers to null
AVLNode::AVLNode(): left(NULL), right(NULL), key(0), entry(NULL){
}

// overloaded cstr for creating entries when storing from documents to structure
AVLNode::AVLNode(long ky, string wrd, int pgNum): left(NULL), right(NULL), key(ky){
    entry = new IndexEntry(wrd, pgNum);
}

// overloaded cstr for creating entries when storing from files to structure
AVLNode::AVLNode(long ky, string wrd, int pgNum, int freq): left(NULL), right(NULL), key(ky){
    entry = new IndexEntry(wrd, pgNum, freq);
}

// overloaded dstr
AVLNode::~AVLNode()
{
    delete entry;
}

long AVLNode::getKey()
{
    return key;
}

IndexEntry *&AVLNode::getIndexEntry()
{
    return entry;
}
