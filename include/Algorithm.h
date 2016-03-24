#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <set>
#include <algorithm>

#include "Structures.h"

using namespace std;

class Algorithm
{
    public:
        GraphColoring algorithm(Graph &graph);

        Algorithm();
        virtual ~Algorithm();
    protected:
    private:
        set<int> colors;

        int getColor(int);
        void resetColor();

};

#endif // ALGORITHM_H
