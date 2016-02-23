#include "userinterface.h"

UserInterface::UserInterface()
{
    //Create an index with default "Hash Table" structure
    index = new IndexHandler(1);
    //Create a document handler that uses 100 files
    docIO = new DocumentHandler(100);
    //Create a parser with access to the index and document handler
    parse = new ParseHandler(index, docIO);
    //Create a querier with access to the index
    query = new QueryHandler(index);
    //Create an indexIO with access to the index
    indexio = new IndexIO(index);

    //Set some UI related variables
    indexType = 1;
    mistakeCount = 0;
    pageCount = 0;

}

UserInterface::~UserInterface()
{
    //Clear everything on the heap
    delete index;
    delete parse;
    delete query;
    delete docIO;
    delete indexio;
}

//For sorting by TfIdf values
bool compareTfIdf(DocNode* lt, DocNode* rt)
{
    if (lt->getTfIdf() > rt->getTfIdf())
        return true;
    return false;
}

bool UserInterface::fileExists(const char* filename)
{
  ifstream ifile(filename);
  return ifile;
}

void UserInterface::misSelectOut()
{
    mistakeCount++;

    cout << endl << "Please make a valid selection\n" << endl;

    if (mistakeCount == 25)
        cout << "You're doing this on purpose, aren't you?" << endl;
    if (mistakeCount == 20)
        cout << "Please stop this and use the program how you're supposed to" << endl;
    if (mistakeCount == 15)
        cout << "Really? Come on, its not that hard" << endl;
    if (mistakeCount == 10)
        cout << "Slow down, its not a contest, choose with a bit more care." << endl;
    if (mistakeCount == 5)
        cout << "Pencils have their erasers, search engines have witty error codes" << endl;
    cout << endl << endl;
}

void UserInterface::clearIndex()
{
    delete index;
    docIO->clearIndex();
    indexio->clearIndex();
    index = new IndexHandler(indexType);
    pageCount = 0;
}

