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
    GraphColoring graphColoring;
    for(auto const &ent1 : graph) {
        graphColoring[ent1.first] = getColor(0);
        for(auto const &ent2 : ent1.second) {
            if(ent2.second){    //it's ent1's neighbour
                while(graphColoring[ent2.first] == graphColoring[ent1.first]){
                    graphColoring[ent1.first] = getColor(graphColoring[ent1.first]);
                }
            }
        }
    }
    return graphColoring;
}


int Algorithm::getColor(int presentColor)
{
    set<int>::iterator it = find(colors.begin(), colors.end(), presentColor);
    if(colors.end() == it){ //if the begining
        presentColor++;
        colors.insert(presentColor);
    } else {
        it++;
        if(colors.end() == it){
            presentColor++;
            colors.insert(presentColor);
        } else {
            return *it;
        }
    }
    return presentColor;
}
