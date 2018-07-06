#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <cmath>
#include <string>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;


Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(width, height), m_score(0), m_rowsLeft(5),
m_timer(1000), m_state(0)
{
}

void Game::play()
{
    displayStatus();
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    m_well.display(m_screen, WELL_X, WELL_Y);
    waitForEnter();
    
    for(;;)
    {
        if (!playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);
}


void Game::displayStatus()
{
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score:     " + num_space(m_score));
    
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left: " + num_space(m_rowsLeft));
    
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:     " + num_space(m_level));
    
    m_screen.refresh();
}

void Game::displaynext_piece(Piece* &n)
{
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next piece:");
    n->display(m_screen, NEXT_PIECE_X, NEXT_PIECE_Y);
}

int Game::fix(Piece* &c, Piece* &n)
{

    m_well.fixPiece(*c);
    c->action(&m_well);
    
    m_well.display(m_screen, WELL_X, WELL_Y, true);
    
    int num_rowClear = m_well.clear_rows();
    m_rowsLeft -= num_rowClear;
    
    if (m_rowsLeft < 0)
        m_rowsLeft = 0;
    
    if (num_rowClear > 0)
        m_score += add_score(num_rowClear);
    
    if (m_rowsLeft <= 0)
        m_state = 2;
    
    delete c;
    
    if (m_state == 2)
    {
        delete n;
        return 1;
    }
    
    c = n;
    assign_piece(n);
    
    if (c->overlap(c->get_x(), c->get_y()) != 0)
    {
        m_state = 3;
        c->display(m_screen);
        delete c;
        delete n;
        return 2;
    }
    
    return 0;
}

bool Game::playOneLevel()
{
    m_state = 1;
    Timer timer;
    
    Piece* current_piece;
    Piece* next_piece;
    assign_piece(current_piece);
    assign_piece(next_piece);
    
    displayStatus();
    displaynext_piece(next_piece);
    current_piece->display(m_screen);
    
    set_timer();
    
    for (;;)
    {
        while (m_state == 1)
        {
            m_screen.clear();
            timer.start();

            while (m_state == 1 && timer.elapsed() < m_timer)
            {
                m_screen.clear();
                m_well.display(m_screen, WELL_X, WELL_Y);
                displaynext_piece(next_piece);
                current_piece->display(m_screen);
                displayPrompt("Press the Enter key to begin playing Chetyris!");
                displayStatus();
                
                char input;
                
                if (getCharIfAny(input))
                {
                    switch(input)
                    {
                        case ARROW_LEFT:
                            current_piece->move(-1, 0);
                            break;

                        case ARROW_RIGHT:
                            current_piece->move(1, 0);
                            break;
                            
                        case ARROW_DOWN:
                            if (!current_piece->move(0, 1))
                                if (fix(current_piece, next_piece) == 2)
                                    return false;
                            
                            timer.start();
                            break;
                            
                        // SPACE
                        case 32:
                            while(current_piece->move(0, 1))
                                ;
                            
                            if (fix(current_piece, next_piece) == 2)
                                return false;
                            timer.start();
                            break;
                            
                        case ARROW_UP:
                            current_piece->rotate();
                            break;
                            
                        // QUIT
                        case 'q':
                        case 'Q':
                            delete current_piece;
                            delete next_piece;
                            return false;
                            break;                          
                            
                        default:
                            break;
                    }
                }
            }

            if (m_state == 1 && !current_piece->fall())
                if (fix(current_piece, next_piece) == 2)
                    return false;
            
            current_piece->display(m_screen);
            m_screen.refresh();
        }
        
        if (m_state == 2)
        {
            m_screen.clear();
            m_well.display(m_screen, WELL_X, WELL_Y);
            displayPrompt("Press the Enter key to begin playing Chetyris!");
            displayStatus();            
            m_screen.refresh();
            m_well.clear_well();
            return true;
        }
        
        if (m_state == 3)
            return false;
    }
}

int Game::get_state() { return m_state; }

int Game::add_score(int num_row)
{
    int score = std::pow(2, num_row-1) * 100;
    return score;
}

void Game::set_timer()
{
    if (1000 - (100 * (m_level-1)) > 100)
        m_timer = 1000 - (100 * (m_level-1));
    else
        m_timer = 100;
    
    m_rowsLeft = 5 * m_level;
}


void Game::assign_piece(Piece* &p)
{
    switch(chooseRandomPieceType())
    {

        case PIECE_I:
            p = new PieceI(&m_well);
            break;
        case PIECE_L:
            p = new PieceL(&m_well);
            break;
        case PIECE_J:
            p = new PieceJ(&m_well);
            break;
        case PIECE_T:
            p = new PieceT(&m_well);
            break;
        case PIECE_O:
            p = new PieceO(&m_well);
            break;
        case PIECE_S:
            p = new PieceS(&m_well);
            break;
        case PIECE_Z:
            p = new PieceZ(&m_well);
            break;
        case PIECE_VAPOR:
            p = new VaporBomb(&m_well);
            break;
        case PIECE_FOAM:
            p = new FoamBomb(&m_well);
            break;
        case PIECE_CRAZY:
            p = new CrazyShape(&m_well);
            break;
            
        default:
            break;
    }
}

std::string Game::num_space(int n)
{
    int num = 1;
    std::string space = "";
    while (n / ((int)(pow(10, num))) > 0)
        num++;
    
    for (int i = 0; i < 7-num; i++)
    {
        space += " ";
    }
    return space + std::to_string(n);
}
