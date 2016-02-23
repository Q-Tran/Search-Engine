#include "avltree.h"

AVLTree::AVLTree()
{
    root = nullptr;
    uniqueWords = 0;
}

AVLTree::~AVLTree()
{
    if (root != NULL)
        deleteNodes(root);
}

void AVLTree::deleteNodes(AvlNode* &t)
{
    AvlNode* temp = t->left;
    if (temp != NULL)
    {
        deleteNodes(temp);
    }

    temp = t->right;
    if (temp != NULL)
    {
        deleteNodes(temp);
    }

    delete t;
}

int AVLTree::height(AvlNode* &t)
{
    return t == nullptr ? -1 : t->height;
}

int AVLTree::max(int lhs, int rhs)
{
    return lhs > rhs ? lhs : rhs;
}

void AVLTree::insert(string& word, int& id)
{
    insert(word, id, root);
}

void AVLTree::insert(ListNode* list)
{
    insert(list, root);
}

void AVLTree::insert(string& word, int& id, AvlNode* &t)
{
    if (t == nullptr)
    {
        t = new AvlNode(word,id,nullptr,nullptr);
        uniqueWords++;
    }
    else if ( word < t->data->getWord()) //Left Case
    {
        insert(word, id, t->left);
        if (height(t->left) - height(t->right) == 2) //Case 1
        {
            if(word < t->left->data->getWord())
            {
                rotateWithLeftChild(t);
            }
            else //Case 2
            {
                doubleWithLeftChild(t);
            }
        }
    }
    else if ( word > t->data->getWord()) //Right Case
    {
        insert(word, id, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if(word > t->right->data->getWord())
            {
                rotateWithRightChild(t);
            }
            else
            {
                doubleWithRightChild(t);
            }
        }
    }
    else
    {
        t->data->insertElement(id);
    }

    t->height = max(height(t->left),height(t->right)) + 1;
    //cout << t->height << endl;
}


void AVLTree::insert(ListNode* list, AvlNode* &t)
{
    if (t == nullptr)
    {
        t = new AvlNode(list,nullptr,nullptr);
        uniqueWords++;
    }
    else if ( list->getWord() < t->data->getWord()) //Left Case
    {
        insert(list, t->left);
        if (height(t->left) - height(t->right) == 2) //Case 1
        {
            if(list->getWord() < t->left->data->getWord())
            {
                rotateWithLeftChild(t);
            }
            else //Case 2
            {
                doubleWithLeftChild(t);
            }
        }
    }
    else if ( list->getWord() > t->data->getWord()) //Right Case
    {
        insert(list, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if(list->getWord() > t->right->data->getWord())
            {
                rotateWithRightChild(t);
            }
            else
            {
                doubleWithRightChild(t);
            }
        }
    }
    else
    {
        //Should never have two of the same word. That would be a problem.
        cout << "WHAT DID YOU DO" << endl;
    }

    t->height = max(height(t->left),height(t->right)) + 1;
    //cout << t->height << endl;
}

void AVLTree::rotateWithLeftChild(AvlNode* &k2)
{
    AvlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left), height( k2->right)) + 1;
    k1->height = max( height( k1->left), k2->height) + 1;
    k2 = k1; //k2 is a reference to the pointer of the left hand node of parent
}

void AVLTree::rotateWithRightChild(AvlNode* &k1)
{
    AvlNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->right), height(k1->left)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2; //k1 is a reference to the pointer of the Right hand node of parent
}

void AVLTree::doubleWithLeftChild(AvlNode* &k3)
{
    rotateWithRightChild(k3->left);

    rotateWithLeftChild(k3);
}

void AVLTree::doubleWithRightChild(AvlNode* &k1)
{
    rotateWithLeftChild(k1->right);

    rotateWithRightChild(k1);
}

ListNode* AVLTree::search(string& word)
{
    return search(word, root);
}

ListNode* AVLTree::search(string& word, AvlNode* &t)
{
    if (t == nullptr)
    {
        return nullptr; //Reached bottom, no match
    }
    if (t->data->getWord() == word)
    {
        return t->data;
    }
    else if (t->data->getWord() > word)
    {
        return search(word,t->left);
    }
    else
    {
        return search(word,t->right);
    }
}

int AVLTree::getUniqueCount()
{
    return uniqueWords;
}

string AVLTree::printNodes()
{
    return printNodes(root);
}

string AVLTree::printNodes(AvlNode* &t)
{
    if (t == nullptr)
    {
        return "";
    }

    string output = "";

    if (t->left != nullptr)
    {
         output += printNodes(t->left);
    }

    output += t->data->printList();

    if (t->right != nullptr)
    {
        output += printNodes(t->right);
    }

    return output;
}

void AVLTree::compileNodes(vector<ListNode*> &nodeList)
{
    return compileNodes(nodeList, root);
}

void AVLTree::compileNodes(vector<ListNode*> &nodeList, AvlNode* &t)
{
    if (t == nullptr)
    {
        return;
    }

    if (t->left != nullptr)
    {
         compileNodes(nodeList,t->left);
    }

    nodeList.push_back(t->data);

    if (t->right != nullptr)
    {
        compileNodes(nodeList,t->right);
    }
}
