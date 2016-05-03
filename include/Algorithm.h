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
        set<int> colors;
        map<int, int> countColorUsing; //map<color, count> count - how many times it's used

        GraphColoring algorithmFull(const Graph &, GraphColoring &);
        int getDegreeOfVertex(int vertex, const Graph &);
        int getColor(int a = 0,bool isGetTotalNewColor = false);
        int getMaxMinUsedColor(bool isMax = true);
        bool isJusticeColoring(); //check if different beetwing using of colors is 1
        bool isColorAllowed(int newColor, set<int> &colorUsed);

};

#endif // ALGORITHM_H
