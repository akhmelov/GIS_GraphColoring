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
    //start simple coloring algorithm
    for(auto const &ent1 : graph) {
        set<int> colorUsed; //which colors already checked and not suitable
        graphColoring[ent1.first] = getColor(0);
        colorUsed.insert(graphColoring[ent1.first]); //insert forbidden color
        for(auto const &ent2 : ent1.second) {
            if(ent2.second){    //it's ent1's neighbour
                while(graphColoring[ent2.first] == graphColoring[ent1.first]){  //is neighbour has the same color?
                    int newColor = getColor(graphColoring[ent1.first]);
                    while(!isColorAllowed(newColor, colorUsed))
                        newColor = getColor(newColor);
                    graphColoring[ent1.first] = newColor;
                    colorUsed.insert(graphColoring[ent1.first]); //insert forbidden color
                }
            }
        }
        countColorUsing[graphColoring[ent1.first]]++;
    }
    //end of the simple coloring algorithm
    for(auto const &ent: countColorUsing){
        cout << "Simple algorithm: color " << ent.first << " has " << ent.second << " vertix(ces)" <<  endl;
    }
    return algorithmFull(graph, graphColoring);
}

GraphColoring Algorithm::algorithmFull(Graph &graph, GraphColoring &graphColoring)
{
    //start justice coloring
    int lastPositionOfPresentColors = *(colors.rbegin()); //new colors will be gave from this position
    while(!isJusticeColoring()){
        int mostUsedColor = getMaxMinUsedColor();
        int lessUsedColor = getMaxMinUsedColor(false);

        int minPositionVertix = -1;
        int maxPositionVertix = -1;
        for(auto const& value: graphColoring) { //gets possition of the vertex for the max and min color
            if(value.second == mostUsedColor)   maxPositionVertix = value.first;
            if(value.second == lessUsedColor)   minPositionVertix = value.first;
            if(minPositionVertix > -1 && maxPositionVertix > -1)    break;
        }
        //change color or gave another color
        set<int> colorUsed; //which colors already checked and not suitable
        colorUsed.insert(graphColoring[maxPositionVertix]); //insert forbidden color
        countColorUsing[graphColoring[maxPositionVertix]]--; //decreases using of this color
        graphColoring[maxPositionVertix] = lessUsedColor; //gave new color
        colorUsed.insert(lessUsedColor); //set new color as forbidden color
        for(auto const &ent2 : graph[maxPositionVertix]) {
            if(ent2.second){    //it's ent1's neighbour
                while(graphColoring[ent2.first] == graphColoring[maxPositionVertix]){  //is neighbour has the same color?
                    int newColor = getColor(lastPositionOfPresentColors);
                    while(!isColorAllowed(newColor, colorUsed))
                        newColor = getColor(newColor);
                    graphColoring[maxPositionVertix] = newColor;
                    colorUsed.insert(graphColoring[maxPositionVertix]); //insert forbidden color
                }
            }
        }
        countColorUsing[graphColoring[maxPositionVertix]]++;

        /*cout << "Justice coloring false lastColor: " << lastPositionOfPresentColors
            << " max(" << maxPositionVertix << "): "<< mostUsedColor << "  min(" << minPositionVertix << "): "<< lessUsedColor << endl;*/
        cout << "Justice coloring false change color for vertix " << "" << maxPositionVertix << " from " << mostUsedColor << " to " <<  graphColoring[maxPositionVertix] << endl;

    }
    //end justice coloring
    for(auto const &ent: countColorUsing){
        cout << "Full algorithm: color " << ent.first << " has " << ent.second << " vertix(ces)" <<  endl;
    }
    return graphColoring;
}

int Algorithm::getColor(int presentColor, bool isGetTotalNewColor)
{
    while(isGetTotalNewColor){
        set<int>::iterator it = find(colors.begin(), colors.end(), presentColor);
        if(colors.end() == it){
            colors.insert(presentColor);
            return presentColor;
        }
        presentColor++;
    }

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

int Algorithm::getMaxMinUsedColor(bool isMax)
{
    int maxMin = countColorUsing.begin()->first;
    for(auto const &ent: countColorUsing){
        if(ent.second > countColorUsing[maxMin] && isMax){
            maxMin = ent.first;
        } else if(ent.second < countColorUsing[maxMin] && !isMax) {
            maxMin = ent.first;
        }
    }
    return maxMin;
}

bool Algorithm::isJusticeColoring()
{
    int firstColor = countColorUsing.begin()->second;
    for(auto const &ent: countColorUsing){
        if(abs(firstColor - ent.second) > 1)
            return false;
    }
    return true;
}
