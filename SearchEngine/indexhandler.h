/* Jakob Wells | Search Engine | indexhandler.h | Decemeber 7th, 2015
 * History:
 * -Initial Design
 * -Added functionality for persistent index
 * -Added functionality for Top50 recall
 * -Changed seach to output list<DocNode*>*
 */
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

    int getInsertCount();
};

#endif // INDEXHANDLER_H
