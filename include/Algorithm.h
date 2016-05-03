#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <set>
#include <algorithm>
#include <cmath>        // std::abs
#include <climits>

#include "Structures.h"

using namespace std;

class Algorithm
{
    public:
        GraphColoring algorithmSequence(const Graph &graph);
        GraphColoring algorithmIndependent(const Graph &graph);

        Algorithm();
        virtual ~Algorithm();
    protected:
    private:
        GraphColoring algorithmFull(const Graph &, GraphColoring &, map<int, int> &countColorUsing, set<int> &colors);
        void removeNeighbours(int vertex, Graph &); //remove all neighbours "vertex" from Graph
        int vertexMinDegree(const Graph &graph); //get vertex with minimum degree
        int getDegreeOfVertex(int vertex, const Graph &);
        int getColor(set<int> &colors, int a = 0,bool isGetTotalNewColor = false);
        int getMaxMinUsedColor(map<int, int> &countColorUsing, bool isMax = true);
        bool isJusticeColoring(map<int, int> &countColorUsing); //check if different beetwing using of colors is 1
        bool isColorAllowed(int newColor, set<int> &colorUsed);

};

#endif // ALGORITHM_H
