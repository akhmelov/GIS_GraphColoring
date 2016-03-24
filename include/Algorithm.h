#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Structures.h"

class Algorithm
{
    public:
        GraphColoring algorithm(Graph &graph);

        Algorithm();
        virtual ~Algorithm();
    protected:
    private:
};

#endif // ALGORITHM_H
