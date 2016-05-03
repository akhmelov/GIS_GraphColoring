#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "Structures.h"


using namespace std;

class InputFile
{
    public:
        Graph makeGraph(string path);
        string displayGraph(Graph &graph);

        InputFile();
        virtual ~InputFile();
    protected:
    private:
};

#endif // INPUTFILE_H
