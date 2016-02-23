#ifndef LISTNODE_H
#define LISTNODE_H

#include "docnode.h"

#include <list>
#include <string>

using namespace std;

class ListNode
{
private:
    list<DocNode*>* docList;

    string wordIndex;

    int count;

    DocNode* searchElement(int&);

public:
    ListNode(string&, int&);
    ListNode(string&, int&, int&, int&);

    ~ListNode();

    //Getters
    list<DocNode*>* getList();

    string getWord();

    int getCount() const;

    //Insert an element, or increment count value for it.
    void insertElement(int&);

    //Special insert, from permanent index
    void insertElement(int&,int&);

    string printList();
};

#endif // LISTNODE_H
