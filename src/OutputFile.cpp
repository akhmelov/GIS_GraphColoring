#include "OutputFile.h"

#include <algorithm>
#include <fstream>

using namespace std;

std::vector< std::pair<int, unsigned int> > OutputFile::computeStatistics(GraphColoring& graphColoring_)
{
    std::vector< std::pair<int, unsigned int> > coloursHistogram_;
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
    return coloursHistogram_;
}

OutputInf OutputFile::generateFinalOutput(GraphColoring& graphColoring_)
{
    OutputInf outInf;
    std::vector< std::pair<int, unsigned int> > coloursHistogram_ = computeStatistics(graphColoring_);
    outInf.numberOfColors = coloursHistogram_.size();
    for(vector< pair<int, unsigned int> >::iterator it = coloursHistogram_.begin(); it != coloursHistogram_.end(); ++it)
    {
        outInf.countColorUsing[it->first] = it->second;
    }
    return outInf;
}

std::string OutputFile::getOutput(GraphColoring &graphColoringSeq, GraphColoring &graphColoringInd, long double timeAlg1, long double timeAlg2)
{
    std::stringstream ss;
    OutputInf resultSequence = generateFinalOutput(graphColoringSeq);
    OutputInf resultIndependent = generateFinalOutput(graphColoringInd);
    ss << endl;
    ss << myFill() << "Sequence" << myFill() << "|" << myFill() << "Independent" << myFill() << endl;
    ss << myFill() << "        " << myFill() << "|" << myFill() << "           " << myFill() << endl;
    ss << myFill() << "" << myFill(9) << "Czas wykonania" << myFill(9) << "" << myFill() << endl;
    ss << myFill() << timeAlg1 << myFill(17) << "|" << myFill() << timeAlg2 << myFill() << endl;
    ss << myFill() << "" << myFill(9) << "Liczba kolorow uzytych" << myFill(9) << "" << myFill() << endl;
    ss << myFill() << resultSequence.numberOfColors << myFill(17) << "|" << myFill() << resultIndependent.numberOfColors << myFill() << endl;
    ss << myFill() << "" << myFill(9) << "kolor:  liczba wierzchołków" << myFill(9) << "" << myFill() << endl;
    for(map<int, int>::iterator it1 = resultSequence.countColorUsing.begin(), it2 = resultIndependent.countColorUsing.begin();
        it1 != resultSequence.countColorUsing.end() || it2 != resultIndependent.countColorUsing.end();) {
        if(it1 != resultSequence.countColorUsing.end())
            { ss << myFill() << it1 -> first << ": " << it1 -> second << myFill(14); it1++; }
        else
            ss << myFill() << "        " << myFill();
        ss << "|";
        if(it2 != resultIndependent.countColorUsing.end())
            { ss << myFill() << it2 -> first << ": " << it2 -> second << myFill(14); it2++; }
        else
            ss << myFill() << "        " << myFill();
        ss << endl;
    }

    ss << myFill() << "" << myFill(9) << "wierzchołek:  kolor" << myFill(9) << "" << myFill() << endl;
    for(map<int, int>::iterator it1 = graphColoringSeq.begin(), it2 = graphColoringInd.begin();
        it1 != graphColoringSeq.end() || it2 != graphColoringInd.end();) {
        if(it1 != graphColoringSeq.end())
            { ss << myFill() << it1 -> first << ": " << it1 -> second << myFill(14); it1++; }
        else
            ss << myFill() << "        " << myFill();
        ss << "|";
        if(it2 != graphColoringInd.end())
            { ss << myFill() << it2 -> first << ": " << it2 -> second << myFill(14); it2++; }
        else
            ss << myFill() << "        " << myFill();
        ss << endl;
    }
    return ss.str();
}

std::string OutputFile::generateGraph(int vertexes, int edges)
{
    std::stringstream ss;
    std::list<pair<int, int>> graph;
    for(int i = 1; i < vertexes; i++){ //generate simple graph
        graph.push_back(make_pair(i, i + 1));
        edges--;
    }

    for(int i = 1; i < vertexes; i++){ //generate simple graph
        srand (time(NULL));
        int howManyEdges = rand() % (edges / vertexes);
        for(int j = howManyEdges; j > 0; j--){
            graph.push_back(make_pair(i, rand() % (vertexes - i) + i + 1));
            edges--;
        }
    }

    for(auto const &ent1 : graph){
        ss << ent1.first << " " << ent1.second << endl;
    }
    return ss.str();
}
