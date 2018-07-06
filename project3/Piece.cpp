#include "Piece.h"
#include "UserInterface.h"
#include "Well.h"
#include <cstdlib>

Piece::Piece(Well* well): m_x(3), m_y(0), m_rotation(0), m_well(well)
{ }

Piece::~Piece()
{ }


int Piece::get_box(int x, int y) const
{
    if (x >= 0 && x < 4 && y >= 0 && y < 4)
        return m_box[x][y];
    else return -1;
}

int Piece::get_x() const { return m_x; }
int Piece::get_y() const { return m_y; }

int Piece::getRotation() const { return m_rotation % 4; }


void Piece::set_box(int x, int y)
{
    if (x >= 0 && x < 4 && y >= 0 && y < 4)
    {
        m_box[x][y] = 1;
    }
    else return;
    
}

void Piece::clear_box()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m_box[i][j] = 0;
}




bool Piece::setPosition(int x, int y)
{

    if (overlap(x, y) == 0)
    {
        m_x = x;
        m_y = y;
        return true;
    }
    
    return false;
}

bool Piece::move(int dx, int dy)
{
    if (overlap(m_x + dx, m_y + dy) == 0)
    {
        m_x += dx;
        m_y += dy;
        return true;
    }
    
    return false;
}

bool Piece::fall()
{
    if (overlap(m_x, m_y+1) == 0)
    {
        m_y += 1;
        return true;
    }
    else return false;
    
}

bool Piece::rotate()
{
    m_rotation++;
    setOrientation(getRotation());

    if (overlap(m_x, m_y) == 0)
        return true;

    m_rotation--;
    setOrientation(getRotation());
    return false;
}



int Piece::overlap(int dx, int dy)
{
    
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (m_box[x][y] == 1)
            {
                int new_x = x + dx;
                int new_y = y + dy;
                
                if (new_x < 0 || new_x > m_well->width()-1) return 1;
                if (new_y < 0 || new_y > m_well->height()-1) return 2;

                if (m_well->get_well(new_x, new_y) != '\0') return 1;
            }
        }
    }
    return 0;
}

void Piece::action(Well* w)
{ }


void Piece::display(Screen &s) const
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (m_box[x][y] == 1)
            {
                s.gotoXY(m_x+x+1, m_y+y);
                s.printChar('#');
            }
        }
    }
}

void Piece::display(Screen &s, int s_x, int s_y) const
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (m_box[x][y] == 1)
            {
                s.gotoXY(s_x+x, s_y+y);
                s.printChar('#');
            }
        }
    }
}

PieceT::PieceT(Well *well)
: Piece(well)
{
    setOrientation(0);
}

PieceT::~PieceT()
{ }

void PieceT::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(0, 1);
            set_box(1, 0);
            set_box(1, 1);
            set_box(2, 1);
            break;
        case 1:
            clear_box();
            set_box(1, 0);
            set_box(1, 1);
            set_box(1, 2);
            set_box(2, 1);
            break;
        case 2:
            clear_box();
            set_box(0, 1);
            set_box(1, 1);
            set_box(2, 1);
            set_box(1, 2);
            break;
        case 3:
            clear_box();
            set_box(1, 0);
            set_box(1, 1);
            set_box(1, 2);
            set_box(0, 1);
            break;
        default:
            break;
    }
}

PieceL::PieceL(Well *well)
: Piece(well)
{
    setOrientation(0);
}

PieceL::~PieceL()
{ }

void PieceL::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(0, 1);
            set_box(1, 1);
            set_box(2, 1);
            set_box(0, 2);
            break;
        case 1:
            clear_box();
            set_box(1, 0);
            set_box(2, 0);
            set_box(2, 1);
            set_box(2, 2);
            break;
        case 2:
            clear_box();
            set_box(0, 2);
            set_box(1, 2);
            set_box(2, 2);
            set_box(2, 1);
            break;
        case 3:
            clear_box();
            set_box(2, 3);
            set_box(1, 1);
            set_box(1, 2);
            set_box(1, 3);
            break;
        default:
            break;
    }
}

