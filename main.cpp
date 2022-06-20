#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include "Maze.h"

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
    }

    int height = 0;
    int width = 0;
    int layers = 0;

    string line;
    getline(in, line);
    stringstream ss(line);
    ss >>  height;
    ss >> width;
    ss >> layers;


    cout << height << endl;
    cout << width << endl;
    cout << layers << endl;
    cout << endl;

    Maze myMaze(height, width, layers);

    int data;

    for (int l = 0; l < layers; ++l){

        getline(in, line);


        for (int h = 0; h < height; ++h){
            getline(in, line);
            stringstream iss(line);

            for (int w = 0; w < width; ++w){
                iss >> data;
                myMaze.setValue(h, w, l, data);
            }

        }

    }

    cout << "Solve Maze:" << endl <<myMaze.toString();
    out << "Solve Maze:" << endl <<myMaze.toString();

    if (myMaze.find_maze_path()) {
        cout << "Solution:" << endl << myMaze.toString();
        out << "Solution:" << endl << myMaze.toString();
    }
    else {
        cout << "No Solution Exists!";
        out << "No Solution Exists!";
    }


    return 0;
}
