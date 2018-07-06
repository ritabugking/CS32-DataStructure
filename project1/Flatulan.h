//
//  Flatulan.h
//  project1
//
//  Created by YI-JU WANG on 2018/4/11.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#ifndef Flatulan_h
#define Flatulan_h

#include <stdio.h>
//#include "City.h"
class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Flatulan declaration.


class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};

#endif /* Flatulan_h */
