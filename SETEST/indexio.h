#ifndef INDEXIO_H
#define INDEXIO_H

#include "indexhandler.h"
#include <fstream>
#include <sstream>
#include <cstdio>

class IndexIO
{
private:
    IndexHandler* index;

public:
    IndexIO(IndexHandler* index);

    void outputIndex ();

    int inputIndex ();

    void clearIndex();
};

#endif // INDEXIO_H
