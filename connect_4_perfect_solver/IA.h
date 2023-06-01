#pragma once
#include "Board.h"
#include "Transposition_Table.h"

class ia
{
private:
    int dichotomic_negamax(board position, unsigned int player, uint16_t depth, int alpha, int beta);
    int negamax(board position, unsigned int player, uint16_t depth, int alpha, int beta);
    transposition_table t_t_ = transposition_table(100000000);
    int *exploration_order_;
    
public:
    ia(board initial_board);
    unsigned int solve(board position, unsigned int player); //solves until the end of the game
    unsigned int solve(board position, unsigned int player, uint16_t depth);
    
};
