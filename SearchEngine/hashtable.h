/* Van Tran | Search Engine | hashtable.h | Decemeber 7th, 2015
 * History:
 * -Initial Design
 * -Added functionality for persistent index - Jakob Wells
 * -Added functionality for Top50 recall - Jakob Wells
 */
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