//The User Interface proper. Consists of nested while loops mostly, with some
//additional logic to keep the user out of some areas before the index is loaded
int UserInterface::startInterface()
{
    //Variables for lock/unlocking different functionality
    bool indexLoaded = false; //Makes sure you don't query an empty index

    cout << "Welcome to the Mustang Search Engine!"
         << "\n(C) Jakob Wells & Van Tran, 2015" << endl;

    //Check for the persistent index
    if (fileExists("IndexOutput.txt"))
    {
        //Load select menu
        while (true)
        {
            cout << "A persistent index has been detected. How would you like to load this index?"
                 << endl << "Type -1- to load the index into an AVLTree"
                 << endl << "Type -2- to load the index into a Hash Table"
                 << endl << ">>> ";
            string s;
            cin >> s;

            if (s == "1")
            {
                delete index;
                index = new IndexHandler(0);
                indexType = 0;
                break;
            }
            else if (s == "2")
            {
                delete index;
                index = new IndexHandler(1);
                indexType = 1;
                break;
            }
            else
            {
                misSelectOut();
            }
        }

        pageCount = indexio->inputIndex();
        index->setPageCount(pageCount);
        docIO->readPositions();
        indexLoaded = true;
    }


    //The real meat of the UI. The MAIN MENU!
    while (true)
    {
        cout << "Please make a selection: "
             << endl << "Type -1- to access the MAINTENANCE MENU"
             << endl << "Type -2- to access the INTERACTIVE MENU"
             << endl << "Type -3- to EXIT"
             << endl << ">>> ";
        string s;
        cin >> s;

        if (s == "1")
        {
            //Maintenance Menu
            while(true)
            {
                cout << "Please make a selection: "
                     << endl << "Type -1- to ADD A NEW DOCUMENT"
                     << endl << "Type -2- to CLEAR THE INDEX"
                     << endl << "Type -3- to EXIT to the MAIN MENU"
                     << endl << ">>> ";

                string c;
                cin >> c;

                if (c == "1")
                {
                    //Add a document to the index
                    cout << "Please type the filename of the xml doc you'd like to add"
                         << endl << "Example: \"filename.xml\""
                         << endl << ">>> ";

                    string x;
                    cin >> x;

                    parse->parse(x);
                    pageCount += parse->getPageCount();
                    index->setPageCount(pageCount);
                    indexio->outputIndex();
                    docIO->printPositions();

                    indexLoaded = true;
                    cout << "New file parsing complete" << endl;
                }

                else if (c == "2")
                {
                    while(true)
                    {
                        //Double check if you want to clear the index.
                        cout << "Do you really want to clear the index?" << endl
                             << "This will clear the persistent index as well!"
                             << endl << "Type -1- to continue"
                             << endl << "Type -2- to EXIT to the MAINTENANCE MENU"
                             << endl << ">>> ";

                        string x;
                        cin >> x;

                        if (x == "1")
                        {
                            clearIndex();
                            indexLoaded = false;
                            cout << "Index has been cleared" << endl;
                            break;
                        }

                        else if (x == "2")
                        {
                            break;
                        }

                        else
                        {
                            misSelectOut();
                        }
                    }
                }

                else if (c == "3")
                {
                    break;
                }

                else
                {
                    misSelectOut();
                }
            }
        }

        else if (s == "2")
        {
            if (indexLoaded)
            {
            //Interactive Menu
            while(true)
            {
                cout << "Please make a selection: "
                     << endl << "Type -1- to SWITCH THE INDEX STRUCTURE"
                     << endl << "Type -2- to MAKE A QUERY"
                     << endl << "Type -3- to SEE STATISTICS"
                     << endl << "Type -4- to EXIT to the MAIN MENU"
                     << endl << ">>> ";

                string c;
                cin >> c;

                if (c == "1")
                {
                //Switch the structure
                    while(true)
                    {
                        if (indexType == 0)
                            cout << "You are currently using an AVL Tree structure\n";
                        else
                            cout << "You are currently using a Hash Table structure\n";
                        cout << "Would you like to switch structures?"
                             << endl << "Type -1- to SWITCH STRUCTURES"
                             << endl << "Type -2- to EXIT to the INTERACTIVE MENU"
                             << endl << ">>> ";

                        string x;
                        cin >> x;

                        if (x == "1")
                        {
                            if (indexType == 0)
                            {
                                delete index;
                                index = new IndexHandler(1);

                                pageCount = indexio->inputIndex();
                                index->setPageCount(pageCount);
                                indexType = 1;
                            }
                            else if (indexType == 1)
                            {
                                delete index;
                                index = new IndexHandler(0);

                                pageCount = indexio->inputIndex();
                                index->setPageCount(pageCount);
                                indexType = 0;
                            }

                            cout << "Index structure switched" << endl;
                            break;
                        }

                        else if (x == "2")
                        {
                            break;
                        }

                        else
                        {
                            misSelectOut();
                        }
                    }
                }

                else if (c == "2")
                {
                    //Querier
                    cout << "Please type an acceptable boolean query:"
                         << endl << "You query may be prefixed by AND or OR,"
                         << endl << "and may be suffixed by NOT, followed by a term."
                         << endl << "Example : \"AND search engine NOT java\""
                         << endl << ">>> ";

                    string x;
                    cin.ignore();
                    getline(cin, x);
                    cout << endl << "Searching for: " << x << endl;

                    list<DocNode*>* temp = query->makeQuery(x);
                    cout << "Query completed:" << endl << endl;

                    if (temp->empty())
                        cout << "Query returned no results" << endl;
                    else
                    {

                        //Number of elements to output.
                        int n = 15;
                        //Sort the docs by TfIdf
                        temp->sort(compareTfIdf);

                        for(list<DocNode*>::iterator it = temp->begin(); it != temp->end() && n > 0; ++it, --n)
                        {
                            cout << "Document Number " << (16 - n) << ":" << endl;
                            cout << docIO->getQuery((*it)->getID()) << "TfIdf value: " <<  (*it)->getTfIdf() << endl << endl;
                        }

                        while (true)
                        {
                            cout << "If you would like to see the full text of"
                                 << endl << " one of the documents above, enter a number from"
                                 << endl << " -1- to -" << (15 - n) << "- corresponding to the doc"
                                 << endl << " you would like to see. Or enter -0- to exit."
                                 << endl << ">>> ";
                            string v;
                            cin >> v;

                            if (v == "0")
                            {
                                break;
                            }
                            else if (stoi(v) > 0 && stoi(v) <= (16-n))
                            {
                                list<DocNode*>::iterator it = temp->begin();
                                for(int x = 1; x < stoi(v); ++x)
                                    ++it;
                                cout << docIO->getFullText((*it)->getID()) << endl;
                            }
                            else
                            {
                                misSelectOut();
                            }
                        }
                    }

                    delete temp;
                }
                else if (c == "3")
                {
                    cout << "Basic statistics for the Search Engine:" << endl
                         << endl << "Total number of Pages indexed: "
                         << to_string(index->getPageCount()) << endl
                         <<  "Total number of unique Words: "
                         << to_string(index->getUniqueCount()) << endl
                         << "Top 50 Words (by total inserts): " << endl
                         << index->printTopWords() << endl;
                }

                else if (c == "4")
                {
                    break;
                }
                else
                {
                    misSelectOut();
                }
            }
            }
            else
            {
                cout << "Please insert data into the index before you try to access it" << endl;
            }
        }

        else if (s == "3")
        {
            //Exit the program
            cout << "Thank you for using the Mustang Search Engine!"
                 << endl << "Please have a nice day!" << endl;
            if (indexLoaded)
            {
                indexio->outputIndex();
                docIO->printPositions();
            }


            break;
        }

        else
        {
            misSelectOut();
        }
    }

    return 0;
}
