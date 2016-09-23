#include "avltree.h"

AVLTree::AVLTree() : Index(), root(NULL){
}

AVLTree::~AVLTree()
{
    makeEmpty(root);
}

// =============== Virtual Functions (from Index) ===============
void AVLTree::addEntry(long qKey, string wrd, int pgNum)
{
    long key = (abs(qKey) % 2000000);
    insert(root, key, wrd, pgNum);
}

void AVLTree::addEntryWithFreq(long qKey, string wrd, int pgNum, int freq)
{
    long key = (abs(qKey) % 2000000);
    insertWithFreq(root, key, wrd, pgNum, freq);
}

IndexEntry *AVLTree::findEntry(long qKey)
{
    // do not try searching if root is NULL (AVL Tree hasn't been built)
    if(root == NULL)
    {
        return NULL;
    }

    long key = (abs(qKey) % 2000000);
    AVLNode* found = search(root, key);

    if(found)
    {
        return found->getIndexEntry();
    }
    else
    {
        return NULL;
    }
}

void AVLTree::clearIndex()
{
    if(root != NULL)
    {
        makeEmpty(root);
    }
}

bool AVLTree::isIndexEmpty() const
{
    return root == NULL;
}

void AVLTree::printContents(ofstream &indexFile)
{
    traversal(root, indexFile);
}

// =============== AVLTree Functions ===============
void AVLTree::makeEmpty(AVLNode* &rt)
{
    if(rt != NULL)
    {
        makeEmpty(rt->left);
        makeEmpty(rt->right);
        delete rt;
        rt = NULL;
    }
}

// makes comparisons to node values to help determine to go left, right, or neither
int AVLTree::compare(long key1, long key2)
{
    if(key1 == key2)
    {
        return EQ;
    }
    else if(key1 < key2)
    {
        return LEFT;
    }
    else
        return RIGHT;
}

// insert new IndexEntry in tree or add page number to an already added entry
// use when storing from documents to structure
void AVLTree::insert(AVLNode *&rt, long ky, string wrd, int pgNum)
{
    // create new node when tree is empty
    if(rt == NULL)
    {
        rt = new AVLNode(ky, wrd, pgNum);
    }
    // traverse down to left subtree
    else if(compare(ky, rt->key) == LEFT)
    {
        insert(rt->left, ky, wrd, pgNum);
    }
    // traverse down to right subtree
    else if(compare(ky, rt->key) == RIGHT)
    {
        insert(rt->right, ky, wrd, pgNum);
    }
    // if there is already an existing node with the same value, add new page number
    else
    {
        rt->getIndexEntry()->addPageEntry(pgNum);
    }

    // balance tree once insertion has been made
    balance(rt);
}

// insert new IndexEntry in tree or add page number to an already added entry
// use when storing from file to structure
void AVLTree::insertWithFreq(AVLNode *&rt, long ky, string wrd, int pgNum, int freq)
{
    // create new node when tree is empty
    if(rt == NULL)
    {
        rt = new AVLNode(ky, wrd, pgNum, freq);
    }
    // traverse down to left subtree
    else if(compare(ky, rt->key) == LEFT)
    {
        insertWithFreq(rt->left, ky, wrd, pgNum, freq);
    }
    // traverse down to right subtree
    else if(compare(ky, rt->key) == RIGHT)
    {
        insertWithFreq(rt->right, ky, wrd, pgNum, freq);
    }
    // if there is already an existing node with the same value, add new page number
    else
    {
        rt->getIndexEntry()->addPageEntryWithFreq(pgNum, freq);
    }

    // balnace tree once insertion has been made
    balance(rt);
}

// traverses through tree in order to find matching value
AVLNode *AVLTree::search(AVLNode *&rt, long ky)
{
    // initializing to avoid conflicting with while condition
    int result = 2;
    while(rt != NULL && result != EQ)
    {
        result = compare(ky, rt->key);

        if(result == LEFT)
        {
            rt = rt->left;
        }
        else if(result == RIGHT)
        {
            rt = rt->right;
        }
    }

    // returns root or NULL if that node doesn't exist
    return rt;
}

// traverses through tree and writes data to index file on disk
void AVLTree::traversal(AVLNode *&rt, std::ofstream &indexFile)
{
    if(rt != NULL)
    {
        traversal(rt->left, indexFile);
        traversal(rt->right, indexFile);

        indexFile << rt->getIndexEntry()->getWord() << " = ";
        stringstream pages;
        for(int i = 0; i < int(rt->getIndexEntry()->getPageList().size()); i++)
        {
            pages << "d" << rt->getIndexEntry()->getPageList()[i].getPageNum() << " [" << rt->getIndexEntry()->getPageList()[i].getFrequency() << "]";
            if(i+1 != int(rt->getIndexEntry()->getPageList().size()))
            {
                pages << ", ";
            }
            if((pages.tellp() >= 130 && pages.tellp() < 145))
            {
                if(i+1 != int(rt->getIndexEntry()->getPageList().size()))
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

// calculate the height of a node based on its left and right children
int AVLTree::height(AVLNode* temp)
{
    int ht = 0;

    if (temp != NULL)
    {
        ht = max(height(temp->left), height(temp->right)) + 1;
    }

    return ht;
}

// returns the height difference
int AVLTree::difference(AVLNode *temp)
{
    return height(temp->left) - height(temp->right);
}

// single left rotation
void AVLTree::rotateLeft(AVLNode *&parent)
{
    AVLNode* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    parent = temp;
}

// right left rotation (double)
void AVLTree::doubleRotateLeft(AVLNode *&parent)
{
    rotateRight(parent->left);
    rotateLeft(parent);
}

// single right rotation
void AVLTree::rotateRight(AVLNode *&parent)
{
    AVLNode* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    parent = temp;
}

// left right rotation (double)
void AVLTree::doubleRotateRight(AVLNode *&parent)
{
    rotateLeft(parent->right);
    rotateRight(parent);
}

// determines whether the tree needs to be rotated (and if so, how)
void AVLTree::balance(AVLNode *&temp)
{
    int balFactor = difference(temp);

    if (balFactor > 1)
    {
        if (difference(temp->left) > 0)
        {
            rotateLeft(temp);
        }
        else
        {
            doubleRotateLeft(temp);
        }
    }
    else if(balFactor < -1)
    {
        if (difference(temp->right) < 0)
        {
            rotateRight(temp);
        }
        else
        {
            doubleRotateRight(temp);
        }
    }
}
