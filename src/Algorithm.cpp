#include "Algorithm.h"

Algorithm::Algorithm()
{
    //ctor
}

Algorithm::~Algorithm()
{
    //dtor
}

GraphColoring Algorithm::algorithm(Graph &graph)
{
    //ctor
    ///TODO Test filling below
    GraphColoring graphColoring;
    for(int i = 1; i < 17; i++)
        graphColoring[i] = i * 9 / 3;
    return graphColoring;
}
