#ifndef WELL_INCLUDED
#define WELL_INCLUDED

class Screen;
class Piece;

class Well
{
public:
    Well(int width, int height);
    
    int width();
    int height();
    char get_well(int x, int y) const;
    bool set_well(int x, int y, char val);
    void fixPiece(Piece &p);
    void clear_row(int n);
    int clear_rows();
    void clear_well();
    void display(Screen& screen, int x, int y, bool flag = false);
    bool check_well_boundary(int x, int y) const;
    bool filled(int x, int y) const;
    
private:
    void print_well(Screen& screen); 
    
    int m_width;
    int m_height;
    char m_well[10][18];
};

#endif // WELL_INCLUDED
