#include "indexio.h"

IndexIO::IndexIO(IndexHandler* ind)
{
    index = ind;
}

void IndexIO::outputIndex()
{
    //cout << "Processing output!!!" << endl;
    string output = index->printNodes();

    ofstream fout("IndexOutput.txt");

    if (fout.is_open())
    {
        fout << index->getPageCount() << endl;
        fout << output;
    }
    else
    {
        cout << "Error writing file" << endl;
    }

    fout.close();
}

int IndexIO::inputIndex()
{
    ifstream fin("IndexOutput.txt");

    int pc;

    if (fin.is_open())
    {
        string pcStr;
        getline(fin,pcStr);
        pc = stoi(pcStr);

        string s;
        while (getline(fin,s))
        {
            stringstream ss(s);

            //First Node
            string word;
            getline(ss,word,'|');

            string wCntStr;
            int wCnt;
            getline(ss,wCntStr,'|');
            wCnt = stoi(wCntStr);

            string idStr;
            int id;
            getline(ss,idStr,'|');
            id = stoi(idStr);

            string countStr;
            int count;
            getline(ss,countStr,'|');
            count = stoi(countStr);

            ListNode* newNode = new ListNode(word,wCnt,id,count);

            while (getline(ss,idStr,'|'))
            {
                id = stoi(idStr);

                getline(ss,countStr,'|');
                count = stoi(countStr);

                newNode->insertElement(id,count);
            }
            //cout << word << endl;
            index->insert(newNode);
        }
    }
    else
    {
        cout << "Error reading file" << endl;
    }

    fin.close();

    return pc;
}

void IndexIO::clearIndex()
{
    remove("IndexOutput.txt");
}
