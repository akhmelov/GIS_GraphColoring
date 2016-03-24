#include "InputFIle.h"

InputFile::InputFile()
{
    //ctor
}

InputFile::~InputFile()
{
    //dtor
}


Graph InputFile::makeGraph(string path)
{
    Graph graph;

    ifstream infile("path");
    string line;
    while (getline(infile, line))
    {
        cout << line << endl;
        istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) { break; } // error
        // process pair (a,b)
    }
    //ctor
}
