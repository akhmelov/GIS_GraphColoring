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
        set<int> colorUsed; //which colors already checked and not suitable
        graphColoring[ent1.first] = getColor(0);
        colorUsed.insert(graphColoring[ent1.first]); //insert forbidden color
        for(auto const &ent2 : ent1.second) {
            if(ent2.second){    //it's ent1's neighbour
                while(graphColoring[ent2.first] == graphColoring[ent1.first]){
                    int newColor = getColor(graphColoring[ent1.first]);
                    while(!isColorAllowed(newColor, colorUsed))
                        newColor = getColor(newColor);
                    graphColoring[ent1.first] = newColor;
                    colorUsed.insert(graphColoring[ent1.first]); //insert forbidden color
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

bool Algorithm::isColorAllowed(int newColor, set<int> &colorUsed)
{
    set<int>::iterator it = find(colorUsed.begin(), colorUsed.end(), newColor);
    return colorUsed.end() == it;
}
