#include "Board.h"

#include <iostream>
using std::string;

class board
{
public:
    int players[2] = {0,0};
    int max_x, max_y;
    
    board() : board(8,8) {}
    board(int x, int y)
    {
        max_x = x;
        max_y = y;
    }

    string to_str()
    {
        
    }
    
};
