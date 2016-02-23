//Created by Van Tran. Integrated by Jakob Wells

#include "hashtable.h"

HashTable::HashTable(int numindex)
{
    indices = numindex;
    table = new AVLTree[indices];
}

HashTable::~HashTable()
{
    delete[] table;
}

void HashTable::insert(string &word, int &id)
{
    table[getHash(word)].insert(word, id);
}

void HashTable::insert(ListNode* list)
{
    string word = list->getWord();
    table[getHash(word)].insert(list);
}


ListNode* HashTable::search(string &word)
{
    return table[getHash(word)].search(word);
}


size_t HashTable::getHash(string &word)
{
    std::hash<std::string> hasher;
    auto hashed = hasher(word);

    //cout << hashed << endl;

    return hashed%indices;
}

int HashTable::getUniqueCount()
{
    int uniqueWords = 0;

    for (int i = 0; i < indices; i++)
        uniqueWords += table[i].getUniqueCount();
    return uniqueWords;
}

string HashTable::printNodes()
{
    string output = "";
    for (int i=0; i < indices; i++)
        output += table[i].printNodes();
    return output;
}

void HashTable::compileNodes(vector<ListNode*> &nodeList)
{
    for (int i=0; i < indices; i++)
        table[i].compileNodes(nodeList);
}
