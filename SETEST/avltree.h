#ifndef AVLTREE_H
#define AVLTREE_H

#include "indexerinterface.h"
#include <vector>

class AVLTree: public IndexerInterface
{
private:
    struct AvlNode
    {
        ListNode* data;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode(string& word, int& id, AvlNode* lt, AvlNode* rt)
        {
            data = new ListNode(word, id);
            left = lt;
            right = rt;
            height = 0;
        }
        AvlNode(ListNode* list, AvlNode* lt, AvlNode* rt)
        {
            data = list;
            left = lt;
            right = rt;
            height = 0;
        }

        ~AvlNode()
        {
            delete data;
        }
    };

    AvlNode* root;

    int uniqueWords;

    int height(AvlNode*&);

    int max(int, int);

    void rotateWithLeftChild(AvlNode* &k2);
    void rotateWithRightChild(AvlNode* &k1);
    void doubleWithLeftChild(AvlNode* &k3);
    void doubleWithRightChild(AvlNode* &k1);

    void insert(string&, int&, AvlNode* &t);

    void insert(ListNode*, AvlNode* &t);

    void deleteNodes(AvlNode* &t);

    ListNode* search(string&, AvlNode* &t);

    string printNodes(AvlNode* &t);

    void compileNodes(vector<ListNode*>&, AvlNode* &t);

public:
    //Default Constructor
    AVLTree();

    //Destuctor
    ~AVLTree();

    //Find an element in the index given a keyword.
    ListNode* search(string&);

    //Insert a new page into the index (or increment an existing one).
    void insert(string&, int&);

    void insert(ListNode*);

    int getUniqueCount();

    string printNodes();

    void compileNodes(vector<ListNode*>&);
};

#endif // AVLTREE_H
