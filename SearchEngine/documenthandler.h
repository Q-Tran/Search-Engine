/* Jakob Wells | Search Engine | documenthandler.h | Decemeber 7th, 2015
 * History:
 * -Initial Design
 * -Added a way to save streampos map
 * -Added the ability to clear the map file
 */
#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <fstream>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

class DocumentHandler
{
private:
    struct FilePosHolder
    {
        streampos startPos;
        streampos queryPos;
        streampos endPos;

        FilePosHolder(streampos start, streampos query, streampos end)
        {
            startPos = start;
            queryPos = query;
            endPos = end;
        }
    };

    int fileCount;

    unordered_map<int,FilePosHolder*> posMap;

public:
    DocumentHandler(int);
    ~DocumentHandler();

    //Pass doc id, get string including info about it
    string getQuery(int);

    //Pass doc id, get query information plus text of the document
    string getFullText(int);

    //Pass doc id, author, date, and text strings, places it
    void addDocument(int, string, string, string, string);

    //Print out the streamposition map to a file
    void printPositions();

    //Read in a streamposition map from a file
    void readPositions();

    //Clear the persistent index
    void clearIndex();

};

#endif // DOCUMENTHANDLER_H
