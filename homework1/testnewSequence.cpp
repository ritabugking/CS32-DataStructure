//
//  testnewSequence.cpp
//  homework1
//
//  Created by YI-JU WANG on 2018/4/17.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include <stdio.h>
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    s.insert(42);
    assert(s.size() == 1  &&  s.find(42) == 0);
    s.insert(1, 43);
    assert(s.size() == 2  &&  s.find(43) == 1);
    s.erase(0);
    assert(s.size() == 1  &&  s.find(42) == -1);
    assert(s.find(43) == 0);
    
    s.insert(1, 44);
    s.insert(2, 45);
    s.insert(3, 46);
    s.insert(4, 46);
    s.insert(5, 46);
    assert(s.size() == 6  &&  s.find(46) == 3);
    s.remove(46);
    assert(s.size() == 3  &&  s.find(46) == -1);
    ItemType value = 0;
    s.get(2, value);
    assert(value == 45);
    s.set(1, 0);
    assert(s.size() == 3  &&  s.find(0) == 1);
    
    Sequence s2;
    s2.insert(0, 0);
    s2.insert(1, 1);
    s2.insert(2, 2);
    s2.insert(3, 3);
    s2.insert(4, 4);
    
    s.swap(s2);
    assert(s.size() == 5  &&  s.find(4) == 4);
    
    s.insert(3);
    assert(s.size() == 6  &&  s.find(3) == 3);
    
    Sequence s3(s);
    assert(s3.size() == 6  &&  s3.find(1) == 1);
    
    Sequence s4(2);
    s4.insert(0, 0);
    s4.insert(1, 1);
    s4.insert(2, 2);
    s4.insert(3, 3);
    s4.insert(4, 4);
    assert(s4.size() == 2  &&  s4.find(4) == -1);
    
    Sequence s5 = s3;
    assert(s5.size() == 6  &&  s5.find(1) == 1);
    
    cout << "Passed all tests" << endl;

}
