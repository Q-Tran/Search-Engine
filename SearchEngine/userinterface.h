/* Jakob Wells | Search Engine | userinterface.h | Decemeber 7th, 2015
 * History:
 * -Initial Design
 * -Various Bugfixes - Jakob Wells, Van Tran
 */
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "indexhandler.h"
#include "parsehandler.h"
#include "queryhandler.h"
#include "documenthandler.h"
#include "indexio.h"

class UserInterface
{
private:
    IndexHandler* index;
    ParseHandler* parse;
    QueryHandler* query;
    DocumentHandler* docIO;
    IndexIO* indexio;

    int pageCount;
    int indexType;
    int mistakeCount;

    bool fileExists(const char*);

    void misSelectOut();

    void clearIndex();

public:
    UserInterface();
    ~UserInterface();

    //Basic-overarching UI. Handles the basic operation of the program
    int startInterface();

};

#endif // USERINTERFACE_H
