#include <iostream>
#include <stdio.h>
#include <string.h>
#include <dirent.h> //for list of files in directory
#include <ctime>

#include "InputFIle.h"
#include "OutputFile.h"
#include "Algorithm.h"

using namespace std;

string myFill(int n = 10)
{
    return string(n, ' ');
}


int main(int argc, char ** argv)
{
    if(string(argv[1]) == "generate"){  //generate random files
        while(true){
            int edges = 0, vertexes = 0;
            string fileName;
            char tmp[256];
            cout << "Wpisz nazwa_pliku ilosc_wierzcholkow ilosc_krawedzi ('exit' to exit)" << endl;
            cin.getline(tmp, 256);
            istringstream iss(tmp);
            if(string(tmp) == "exit") break;
            if(!(iss >> fileName >> vertexes >> edges)) { break; } // error
            if(!(edges > vertexes) || vertexes < 1) {cout << "Not true (edges > vertexes) or (vertexes < 0)"; return -1;}

            string result = OutputFile().generateGraph(vertexes, edges);
            ofstream outputFileLog;
            outputFileLog.open(fileName.c_str(), std::ofstream::in | std::ofstream::out | std::ofstream::app);
            outputFileLog << result;
            outputFileLog.close();
            //cout << result;
        }
        return 0;
    }
    string inFilePath;
    string outFilePath;

    if ( argc > 1){ //if command line contain file's names
        inFilePath = string(argv[1]);
        outFilePath = string(argv[2]);
    } else { //get file's name
        char tmp[256];
        cout << "Sciezka do pliku wejsciowego: ";
        cin.getline(tmp, 256);
        inFilePath = string(tmp);
        cout << "Sciezka do pliku wyjsciowego: ";
        cin.getline(tmp, 256);
        outFilePath = string(tmp);
    }
    cout << "From file: " << inFilePath << endl;
    cout << "To file: " << outFilePath << endl;

    InputFile inputFile;
    Graph graph = inputFile.makeGraph(inFilePath);
    cout << inputFile.displayGraph(graph);
    Algorithm algorithm;
    GraphColoring graphColoring;
    OutputInf outputInf;
    if(true){
        graphColoring = algorithm.algorithmSequence(graph, outputInf);
    } else {
        graphColoring = algorithm.algorithmIndependent(graph, outputInf);
    }

    string result = OutputFile().getSimpleOutput(graphColoring, outputInf);
    ofstream outputFileLog;
    outputFileLog.open(outFilePath, std::ofstream::in | std::ofstream::out | std::ofstream::trunc);
    outputFileLog << result;
    outputFileLog.close();
    cout << result << endl;

    if(1){ //for all files in one folder
        ///JUST FOR TESTING AND DOCUMENTATION -- UNSED CODE ON PRODUCTION
        //char pathToDirectory[256] = ;
        string pathToDirectory = string("/home/akhmelov/home/studia/GIS/Project/GIS_GraphColoring/test2/");
        string pathToOutputDirectory = "/home/akhmelov/home/studia/GIS/Project/GIS_GraphColoring/outputs/";
        ofstream outputFile;
        outputFile.open((pathToOutputDirectory + "output.txt").c_str(), ofstream::in | std::ofstream::trunc);
        string::size_type sz;     // alias of size_t

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (pathToDirectory.c_str())) != NULL) {
          /* print all the files and directories within directory */
          while ((ent = readdir (dir)) != NULL) {
            string fileName(ent->d_name);
            if (fileName == ".." || fileName == "." || fileName == "inputFiles.txt") continue; //special files in linux or mine

            outputFile << pathToDirectory << fileName << endl;
            Graph graph = inputFile.makeGraph(pathToDirectory + ent -> d_name);

            OutputInf outputSeq;
            OutputInf outputInd;
            Algorithm algorithm;
            GraphColoring graphColoringSeq = algorithm.algorithmSequence(graph, outputSeq);
            GraphColoring graphColoringInd = algorithm.algorithmIndependent(graph, outputInd);

            string result = OutputFile().getOutput(graphColoringSeq, graphColoringInd, outputSeq, outputInd);
            outputFile << result << endl;

            ofstream outputFileLog;
            outputFileLog.open((pathToOutputDirectory + "log_" + fileName).c_str(), ofstream::in | std::ofstream::trunc);
            outputFileLog << result;
            outputFileLog.close();
          }
          closedir (dir);
        } else {
          /* could not open directory */
          perror ("");
          return EXIT_FAILURE;
        }
        outputFile.close();
    }

    char a;
    cout << "Press any symbol -> enter to exit" << endl;
    cin >> a;

    return 0;
}
