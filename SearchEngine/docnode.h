/* Jakob Wells | Search Engine | DocNode.h | Decemeber 7th, 2015
 * History:
 * -Initial Design
 * -Added functionality for persistent index
 * -Added TfIdf values
 */

#ifndef DOCNODE_H
#define DOCNODE_H

#include <iostream>

class DocNode
{
private:

    int docID;
    int docCount;
    double tfIdf;

public:
    //Create a new node with a count of 1
    DocNode(int&);

    //Create a new node with a preset count
    DocNode(int&,int&);

    //Retrieve the id of the document
    int getID();

    //Retrieve the count of a word's appearance in the document
    int getCount();

    //Retrieve the TfIdf value
    double getTfIdf();

    //Increase the count of a word on this page
    void increaseCount();

    //Set the TfIdf value given the idf value of the word
    void setTfIdf(double idf);

    //Add the docCount and tfIdf of a node to this node, effectively merging them
    void mergeNode (DocNode* rt);
};

#endif // DOCNODE_H
