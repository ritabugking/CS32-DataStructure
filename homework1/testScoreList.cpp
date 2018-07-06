//
//  testScoreList.cpp
//  homework1
//
//  Created by YI-JU WANG on 2018/4/17.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include <stdio.h>
#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    ScoreList sl;
    assert(sl.size()==0);
    assert(sl.add(42) == 1);
    sl.add(43);
    assert(sl.size() == 2);
    sl.add(44);
    sl.add(45);
    sl.add(46);
    assert(sl.size()==5);
    assert(sl.minimum()==42);
    assert(sl.maximum()==46);
    sl.remove(46);
    assert(sl.maximum()==45);
    sl.add(0);
    assert(sl.minimum()==0);
    assert(sl.add(-1)==1);
    assert(sl.add(10000)==1);
    sl.add(-1);
    sl.add(10000);
    assert(sl.size()==5);
    
    cout << "Passed all tests" << endl;
}
