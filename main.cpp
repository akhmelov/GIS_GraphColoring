#include <iostream>
#include <stdio.h>
#include <string.h>
#include <dirent.h> //for list of files in directory

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
    GraphColoring graphColoringSeq = algorithm.algorithmSequence(graph);
    GraphColoring graphColoringInd = algorithm.algorithmIndependent(graph);

    cout << OutputFile().getOutput(graphColoringSeq, graphColoringInd) << endl;

    if(true){ //for all files in one folder
        //char pathToDirectory[256] = ;
        string pathToDirectory = string("/home/akhmelov/home/studia/GIS/Project/GIS_GraphColoring/test/");
        string pathToOutputDirectory = "/home/akhmelov/home/studia/GIS/Project/GIS_GraphColoring/outputs/";
        ofstream outputFile;
        outputFile.open((pathToOutputDirectory + "output.txt").c_str(), ofstream::in);
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

            Algorithm algorithm;
            GraphColoring graphColoringSeq = algorithm.algorithmSequence(graph);
            GraphColoring graphColoringInd = algorithm.algorithmIndependent(graph);

            string result = OutputFile().getOutput(graphColoringSeq, graphColoringInd);
            outputFile << result << endl;

            ofstream outputFileLog;
            outputFileLog.open((pathToOutputDirectory + "log_" + fileName).c_str(), ofstream::in);
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
