//
//  History.cpp
//  project1
//
//  Created by YI-JU WANG on 2018/4/11.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include "History.h"
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  History implementation
///////////////////////////////////////////////////////////////////////////

History::History(int nRows, int nCols)
: m_row(nRows), m_col(nCols)
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            flatulanHistory[i][j] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    if (r < 1 || r > m_row || c < 1 || c > m_col)
        return false;
    if (flatulanHistory[r-1][c-1] == '.')
        flatulanHistory[r-1][c-1] = 'A';
    else if (flatulanHistory[r-1][c-1] >= 'A' && flatulanHistory[r-1][c-1] <= 'Y')
        flatulanHistory[r-1][c-1] += 1;
    return true;
}

void History::display() const
{
    // Draw the grid
    clearScreen();
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            cout << flatulanHistory[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
