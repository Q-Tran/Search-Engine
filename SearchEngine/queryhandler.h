/* Van Tran | Search Engine | queryhandler.h | Decemeber 7th, 2015
 * History:
 * -Initial Design
 * -Various bugfixes
 */
#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H

#include "indexhandler.h"
#include "stemmer.h"
#include "docnode.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

class QueryHandler{
private:
    IndexHandler* Indexer;
public:
    QueryHandler(IndexHandler*);
    list<DocNode*>* makeQuery(std::string);
};


#endif
