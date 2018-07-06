//
//  ScoreList.cpp
//  homework1
//
//  Created by YI-JU WANG on 2018/4/17.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#include "ScoreList.h"

ScoreList::ScoreList()
{

}

bool ScoreList::add(unsigned long score)
{
    if (score < 0 || score > 100)
        return false;
    if (s.size() == DEFAULT_MAX_ITEMS)
        return false;
    
    return s.insert(s.size(), score);
    
}

bool ScoreList::remove(unsigned long score)
{

    int pos;
    pos = s.find(score);
    if (pos == -1)
        return false;
    return s.erase(pos);
    
}

int ScoreList::size() const
{

    return s.size();
}

unsigned long ScoreList::minimum() const
{

    if (s.empty())
        return NO_SCORE;
    for (int i=0; i<=100; i++)
    {
    
        int pos = s.find(i);
        if (pos!=-1)
            return i;
            
    }
    return NO_SCORE;
}

unsigned long ScoreList::maximum() const
{
    if (s.empty())
        return NO_SCORE;

    for (int i=100; i>=0; i--)
    {
        
        int pos = s.find(i);
        if (pos!=-1)
            return i;
        
    }
    return NO_SCORE;
}
