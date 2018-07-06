#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"

Well::Well(int width, int height):
m_width(width), m_height(height)
{
    clear_well();
}


int Well::width() { return m_width; }
int Well::height() { return m_height; }

char Well::get_well(int x, int y) const
{
    if (check_well_boundary(x, y))
    {
        return m_well[x][y];
    }
    return '\0';
}

bool Well::set_well(int x, int y, char val)
{
    if (check_well_boundary(x, y))
    {
        m_well[x][y] = val;
        return true;
    }
    else
        return false;
}

void Well::fixPiece(Piece &p)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (p.get_box(x, y) == 1)
            {
                int pos_x = p.get_x() + x;
                int pos_y = p.get_y() + y;
                m_well[pos_x][pos_y] = '$';
            }
        }
    }
}

void Well::clear_row(int n)
{
    for (int y = n; y > 0; y--)
        for (int x = 0; x < m_width; x++)
            m_well[x][y] = m_well[x][y-1];
    
    for (int x = 0; x < m_width; x++)
        m_well[x][0] = '\0';
}

int Well::clear_rows()
{
    int num_rowClear = 0;
    
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            if (m_well[x][y] != '$' && m_well[x][y] != '*')
                break;
            else if ((m_well[x][y] == '$' || m_well[x][y] == '*') && x == m_width-1)
            {
                clear_row(y);
                num_rowClear++;
            }
        }
    }
    
    return num_rowClear;
}

void Well::clear_well()
{
    for (int i = 0; i < m_width; i++)
        for (int j = 0; j < m_height; j++)
            m_well[i][j] = '\0';
}

void Well::display(Screen& screen, int x, int y, bool flag)
{
    print_well(screen);
    
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            if (!flag)
            {
                if (m_well[i][j] != '\0')
                {
                    screen.gotoXY(i+1, j);
                    screen.printChar(m_well[i][j]);
                }
            }
            
            else
            {
                screen.gotoXY(i+1, j);
                if (m_well[i][j] == '\0')
                    screen.printChar(' ');
                else
                    screen.printChar(m_well[i][j]);
            }
        }
    }
}

bool Well::check_well_boundary(int x, int y) const
{
    return (x >= 0 && x <= m_width-1 && y >= 0 && y <= m_height-1);
}

bool Well::filled(int x, int y) const
{
    return (check_well_boundary(x, y) && m_well[x][y] != '\0');
}

void Well::print_well(Screen& screen)
{
    screen.gotoXY(0, 0);
    for (int y = 0; y < m_height+1; y++)
    {
        screen.printChar('@');
        screen.gotoXY(0, y);
    }
    
    screen.gotoXY(m_width+1, 0);
    for (int y = 0; y < m_height+1; y++)
    {
        screen.printChar('@');
        screen.gotoXY(m_width+1, y);
    }
    
    screen.gotoXY(0, m_height);
    for (int x = 0; x < m_width+3; x++)
    {
        screen.printChar('@');
        screen.gotoXY(x, m_height);
    }
}
