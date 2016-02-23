/* Van Tran | Search Engine | parsehandler.h | Decemeber 7th, 2015
 * History:
 * -Initial Design
 * -Added stemming and stop words
 * -Added output to DocumentHandler
 */
#ifndef PARSEHANDLER_H
#define PARSEHANDLER_H

#include "indexhandler.h"
#include "stemmer.h"
#include "documenthandler.h"

#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "rapidxml.hpp"
class ParseHandler
{
private:

    IndexHandler* index;
    DocumentHandler* docIO;

    unordered_map<string,int>* stopWords;
    unordered_map<string,string>* stemWords;

    int pageCount;

public:
    ParseHandler(IndexHandler*, DocumentHandler*);
    void parse(string);

    int getPageCount();
};

#endif // PARSEHANDLER_H
