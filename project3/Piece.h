#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include <cstdlib>

class Well;
class Screen;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

class Piece
{
public:
    Piece(Well* well);
    virtual ~Piece();
    
    int get_box(int x, int y) const;
    int get_x() const;
    int get_y() const;
    int getRotation() const;
    
    void set_box(int x, int y);
    void clear_box();
    bool setPosition(int x, int y);
    virtual bool move(int dx, int dy);
    bool fall();
    bool rotate();
    virtual void setOrientation(int o) = 0;
    
    int overlap(int dx, int dy);
    virtual void action(Well *w);

    void display(Screen &s) const;
    void display(Screen &s, int s_x, int s_y) const;
    
    
private:
    int m_box[4][4];
    int m_x;
    int m_y;
    int m_rotation;
    Well* m_well;      
    
};


class PieceT : public Piece
{
public:
    PieceT(Well* well);
    virtual ~PieceT();
    virtual void setOrientation(int o);
};

class PieceI : public Piece
{
public:
    PieceI(Well* well);
    virtual ~PieceI();
    virtual void setOrientation(int o);
};

class PieceL : public Piece
{
public:
    PieceL(Well* well);
    virtual ~PieceL();
    virtual void setOrientation(int o);
};

class PieceJ : public Piece
{
public:
    PieceJ(Well* well);
    virtual ~PieceJ();
    virtual void setOrientation(int o);
};

class PieceO : public Piece
{
public:
    PieceO(Well* well);
    virtual ~PieceO();
    virtual void setOrientation(int o);
};

class PieceS : public Piece
{
public:
    PieceS(Well* well);
    virtual ~PieceS();
    virtual void setOrientation(int o);
};

class PieceZ : public Piece
{
public:
    PieceZ(Well* well);
    virtual ~PieceZ();
    virtual void setOrientation(int o);
};

class CrazyShape : public Piece
{
public:
    CrazyShape(Well* well);
    virtual ~CrazyShape();
    virtual void setOrientation(int o);
    virtual bool move(int dx, int dy);
};


class VaporBomb : public Piece
{
public:
    VaporBomb(Well* well);
    virtual ~VaporBomb();
    virtual void setOrientation(int o);
    virtual void action(Well* w);
};

class FoamBomb : public Piece
{
public:
    FoamBomb(Well* well);
    virtual ~FoamBomb();
    virtual void setOrientation(int o);
    virtual void action(Well* w);
    
    void foam(int x0, int y0, int x, int y, Well* w);
    
};



#endif // PIECE_INCLUDED
