//
// Created by Nate Lampros on 10/29/21.
//

#ifndef CS235LAB7_MAZE_H
#define CS235LAB7_MAZE_H
#include "MazeInterface.h"
#include <iostream>
#include <sstream>
using namespace  std;




class Maze : public MazeInterface{
private:
    enum CellValue_t { OPEN, BLOCKED, VISITED, EXIT, LEFT, RIGHT, UP, DOWN, OUT, IN, PATH };
    string mazeOutput = "_X*ELRUDOI";

    int ***myArray;
    int height;
    int width;
    int layer;

public:
    Maze() = default;
        /** Set maze value
        @parm height
        @parm width
        @parm layer
        @parm value
        */
    Maze(int arrayHeight, int arrayWidth, int arrayLayer) {
        height = arrayHeight;
        width = arrayWidth;
        layer = arrayLayer;
        myArray = new int**[height];

        for(int i = 0; i < height; ++i)
        {
            myArray[i] = new int*[width];
            for (int j = 0; j < width; ++j){
                myArray[i][j] = new int[layer];
            }
        }



    }
    ~Maze(void) {
        //loop to delete all arrays
        for (int i = 0; i < height; ++i){
            for(int j = 0; j < width; ++j)
            {
                delete [] myArray[i][j];
            }
            delete [] myArray[i];
        }
        delete [] myArray;
    }


    virtual void setValue(int h, int w, int l, int value) {
        myArray[h][w][l] = value;
    }

    /** Solve maze
       @return true if solveable, else false
    */
    bool find_maze_path(int h, int w, int l){
        //Base Cases
        if (l >= layer || l < 0 || w >= width || w < 0 || h >= height || h < 0){
            return false;
        }
        if(myArray[h][w][l] == EXIT){
            return true;
        }
        if(myArray[h][w][l] != OPEN){
            return false;
        }
        //Inductive Step
        myArray[h][w][l] = VISITED;
        if (find_maze_path(h,(w-1),l)){ //LEFT
            myArray[h][w][l] = LEFT;
            return true;
        }
        if (find_maze_path(h,(w+1),l)){ //RIGHT
            myArray[h][w][l] = RIGHT;
            return true;
        }
        if (find_maze_path((h-1),w,l)){ //UP
            myArray[h][w][l] = UP;
            return true;
        }
        if (find_maze_path((h+1),w,l)){ //DOWN
            myArray[h][w][l] = DOWN;
            return true;
        }
        if (find_maze_path(h,w,(l -1))) { //OUT
            myArray[h][w][l] = OUT;
            return true;
        }
        if (find_maze_path(h,w,(l+1))){ //IN
            myArray[h][w][l] = IN;
            return true;
        }
        return false;
    }


    virtual bool find_maze_path(){
        myArray[height - 1][width - 1][layer - 1] = EXIT;
        return find_maze_path(0, 0, 0);
        //return find_maze_path(2, 2, 2);

    }

    /** Output maze (same order as input maze)
      @return string of 2D layer
    */
    virtual std::string toString()const{
        stringstream oss;
        for (int l = 0; l < layer; ++l){
            oss << "Layer " << (l+1) << endl;

            for (int h = 0; h < height; ++h){

                for (int w = 0; w < width; ++w){
                    int data = myArray[h][w][l];
                    oss << " ";
                    oss << mazeOutput[data];
                }
                oss << endl;

            }


        }

        return oss.str();
    }

};


#endif //CS235LAB7_MAZE_H
