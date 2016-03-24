#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char ** argv)
{
    string inFilePath;
    string outFilePath;

    if ( argc > 1){ //if command line contain file's names
        inFilePath = string(argv[1]);
        outFilePath = string(argv[2]);
    }else { //get file's name
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
    cout << "Hello world!" << endl;
    return 0;
}
