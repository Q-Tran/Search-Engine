#include "listnode.h"

ListNode::ListNode(string &word, int &index)
{
    docList = new list<DocNode*>;
    wordIndex = word;

    DocNode* newNode = new DocNode(index);
    docList->push_front(newNode);

    count = 1;
}

ListNode::ListNode(string &word, int &wCnt, int &index, int &indCnt)
{
    docList = new list<DocNode*>;
    wordIndex = word;

    DocNode* newNode = new DocNode(index,indCnt);
    docList->push_front(newNode);

    count = wCnt;
}

ListNode::~ListNode()
{
    for(list<DocNode*>::iterator it = docList->begin(); it != docList->end(); ++it)
    {
        delete (*it);
    }
    delete docList;
}

list<DocNode*>* ListNode::getList()
{
    return docList;
}

string ListNode::getWord()
{
    return wordIndex;
}

int ListNode::getCount() const
{
    return count;
}

void ListNode::insertElement(int &id)
{
    DocNode* temp = *(docList->begin());

    if(temp->getID() != id)
    {
        DocNode* newNode = new DocNode(id);
        docList->push_front(newNode);
    }
    else
    {
        temp->increaseCount();
    }

    count++;
}

void ListNode::insertElement(int &id, int &idCnt)
{
    DocNode* newNode = new DocNode(id,idCnt);
    docList->push_front(newNode);
}

DocNode* ListNode::searchElement(int &id)
{
    for(list<DocNode*>::iterator it = docList->begin(); it != docList->end(); ++it)
    {
        if ((*it)->getID() == id)
        {
            return &**it;
        }
    }
    return nullptr;
}

string ListNode::printList()
{
    string output = getWord() + "|" + to_string(getCount());

    for(list<DocNode*>::iterator it = docList->begin(); it != docList->end(); ++it)
    {
        output += "|" + to_string((*it)->getID()) + "|" + to_string((*it)->getCount());
    }
    return output + "\n";
}
