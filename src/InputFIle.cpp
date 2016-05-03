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

    ifstream file(path);
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) { break; } // error
        graph[a][b] = true;
        graph[b][a] = true;//semetric matrix
    }

    return graph;
}

string InputFile::displayGraph(Graph &graph)
{
    stringstream ss;
    vector<int> tmp;
    ss << "  |";
    for(auto const &ent1 : graph) {
        ss << " " << ent1.first;
        tmp.push_back(ent1.first);
    }
    ss << endl;
    ss << "--+";
    for(auto const &ent1 : graph) {
        ss << "--";
    }
    ss << endl;
    for(auto const &ent1 : graph) {
        ss << ent1.first << " |";
        for(vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            if(ent1.second.find(*it) != ent1.second.end()) ss << " +"; else ss << " -";
        }
        ss << endl;
    }
    ss << endl;
    return ss.str();
}
