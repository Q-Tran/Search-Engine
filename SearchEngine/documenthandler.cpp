#include "documenthandler.h"

DocumentHandler::DocumentHandler(int numbFiles)
{
    fileCount = numbFiles;
}

DocumentHandler::~DocumentHandler()
{
    for (unordered_map<int,FilePosHolder*>::iterator it = posMap.begin(); it != posMap.end(); ++it)
    {
        delete it->second;
    }
}

string DocumentHandler::getFullText(int id)
{
    string output = "";

    fstream fin(( to_string(id%fileCount) + ".txt"), ios::in);

    if (fin.is_open())
    {
        fin.seekg(posMap.find(id)->second->startPos);

        streampos end = posMap.find(id)->second->endPos;

        while (fin.tellg() < end)
        {
            string newLine;

            getline(fin,newLine);

            output += newLine + "\n";
        }

        fin.close();
    }
    else
    {
        cout << "Error reading file" << endl;
    }

    return output;
}

string DocumentHandler::getQuery(int id)
{
    string output = "";

    fstream fin(( to_string(id%fileCount) + ".txt"), ios::in);

    if (fin.is_open())
    {
        fin.seekg(posMap.find(id)->second->startPos);

        streampos query = posMap.find(id)->second->queryPos;

        while (fin.tellg() < query)
        {
            string newLine;

            getline(fin,newLine);

            output += newLine + "\n";
        }

        fin.close();
    }
    else
    {
        cout << "Error reading file" << endl;
    }

    return output;
}

void DocumentHandler::addDocument(int id, string title, string author, string date, string text)
{
    fstream fout(( to_string(id%fileCount) + ".txt"), ios::out | ios::app);

    if (fout.is_open())
    {
        streampos start = fout.tellg();

        fout << title << endl;
        fout << author << endl;
        fout << date << endl;

        streampos query = fout.tellg();

        fout << text << endl;

        streampos end = fout.tellg();

        fout << endl;

        FilePosHolder* newPos = new FilePosHolder(start, query, end);

        posMap.insert({id,newPos});

        fout.close();
    }
    else
    {
        cout << "Error writing file" << endl;
    }

}

void DocumentHandler::printPositions()
{
    ofstream fout("PositionMap.txt");

    if (fout.is_open())
    {
        for (unordered_map<int,FilePosHolder*>::iterator it = posMap.begin(); it != posMap.end(); ++it)
        {
            fout << it->first << '|' << it->second->startPos << '|' << it->second->queryPos << '|' << it->second->endPos << '\n';
        }
    }
    else
    {
        cout << "Error writing file" << endl;
    }

    fout.close();
}

void DocumentHandler::readPositions()
{
    ifstream fin("PositionMap.txt");

    if (fin.is_open())
    {
        string s;
        while (getline(fin,s))
        {
            stringstream ss(s);

            string idStr;
            getline(ss,idStr,'|');
            int id = stoi(idStr);

            string startStr;
            getline(ss,startStr,'|');
            int start = stoi(startStr);

            string queryStr;
            getline(ss,queryStr,'|');
            int query = stoi(queryStr);

            string endStr;
            getline(ss,endStr,'|');
            int end = stoi(endStr);

            FilePosHolder* newPos = new FilePosHolder(start, query, end);

            posMap.insert({id,newPos});
        }
        fin.close();
    }
    else
    {
        cout << "Error reading file" << endl;
    }

    fin.close();
}

void DocumentHandler::clearIndex()
{
    for (int i = 0; i < fileCount; i++)
    {
        string s = to_string(i) + ".txt";
        remove(s.c_str());
    }

    remove("PositionMap.txt");
}
