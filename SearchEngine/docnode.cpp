#include "docnode.h"

//Create a new node with a count of 1 and a default tfIdf value
DocNode::DocNode(int& id)
{
    docID = id;
    docCount = 1;
    tfIdf = 0.0;
}

//Create a new node with a preset count
DocNode::DocNode(int& id, int& count)
{
    docID = id;
    docCount = count;
    tfIdf = 0.0;
}

//Retrieve the id of the document
int DocNode::getID()
{
    return docID;
}

//Retrieve the count that the word appears in the document
int DocNode::getCount()
{
    return docCount;
}

//Increase the count that the word appears by 1
void DocNode::increaseCount()
{
    docCount++;
}

//Set the TfIdf value given the idf value of the word
void DocNode::setTfIdf(double idf)
{
    tfIdf = (docCount * idf);
}

//Retrieve the TfIdf value
double DocNode::getTfIdf()
{
    return tfIdf;
}

//Combine the values of a given node with this one, effectively merging the nodes
void DocNode::mergeNode(DocNode* rt)
{
    tfIdf += rt->getTfIdf();
}
