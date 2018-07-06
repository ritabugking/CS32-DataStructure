//
//  Game.h
//  project1
//
//  Created by YI-JU WANG on 2018/4/11.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>

class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

#endif /* Game_h */
