//
//  History.h
//  project1
//
//  Created by YI-JU WANG on 2018/4/11.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#ifndef History_h
#define History_h

#include <stdio.h>
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    char flatulanHistory[MAXROWS][MAXCOLS];
    int m_row;
    int m_col;
};

#endif /* History_h */