PieceJ::PieceJ(Well *well)
: Piece(well)
{
    setOrientation(0);
}

PieceJ::~PieceJ()
{ }

void PieceJ::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(3, 2);
            set_box(1, 1);
            set_box(2, 1);
            set_box(3, 1);
            break;
        case 1:
            clear_box();
            set_box(1, 3);
            set_box(2, 1);
            set_box(2, 2);
            set_box(2, 3);
            break;
        case 2:
            clear_box();
            set_box(1, 2);
            set_box(2, 2);
            set_box(3, 2);
            set_box(1, 1);
            break;
        case 3:
            clear_box();
            set_box(1, 0);
            set_box(1, 1);
            set_box(1, 2);
            set_box(2, 0);
            break;
        default:
            break;
            
    }
}

PieceO::PieceO(Well *well)
: Piece(well)
{
    setOrientation(0);
}

PieceO::~PieceO()
{ }

void PieceO::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(0, 0);
            set_box(0, 1);
            set_box(1, 1);
            set_box(1, 0);
        case 1:
            clear_box();
            set_box(0, 0);
            set_box(0, 1);
            set_box(1, 1);
            set_box(1, 0);
        case 2:
            clear_box();
            set_box(0, 0);
            set_box(0, 1);
            set_box(1, 1);
            set_box(1, 0);
        case 3:
            clear_box();
            set_box(0, 0);
            set_box(0, 1);
            set_box(1, 1);
            set_box(1, 0);
            break;
        default:
            break;
    }
}

PieceS::PieceS(Well *well)
: Piece(well)
{
    setOrientation(0);
}

PieceS::~PieceS()
{ }

void PieceS::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(1, 1);
            set_box(2, 1);
            set_box(0, 2);
            set_box(1, 2);
            break;
        case 1:
            clear_box();
            set_box(1, 0);
            set_box(1, 1);
            set_box(2, 1);
            set_box(2, 2);
            break;
        case 2:
            clear_box();
            set_box(0, 2);
            set_box(1, 1);
            set_box(1, 2);
            set_box(2, 1);
            break;
        case 3:
            clear_box();
            set_box(1, 0);
            set_box(1, 1);
            set_box(2, 1);
            set_box(2, 2);
            break;
        default:
            break;
    }
}

PieceZ::PieceZ(Well *well)
: Piece(well)
{
    setOrientation(0);
}

PieceZ::~PieceZ()
{ }

void PieceZ::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(1, 1);
            set_box(2, 2);
            set_box(0, 1);
            set_box(1, 2);
            break;
        case 1:
            clear_box();
            set_box(1, 2);
            set_box(1, 1);
            set_box(2, 1);
            set_box(2, 0);
            break;
        case 2:
            clear_box();
            set_box(1, 1);
            set_box(2, 2);
            set_box(0, 1);
            set_box(1, 2);
            break;
        case 3:
            clear_box();
            set_box(1, 2);
            set_box(1, 1);
            set_box(2, 1);
            set_box(2, 0);
            break;
        default:
            break;
            
    }
}

PieceI::PieceI(Well *well)
: Piece(well)
{
    setOrientation(0);
}

PieceI::~PieceI()
{ }

void PieceI::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(0, 1);
            set_box(1, 1);
            set_box(2, 1);
            set_box(3, 1);
            break;
        case 1:
            clear_box();
            set_box(1, 0);
            set_box(1, 1);
            set_box(1, 2);
            set_box(1, 3);
            break;
        case 2:
            clear_box();
            set_box(0, 1);
            set_box(1, 1);
            set_box(2, 1);
            set_box(3, 1);
            break;
        case 3:
            clear_box();
            set_box(1, 0);
            set_box(1, 1);
            set_box(1, 2);
            set_box(1, 3);
            break;
        default:
            break;
            
    }
}

