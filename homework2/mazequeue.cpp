//
//  mazequeue.cpp
//  homework 2
//
//  Created by YI-JU WANG on 2018/5/1.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include <queue>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

// Represents an (r,c) coordinate pair
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

/* * * * *
 
 Parameters:
 - A rectangular maze of Xs and dots that represents the maze. Each string of the array is a row of the maze. Each'X'represents
 a wall, and each '.' represents a walkway.
 - The number of rows in the maze.
 - The number of columns in the maze. Each string in the maze parameter must be this length.
 - The starting coordinates in the maze: sr, sc; the row number is in the range 0 through nRows−1, and the column number is in
 the range 0 through nCols−1.
 - The ending coordinates in the maze: er, ec; the row number is in the range 0 through nRows−1, and the column number is in
 the range 0 through nCols−1.
 
 Return value:
 - Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
 
 * * * * */
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    int nRows = 10;
    int nCols = 10;
    if (sr < 0 || sc < 0 || er < 0 || ec < 0 || sr > nRows || er > nRows || sc > nCols || ec > nCols || maze[sr][sc]!='.' || maze[er][ec]!='.')
        return false;
    // Push the starting coordinate (sr,sc) onto the coordinate queue and update maze[sr][sc] to indicate that the algorithm
    // has encountered it (i.e., set maze[sr][sc] to have a value other than '.').
    queue<Coord> coordQueue;
    Coord start(sr, sc);
    coordQueue.push(start);
    maze[sr][sc] = '1';
    
    // While the queue is not empty
    while(!coordQueue.empty())
    {
        // Pop the front coordinate off the queue and get the current (r,c) location
        Coord temp = coordQueue.front();
        int r, c;
        r = temp.r();
        c = temp.c();
        coordQueue.pop();
        //cout << '(' << r << ',' << c << ')';
        
        // If the current (r,c) coordinate is equal to the ending coordinate,
        // the maze is solved. Return true.
        if(r == er && c == ec)
            return true;
        
        // Check each place you can move from the current cell as follows:
        
        // If you can move NORTH and haven't encountered that cell yet,
        // then push the coordinate (r-1,c) at back of the queue and update
        // maze[r-1][c] to indicate the algorithm has encountered it.
        if((r-1) >= 0 && maze[r-1][c] == '.'){
            Coord north(r-1, c);
            coordQueue.push(north);
            maze[r-1][c] = '1';
        }
        
        // If you can move EAST and haven't encountered that cell yet,
        // then push the coordinate (r,c+1) at back of the queue and update
        // maze[r][c+1] to indicate the algorithm has encountered it.
        if((c+1) < nCols && maze[r][c+1] == '.'){
            Coord east(r, c+1);
            coordQueue.push(east);
            maze[r][c+1] = '1';
        }
        
        // If you can move SOUTH and haven't encountered that cell yet,
        // then push the coordinate (r+1,c) at back of the queue and update
        // maze[r+1][c] to indicate the algorithm has encountered it.
        if((r+1) < nRows && maze[r+1][c] == '.'){
            Coord south(r+1, c);
            coordQueue.push(south);
            maze[r+1][c] = '1';
        }
        
        // If you can move WEST and haven't encountered that cell yet,
        // then push the coordinate (r,c-1) at back of the queue and update
        // maze[r][c-1] to indicate the algorithm has encountered it.
        if((c-1) >= 0 && maze[r][c-1] == '.'){
            Coord west(r, c-1);
            coordQueue.push(west);
            maze[r][c-1] = '1';
        }
        
    }
    // There was no solution, so return false
    return false;
    
}

/*
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    if (pathExists(maze, 6,5, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

*/

