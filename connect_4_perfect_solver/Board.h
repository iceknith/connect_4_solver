#pragma once
#include <iostream>

class board
{
private:
    uint64_t players_[2] = {0,0};
    uint64_t bottom_row_;
    uint64_t *line_masks_;
    
    uint16_t max_x_, max_y_;
    uint16_t num_move_ = 0, max_mooves_;
    
public:
    board();
    board(int x, int y);

    uint16_t get_max_x();
    uint16_t get_max_y();
    uint64_t get_bit_board(uint8_t player);
    uint64_t get_key(uint8_t player);
    uint16_t max_moves_left();
    
    std::string to_str();
    bool is_valid(unsigned int x);
    bool is_full();
    void play(unsigned int x, unsigned int player); //returns true if win
    bool win(unsigned int player);
};
