/* Page stores the page number the associated index entry appears in and the frequency
 * of the term within the XML document
 *
 * Functions of the Page class allow for adding the two integers and increasing frequency
 * This is necessary for return most relevant documents a term appears in
*/
#ifndef PAGE_H
#define PAGE_H
#include <iostream>
#include <vector>
using namespace std;

class Page
{
private:
    int pageNum;
    int frequency;

public:
    Page();
    Page(int pgNum);
    Page(int pgNum, int freq);
    Page(const Page& other);
    Page& operator=(const Page &rhs);

    void setPageNum(int pgNum);
    int getPageNum() const;

    void increaseFrequency();
    int getFrequency();
    void totalFrequencies(int addedFreqs);
};

// overloaded comparison operator used for comparing Page objects when using iterator
inline bool operator==(const Page& lhs, const Page& rhs)
{
    // only need to check page numbers to determine match
    if(lhs.getPageNum() == rhs.getPageNum())
    {
        return true;
    }

    return false;
}

#endif // PAGE_H
