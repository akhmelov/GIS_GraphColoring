#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <string>
#include <set>
#include <sstream>

#include "Structures.h"

class OutputFile
{
    public:
        OutputFile(GraphColoring& graphColoring, std::string& outFilePath);
        void generateOutput();
        OutputInf generateFinalOutputStr();

    private:
        GraphColoring& graphColoring_;
        std::string& outFilePath_;
        std::vector< std::pair<int, unsigned int> > coloursHistogram_;

        void computeStatistics();
};

#endif // OUTPUTFILE_H
