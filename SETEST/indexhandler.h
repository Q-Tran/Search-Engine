#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "avltree.h"
#include "hashtable.h"

#include <algorithm>
#include <cmath>

class IndexHandler
{
private:
    IndexerInterface* index;

    int inserts;
    int curId;
    int pageCount;

public:
    int getInsertCount();

    IndexHandler(int);

    ~IndexHandler();

    void addDocId(int&);

    void insert(string&);

    void insert(ListNode* t);

    list<DocNode*>* search(string&);

    int getUniqueCount();

    string printNodes();

    string printTopWords();

    void setPageCount(int);
    int getPageCount();
};

#endif // INDEXHANDLER_H
