#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "game.h"

using namespace std;

void parseReadFile(string &inputFile, vector<GameInputs> &g, vector<string> &lines)
{
    std::ifstream infile(inputFile);
    string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line);
        // parse lines
        std::istringstream iss(line);
        string hand1, hand2, board;

        iss >> hand1  >> hand2 >> board;

        // removing label at the begining of the string
        hand1 = string(hand1.begin() + hand1.find(":") + 1, hand1.end());
        hand2 = string(hand2.begin() + hand2.find(":") + 1, hand2.end());
        board = string(board.begin() + board.find(":") + 1, board.end());
        
        // create new game scenario
        g.emplace_back(hand1, hand2, board);
    }      
}
int main (int argc, char **argv)
{
    vector<string> inputs;

    // get command line values
    for (int i= 0; i < argc; ++i)
        inputs.push_back(string(argv[i]));
    
    // get name of input and output file
    string inputFile = inputs[1];
    string outputFile = inputs[2];


    // this will be used as a list of game scenario.
    // essentially parsed version of each line in the input
    vector<GameInputs> g;
    vector <string> lines;
    // read input file and store in lines
    parseReadFile(inputFile, g, lines);

    vector<string> results;

    for (int i = 0; i < g.size(); i ++)
    {
        /*
        cout << "game " << i << ":" << endl;
        g[i].print();*/

        ResultFinder rf(g[i]);
        results.emplace_back(rf.getFinalResult());
    }

    
    // print to file
    ofstream myfile;
    myfile.open(outputFile, ios::trunc);

    for (int i = 0; i < results.size(); i++)
    {
        myfile << lines[i] << endl;
        myfile << results[i] << endl << endl;
    }

    myfile.close();

    return 0;

}

