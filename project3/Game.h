#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>

class Game
{
public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    void displaynext_piece(Piece* &n);
    int fix(Piece* &c, Piece* &n);
    int get_state();
    
    
private:
    int add_score(int num_row);
    void set_timer();
    void assign_piece(Piece* &p);
    std::string num_space(int n);
 
    Well        m_well;
    Screen      m_screen;
    int         m_level;
    int         m_score;
    int         m_rowsLeft;
    int         m_state;
    int         m_timer;       
};

#endif // GAME_INCLUDED
