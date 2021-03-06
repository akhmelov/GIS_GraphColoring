#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <string>
#include <set>
#include <sstream>
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include "Structures.h"

class OutputFile
{
    public:
        std::string getOutput(GraphColoring &graphColoringSeq, GraphColoring &graphColoringInd, OutputInf &resultSequence, OutputInf &resultIndependent, long double timeAlg1 = -1, long double timeAlg2 = -1);
        std::string getSimpleOutput(GraphColoring &graphColoringSeq, OutputInf &result);
        std::string generateGraph(int vertexes, int edges);
    private:
        std::vector< std::pair<int, unsigned int> > computeStatistics(GraphColoring& graphColoring_, OutputInf &result);
        OutputInf generateFinalOutput(GraphColoring& graphColoring_, OutputInf &result);

        std::string myFill(int n = 10) { return std::string(n, ' ');}
};

#endif // OUTPUTFILE_H
