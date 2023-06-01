#include "Board.h"

#include <iostream>
#include <string>
#include <math.h>
using std::string;


board::board() : board(7,6) {}

board::board(const int x, const int y)
{
    max_x_ = x;
    max_y_ = y;
    max_mooves_ = x*y;
    
    max_y_ += 1; //adding one "invisible" row to prevent bugs in the collision detection

    bottom_row_ = 1;
    for (int i = 1; i < max_x_; ++i) bottom_row_ += 1ull << i*max_y_;

    line_masks_ = new uint64_t[x];
    for (int i = 0; i < max_x_; ++i) line_masks_[i] = ((1ull << max_y_) - 1) << i*max_y_;
}


uint16_t board::get_max_x() {return max_x_;}

uint16_t board::get_max_y() {return max_y_;}

uint64_t board::get_bit_board(const uint8_t player) {return players_[player];}

uint64_t board::get_key(const uint8_t player)
{
    const uint8_t player2 = (player+1)%2;
    return (players_[player] | players_[player2]) + players_[player2] + bottom_row_;
}

uint16_t board::max_moves_left() {return max_mooves_ - num_move_;}

string board::to_str()
{
    string board = "";
    uint64_t mask = 1u;

    //get the board and turning it 90 degrees
    for (unsigned int y = 1; y < max_y_; y += 1)
    {
        string line = "";
        for (unsigned int x = 1; x <= max_x_; x += 1)
        {
            //display the correct symbols
            if (players_[0] & mask) {line += "| X ";}
            else
            {
                if(players_[1] & mask) {line += "| O ";}
                else {line += "|   ";}
            }
            
            mask <<= max_y_; //we change rows
        }
        
        mask = 1ull << y; //we change lines
        board = line + "|" + "\n" + board; //add all the lines together
    }

    string first_line = "";
    for (int i = 1; i <= max_x_; i += 1) first_line += "| " + std::to_string(i) + " ";
    
    return first_line + "|\n" + board;
}

bool board::is_valid(const unsigned int x)
{
    const uint64_t mask = 1ull << (max_y_ - 2 + max_y_ * x); //detect the second block on top, to create an "invisible" row
    return x < max_x_ and not ((players_[0] & mask) | (players_[1] & mask));
}

bool board::is_full()
{
    return num_move_ >= max_mooves_;
}

void board::play(const unsigned int x, const unsigned int player)
{
    const uint64_t line_mask = line_masks_[x];
    
    uint64_t line = ((players_[0] & line_mask) | (players_[1] & line_mask)) >> x*max_y_; //we take all the pieces on this column
    unsigned int y;
    for(y = 0; line != 0; y++) line >>= 1; //we find the highest piece's position
    
    players_[player] |= (1ull << (x*max_y_ + y)); //we add the played piece

    num_move_ += 1;
    
}

bool board::win(const unsigned int player)
{
    //horizontal check
    uint64_t intermediate_board = players_[player] & (players_[player] >> max_y_);
    if (intermediate_board & (intermediate_board >> max_y_*2)) {return true;}

    //vertical check
    intermediate_board = players_[player] & (players_[player] >> 1);
    if (intermediate_board & (intermediate_board >> 2)) {return true;}

    //diagonal / check
    intermediate_board = players_[player] & (players_[player] >> (max_y_ + 1));
    if (intermediate_board & (intermediate_board >> (max_y_*2 + 2))) { return true;}

    //diagonal \ check
    intermediate_board = players_[player] & (players_[player] >> (max_y_ - 1));
    if (intermediate_board & (intermediate_board >> (max_y_*2 - 2))) { return true;}
    
    return false;
}

