#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <map>

typedef std::map<int, std::map<int, bool> > Graph;
typedef std::map<int, int> GraphColoring;

struct OutputInf {
    int numberOfColors = 0;
    std::map<int, int> countColorUsing;
};


class Structures
{
    public:
        Structures();
        virtual ~Structures();
    protected:
    private:
};

#endif // STRUCTURES_H
