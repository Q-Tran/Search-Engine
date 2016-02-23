#ifndef INDEXERINTERFACE_H
#define INDEXERINTERFACE_H

#include "listnode.h"
#include <vector>

class IndexerInterface
{
public:
    IndexerInterface() {}

    virtual ~IndexerInterface() {}

    //Find an element in the index given a keyword.
    virtual ListNode* search(string&) = 0;

    //Insert a new page into the index (or increment an existing one).
    virtual void insert(string&, int&) = 0;

    //Insert a new list of pages to the index
    virtual void insert(ListNode*) = 0;

    //Get the number of unique words in the structure.
    virtual int getUniqueCount() = 0;

    virtual string printNodes() = 0;

    virtual void compileNodes(vector<ListNode*>&) = 0;
};

#endif // INDEXERINTERFACE_H
