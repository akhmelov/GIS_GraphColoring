#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <sstream>
#include <string>
#include <fstream>

#include "Structures.h"


using namespace std;

class InputFile
{
    public:
        Graph makeGraph(string path);

        InputFile();
        virtual ~InputFile();
    protected:
    private:
};

#endif // INPUTFILE_H
