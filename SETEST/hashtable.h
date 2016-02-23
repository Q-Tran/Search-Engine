#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "indexerinterface.h"
#include "avltree.h"

#include <functional>

class HashTable: public IndexerInterface
{
private:
    int indices;
    AVLTree* table;

    size_t getHash(string& word);
public:
    HashTable(int numindex);

    ~HashTable();

    void insert(string& arg, int& id);

    void insert(ListNode* list);

    ListNode* search(string& arg);

    int getUniqueCount();

    string printNodes();

    void compileNodes(vector<ListNode*>&);
};

#endif // HASHTABLE_H