VaporBomb::VaporBomb(Well *well)
: Piece(well)
{
    setOrientation(0);
}

VaporBomb::~VaporBomb()
{ }

void VaporBomb::setOrientation(int o)
{
    
    switch (o)
    {
        case 0:
            clear_box();
            set_box(1, 0);
            set_box(2, 0);
            break;
        case 1:
            clear_box();
            set_box(1, 0);
            set_box(2, 0);
            break;
        case 2:
            clear_box();
            set_box(1, 0);
            set_box(2, 0);
            break;
        case 3:
            clear_box();
            set_box(1, 0);
            set_box(2, 0);
            break;
        default:
            break;
    }
}

void VaporBomb::action(Well *w)
{
    
    int vaporBomb1 = get_x() + 1;
    int vaporBomb2 = get_x() + 2;
    
    for (int i = -2; i <= 2; i++)
    {
        int yTarget = get_y() + i;

        w->set_well(vaporBomb1, yTarget, '\0');
        w->set_well(vaporBomb2, yTarget, '\0');
    }
}


FoamBomb::FoamBomb(Well *well)
: Piece(well)
{
    setOrientation(0);
}

FoamBomb::~FoamBomb()
{ }

void FoamBomb::setOrientation(int o)
{
    
    switch(o)
    {
        case 0:
            clear_box();
            set_box(1, 1);
            break;
        case 1:
            clear_box();
            set_box(1, 1);
            break;
        case 2:
            clear_box();
            set_box(1, 1);
            break;
        case 3:
            clear_box();
            set_box(1, 1);
            break;
        default:
            break;
    }
}

void FoamBomb::action(Well* w)
{
    int FoamBomb_x = get_x() + 1;
    int FoamBomb_y = get_y() + 1;
    foam(FoamBomb_x, FoamBomb_y, FoamBomb_x, FoamBomb_y, w);
}

void FoamBomb::foam(int sx, int sy, int ex, int ey, Well* w)
{
    
    if (!w->check_well_boundary(ex, ey))
        return;
    
    if (ex > sx+2 || ex < sx-2 || ey > sy+2 || ey < sy-2)
        return;

    if (ex!=sx && ey != sy && w->get_well(ex, ey) != '\0')
        return;
    
    w->set_well(ex, ey, '*');
    
    if (!w->filled(ex+1, ey))
        foam(sx, sy, ex+1, ey, w);
    if (!w->filled(ex-1, ey))
        foam(sx, sy, ex-1, ey, w);
    if (!w->filled(ex, ey+1))
        foam(sx, sy, ex, ey+1, w);
    if (!w->filled(ex, ey-1))
        foam(sx, sy, ex, ey-1, w);
    
}


CrazyShape::CrazyShape(Well *well)
: Piece(well)
{
    setOrientation(0);
}

CrazyShape::~CrazyShape()
{ }

void CrazyShape::setOrientation(int o)
{
    
    switch(o)
    {
        case 0:
            clear_box();
            set_box(0, 0);
            set_box(1, 1);
            set_box(2, 1);
            set_box(3, 0);
            break;
        case 1:
            clear_box();
            set_box(3, 0);
            set_box(2, 1);
            set_box(2, 2);
            set_box(3, 3);
            break;
        case 2:
            clear_box();
            set_box(0, 3);
            set_box(1, 2);
            set_box(2, 2);
            set_box(3, 3);
            break;
        case 3:
            clear_box();
            set_box(0, 0);
            set_box(1, 1);
            set_box(1, 2);
            set_box(0, 3);
            break;
        default:
            break;
    }
}


bool CrazyShape::move(int dx, int dy)
{
    if (overlap(get_x()-dx, get_y()+dy) == 0)
    {
        setPosition(get_x()-dx, get_y()+dy);
        return true;
    }
    
    return false;
}



