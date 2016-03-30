#include "OutputFile.h"

#include <algorithm>
#include <fstream>

using namespace std;

OutputFile::OutputFile(GraphColoring& graphColoring, string& outFilePath) : graphColoring_(graphColoring), outFilePath_(outFilePath){}

void OutputFile::computeStatistics()
{
    for(GraphColoring::iterator it = graphColoring_.begin(); it != graphColoring_.end(); ++it)
    {
        int actualColour = it->second;
        vector< pair<int, unsigned int> >::iterator findIt = find_if( coloursHistogram_.begin(), coloursHistogram_.end(), [&actualColour](const std::pair<int, unsigned int>& element){ return element.first == actualColour; } );
        if(findIt == coloursHistogram_.end())
        {
            pair<int, unsigned int> tmp (actualColour, 1U);
            coloursHistogram_.push_back(tmp);
        }
        else
        {
            findIt->second += 1U;
        }
    }
    return;
}

void OutputFile::generateOutput()
{
    computeStatistics();
    ofstream ofile(outFilePath_.c_str());
    ofile << "Liczba kolorów:  " << coloursHistogram_.size() << endl << endl;
    ofile << "kolor:  liczba wierzchołków" << endl;
    for(vector< pair<int, unsigned int> >::iterator it = coloursHistogram_.begin(); it != coloursHistogram_.end(); ++it)
    {
        ofile << it->first << ":  " << it->second << endl;
    }
    ofile << endl << "wierzchołek:  kolor" << endl;
    for(GraphColoring::iterator it = graphColoring_.begin(); it != graphColoring_.end(); ++it)
    {
        ofile << it->first << ":  " << it->second << endl;
    }
    ofile.close();
}
