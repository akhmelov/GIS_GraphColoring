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
    OutputInf resultSequence = OutputFile(graphColoringSeq, outFilePath).generateFinalOutputStr();
    OutputInf resultIndependent = OutputFile(graphColoringInd, outFilePath).generateFinalOutputStr();

    cout << endl;
    cout << myFill() << "Sequence" << myFill() << "|" << myFill() << "Independent" << myFill() << endl;
    cout << myFill() << "        " << myFill() << "|" << myFill() << "           " << myFill() << endl;
    cout << myFill() << "" << myFill(9) << "Liczba kolorow uzytych" << myFill(9) << "" << myFill() << endl;
    cout << myFill() << resultSequence.numberOfColors << myFill(17) << "|" << myFill() << resultIndependent.numberOfColors << myFill() << endl;
    cout << myFill() << "" << myFill(9) << "kolor:  liczba wierzchołków" << myFill(9) << "" << myFill() << endl;
    for(map<int, int>::iterator it1 = resultSequence.countColorUsing.begin(), it2 = resultIndependent.countColorUsing.begin();
        it1 != resultSequence.countColorUsing.end() || it2 != resultIndependent.countColorUsing.end();) {
        if(it1 != resultSequence.countColorUsing.end())
            { cout << myFill() << it1 -> first << ": " << it1 -> second << myFill(14); it1++; }
        else
            cout << myFill() << "        " << myFill();
        cout << "|";
        if(it2 != resultIndependent.countColorUsing.end())
            { cout << myFill() << it2 -> first << ": " << it2 -> second << myFill(14); it2++; }
        else
            cout << myFill() << "        " << myFill();
        cout << endl;
    }

    OutputFile outputFile(graphColoringInd, outFilePath);
    outputFile.generateOutput();

    for(auto const& value: graphColoringSeq) {
        cout << value.first << " " << value.second << endl;
    }


    cout << "Hello world!" << endl;


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

            outputFile << pathToDirectory << fileName << endl;    cout << pathToDirectory << fileName << endl;
            Graph graph = inputFile.makeGraph(pathToDirectory + ent->d_name);

            string outFilePath = string(pathToOutputDirectory + "log_" + fileName);
            Algorithm algorithm;
            GraphColoring graphColoringSeq = algorithm.algorithmSequence(graph);
            GraphColoring graphColoringInd = algorithm.algorithmIndependent(graph);
            OutputInf resultSequence = OutputFile(graphColoringSeq, outFilePath).generateFinalOutputStr();
            OutputInf resultIndependent = OutputFile(graphColoringInd, outFilePath).generateFinalOutputStr();

            outputFile << endl;
            outputFile << myFill() << "Sequence" << myFill() << "|" << myFill() << "Independent" << myFill() << endl;
            outputFile << myFill() << "        " << myFill() << "|" << myFill() << "           " << myFill() << endl;
            outputFile << myFill() << "" << myFill(9) << "Liczba kolorow uzytych" << myFill(9) << "" << myFill() << endl;
            outputFile << myFill() << resultSequence.numberOfColors << myFill(17) << "|" << myFill() << resultIndependent.numberOfColors << myFill() << endl;
            outputFile << myFill() << "" << myFill(9) << "kolor:  liczba wierzchołków" << myFill(9) << "" << myFill() << endl;
            for(map<int, int>::iterator it1 = resultSequence.countColorUsing.begin(), it2 = resultIndependent.countColorUsing.begin();
                it1 != resultSequence.countColorUsing.end() || it2 != resultIndependent.countColorUsing.end();) {
                if(it1 != resultSequence.countColorUsing.end())
                    { outputFile << myFill() << it1 -> first << ": " << it1 -> second << myFill(14); it1++; }
                else
                    outputFile << myFill() << "        " << myFill();
                outputFile << "|";
                if(it2 != resultIndependent.countColorUsing.end())
                    { outputFile << myFill() << it2 -> first << ": " << it2 -> second << myFill(14); it2++; }
                else
                    outputFile << myFill() << "        " << myFill();
                outputFile << endl;
            }

          }
          closedir (dir);
        } else {
          /* could not open directory */
          perror ("");
          return EXIT_FAILURE;
        }
        outputFile.close();
    }

    return 0;
}
