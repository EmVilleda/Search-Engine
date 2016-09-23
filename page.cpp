#include "page.h"

// default cstr
Page::Page(): pageNum(0), frequency(0){
}

// overloaded cstr: when a page number is added, frequency automatically set to 1
Page::Page(int pgNum): pageNum(pgNum), frequency(1){
}

// overloaded cstr: when a page number is added and its freq
Page::Page(int pgNum, int freq): pageNum(pgNum), frequency(freq){
}

// overloaded copy cstr
Page::Page(const Page& other ): pageNum(other.pageNum), frequency(other.frequency){
}

// overloaded assignment operator
Page& Page::operator=(const Page &rhs)
{
    // check for self-assignment
    if (this == &rhs)
        return *this;

    // do the copy
    pageNum = rhs.pageNum;
    frequency = rhs.frequency;

    // return the existing object
    return *this;
}

void Page::setPageNum(int pgNum)
{
    pageNum = pgNum;
}

int Page::getPageNum() const
{
    return pageNum;
}

// rather than set frequency, every time this is called
// increment frequency by 1
void Page::increaseFrequency()
{
    frequency++;
}

int Page::getFrequency()
{
    return frequency;
}

// adds the new frequency to the total frequency
void Page::totalFrequencies(int addedFreqs)
{
    frequency+=addedFreqs;
}
