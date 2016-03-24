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

void InputFile::displayGraph(Graph &graph)
{
    vector<int> tmp;
    cout << "  |";
    for(auto const &ent1 : graph) {
        cout << " " << ent1.first;
        tmp.push_back(ent1.first);
    }
    cout << endl;
    cout << "--+";
    for(auto const &ent1 : graph) {
        cout << "--";
    }
    cout << endl;
    for(auto const &ent1 : graph) {
        cout << ent1.first << " |";
        for(vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            if(ent1.second.find(*it) != ent1.second.end()) cout << " +"; else cout << " -";
        }
        cout << endl;
    }
    cout << endl;
}
