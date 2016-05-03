#include "Algorithm.h"

Algorithm::Algorithm()
{
    //ctor
}

Algorithm::~Algorithm()
{
    //dtor
}

GraphColoring Algorithm::algorithmSequence(const Graph &graph)
{
    GraphColoring graphColoring;
    set<int> colors;
    map<int, int> countColorUsing;
    //start simple coloring algorithm
    for(auto const &ent1 : graph) {
        set<int> colorUsed; //which colors already checked and not suitable
        graphColoring[ent1.first] = getColor(colors, 0);
        colorUsed.insert(graphColoring[ent1.first]); //insert forbidden color
        for(auto const &ent2 : ent1.second) {
            if(ent2.second){    //it's ent1's neighbour
                colorUsed.insert(graphColoring[ent2.first]); //the color of the neighbour is forbidden
                while(graphColoring[ent2.first] == graphColoring[ent1.first]){  //is neighbour has the same color?
                    int newColor = getColor(colors, graphColoring[ent1.first]);
                    while(!isColorAllowed(newColor, colorUsed))
                        newColor = getColor(colors, newColor);
                    graphColoring[ent1.first] = newColor;
                    colorUsed.insert(graphColoring[ent1.first]); //insert forbidden color
                }
            }
        }
        countColorUsing[graphColoring[ent1.first]]++;
    }
    //end of the simple coloring algorithm
    for(auto const &ent: countColorUsing){
        //cout << "Sequence algorithm: color " << ent.first << " has " << ent.second << " vertix(ces)" <<  endl;
    }
    return algorithmFull(graph, graphColoring, countColorUsing, colors);
}

GraphColoring Algorithm::algorithmIndependent(const Graph &graph)
{   ///TODO independent set
    GraphColoring graphColoring;
    set<int> colors;
    map<int, int> countColorUsing;

    Graph graph_ = graph;
    int newColor = getColor(colors, 0);

    Graph tmpGraph = graph_;
    while(graph_.size() != 0){  //graph without visited vertexes
        tmpGraph = graph_; //graph without visited vertexes, but with neighbours
        while(tmpGraph.size() != 0){    //graph without visited vertexes' neighbours
            int vertex = vertexMinDegree(tmpGraph); //get vertex with minimum degree
            if(vertex == -1) break;
            countColorUsing[newColor]++;  graphColoring[vertex] = newColor; //set color
            removeNeighbours(vertex, tmpGraph);
            graph_.erase(vertex); //remove visited vertex
            tmpGraph.erase(vertex); //remove visited vertex
        }
        newColor = getColor(colors, newColor); //get next color
    }

    //end of the simple coloring algorithm
    for(auto const &ent: countColorUsing){
        //cout << "Independent algorithm: color " << ent.first << " has " << ent.second << " vertix(ces)" <<  endl;
    }
    return algorithmFull(graph, graphColoring, countColorUsing, colors);
}

GraphColoring Algorithm::algorithmFull(const Graph &graph, GraphColoring &graphColoring, map<int, int> &countColorUsing, set<int> &colors)
{
    //start justice coloring
    int lastPositionOfPresentColors = *(colors.rbegin()); //new colors will be gave from this position
    while(!isJusticeColoring(countColorUsing)){
        int mostUsedColor = getMaxMinUsedColor(countColorUsing);
        int lessUsedColor = getMaxMinUsedColor(countColorUsing, false);

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
        for(auto const &ent2 : (graph.find(maxPositionVertix)) -> second) {
            colorUsed.insert(graphColoring[ent2.first]); //the color of the neighbour is forbidden
            if(ent2.second){    //it's ent1's neighbour
                while(graphColoring[ent2.first] == graphColoring[maxPositionVertix]){  //is neighbour has the same color?
                    int newColor = getColor(colors, lastPositionOfPresentColors);
                    while(!isColorAllowed(newColor, colorUsed))
                        newColor = getColor(colors, newColor);
                    graphColoring[maxPositionVertix] = newColor;
                    colorUsed.insert(graphColoring[maxPositionVertix]); //insert forbidden color
                }
            }
        }
        countColorUsing[graphColoring[maxPositionVertix]]++;

        /*cout << "Justice coloring false lastColor: " << lastPositionOfPresentColors
            << " max(" << maxPositionVertix << "): "<< mostUsedColor << "  min(" << minPositionVertix << "): "<< lessUsedColor << endl;*/
        //cout << "Justice color checking false change color for vertix " << "" << maxPositionVertix << " from " << mostUsedColor << " to " <<  graphColoring[maxPositionVertix] << endl;

    }
    //end justice coloring
    for(auto const &ent: countColorUsing){
        //cout << "Full algorithm: color " << ent.first << " has " << ent.second << " vertix(ces)" <<  endl;
    }
    return graphColoring;
}

void Algorithm::removeNeighbours(int vertex, Graph &graph)
{
    for(auto &ent2 : graph[vertex]) {
        if(ent2.second){    //it's ent1's neighbour
            //ent2.second = false;  ((graph[ent2.first].find(vertex)) -> second) = false; //set connection to false, the graph is symethric
            graph.erase(ent2.first);
        }
    }
}

int Algorithm::vertexMinDegree(const Graph &graph)
{
    pair<int, int> vertex(-1, INT_MAX); //<vertex, degree>
    for(auto const &ent1 : graph) {
        int tmpDegree = getDegreeOfVertex(ent1.first, graph);
        if(tmpDegree < vertex.second) vertex = make_pair(ent1.first, ent1.second.size());
    }
    return vertex.first;
}

int Algorithm::getDegreeOfVertex(int vertex, const Graph &graph)
{
    int count = 0;
    for(auto const &ent2 : (graph.find(vertex)) -> second) {
        if(ent2.second) count++;
    }
    return count;
}

int Algorithm::getColor(set<int> &colors, int presentColor, bool isGetTotalNewColor)
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

int Algorithm::getMaxMinUsedColor(map<int, int> &countColorUsing, bool isMax)
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

bool Algorithm::isJusticeColoring(map<int, int> &countColorUsing)
{
    int maxColorCount = countColorUsing.begin()->second;
    int minColorCount = countColorUsing.begin()->second;
    for(auto const &ent: countColorUsing){
        if(maxColorCount < ent.second) maxColorCount = ent.second;
        if(minColorCount > ent.second) minColorCount = ent.second;
        if(abs(maxColorCount - minColorCount) > 1) return false;
    }
    return true;
}
