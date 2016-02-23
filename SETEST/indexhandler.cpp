#include "indexhandler.h"

IndexHandler::IndexHandler(int type)
{
    if (type == 0)
    {
        index = new AVLTree();
    }
    else
    {
        index = new HashTable(100000);
    }

    inserts = 0;
    curId = 0;
}

IndexHandler::~IndexHandler()
{
    delete index;
}

void IndexHandler::addDocId(int &id)
{
    curId = id;
}

void IndexHandler::insert(string &word)
{
    inserts++;
    index->insert(word,curId);
}

void IndexHandler::insert(ListNode* t)
{
    inserts++;
    index->insert(t);
}

bool compareDocs(DocNode* lt, DocNode* rt)
{
    if (lt->getID() < rt->getID())
        return true;
    return false;
}

list<DocNode*>* IndexHandler::search(string &word)
{
    ListNode* temp = index->search(word);
    list<DocNode*>* docList;

    if (temp == nullptr)
    {
        //return empty list
        docList = new list<DocNode*>;
        return docList;
    }
    else
    {
        //Set list to queried list, sort it, and return it
        docList = index->search(word)->getList();

        docList->sort(compareDocs);

        double idf = log10 (float(pageCount) / float(docList->size()));
        for(list<DocNode*>::iterator it = docList->begin(); it != docList->end(); ++it)
        {
            (*it)->setTfIdf(idf);
        }
    }
    return docList;
}

int IndexHandler::getInsertCount()
{
    return inserts;
}

int IndexHandler::getUniqueCount()
{
    return index->getUniqueCount();
}

string IndexHandler::printNodes()
{
    return index->printNodes();
}

bool compareNodes(ListNode* lt, ListNode* rt)
{
    if (lt->getCount() > rt->getCount())
        return true;
    return false;
}

string IndexHandler::printTopWords()
{
    //Compile a list of all words in structure
    vector<ListNode*> wordList;
    index->compileNodes(wordList);

    //Sort by total insert count
    sort(wordList.begin(),wordList.end(),compareNodes);

    //Build output string
    string topFifty = "";
    for (unsigned int i = 0; i < 50; i++)
    {
        if (i % 5 == 0 && i != 0)
            topFifty += "\n";

        topFifty += wordList[i]->getWord() + " | ";

        if (i > wordList.size())
        {
            break;
        }
    }

    return topFifty;
}

void IndexHandler::setPageCount(int pages)
{
    pageCount = pages;
}

int IndexHandler::getPageCount()
{
    return pageCount;
}
