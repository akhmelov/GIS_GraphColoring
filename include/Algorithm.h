#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <set>
#include <algorithm>
#include <cmath>        // std::abs

#include "Structures.h"

using namespace std;

class Algorithm
{
    public:
        GraphColoring algorithm1(const Graph &graph);
        GraphColoring algorithm2(const Graph &graph);

        Algorithm();
        virtual ~Algorithm();
    protected:
    private:
        //set<int> colors;

        GraphColoring algorithmFull(const Graph &, GraphColoring &, map<int, int> &countColorUsing, set<int> &colors);
        int getDegreeOfVertex(int vertex, const Graph &);
        int getColor(set<int> &colors, int a = 0,bool isGetTotalNewColor = false);
        int getMaxMinUsedColor(map<int, int> &countColorUsing, bool isMax = true);
        bool isJusticeColoring(map<int, int> &countColorUsing); //check if different beetwing using of colors is 1
        bool isColorAllowed(int newColor, set<int> &colorUsed);

};

#endif // ALGORITHM_H
