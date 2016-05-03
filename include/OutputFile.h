#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <string>
#include <set>
#include <sstream>

#include "Structures.h"

class OutputFile
{
    public:
        std::string getOutput(GraphColoring &graphColoringSeq, GraphColoring &graphColoringInd);
        void writeOutputToFile();

    private:
        //GraphColoring& graphColoring_;
        //std::string& outFilePath_;
        //std::vector< std::pair<int, unsigned int> > coloursHistogram_;

        std::vector< std::pair<int, unsigned int> > computeStatistics(GraphColoring& graphColoring_);
        OutputInf generateFinalOutput(GraphColoring& graphColoring_);

        std::string myFill(int n = 10) { return std::string(n, ' ');}
};

#endif // OUTPUTFILE_H
