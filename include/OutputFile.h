#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include "Structures.h"
#include <set>

class OutputFile
{
    public:
        OutputFile(GraphColoring& graphColoring, std::string& outFilePath);
        void generateOutput();

    private:
        GraphColoring& graphColoring_;
        std::string& outFilePath_;
        std::vector< std::pair<int, unsigned int> > coloursHistogram_;

        void computeStatistics();
};

#endif // OUTPUTFILE_H
