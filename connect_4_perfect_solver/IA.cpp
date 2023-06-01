#include "ia.h"
#include <chrono>

int t_t_skips = 0;

ia::ia(board initial_board)
{
    
    //define an efficient exploration order, to optimise the pruning
    unsigned int x = initial_board.get_max_x();
    exploration_order_ = new int[x];
    for (unsigned int i = 0; i < x; i += 1) exploration_order_[i] = (x/2) + ((i+1)/2) * pow(-1, i);
    
}

unsigned int ia::solve(board position, const unsigned int player)
{
    return solve(position, player, position.max_moves_left());
}

unsigned int ia::solve(board position, const unsigned int player, const uint16_t depth)
{
    std::cout << "\nAI IS THINKING...\n" << std::flush;

    //set up variables
    t_t_skips = 0;
    unsigned int max_play = 0;
    int alpha = -depth; //smallest score possible
    int next_value;

    for (unsigned int i = 0; i < position.get_max_x(); i += 1)
    {
        const int move = exploration_order_[i];
        if (position.is_valid(move))
        {
            board next_pos  = position;
            next_pos.play(move, player);

            //handle all the cases: move not possible, move winning, other moves
            
            if (next_pos.win(player)) return move; //return if we get a win next turn
            
            if (next_pos.is_full()) next_value = 0;
            else next_value = - negamax(next_pos, (player+1)%2, depth - 1, - depth,  - alpha);

            std::cout << "Move " << move + 1 << " (or a previous one), has a minimal value of: " << next_value << "\n" << std::flush;
        
            if (next_value > alpha) //potentially update the max possible value and move
            {
                max_play = move;
                alpha = next_value;
            }
        }
    }
    std::cout << "number of transposition table skips: " << t_t_skips;
    return max_play;
}

int ia::dichotomic_negamax(board position, const unsigned int player, const uint16_t depth, int alpha, int beta)
{
    int inf = alpha;
    int sup = beta;
    
    while (inf < sup)
    {
        int m = inf + (sup - inf)/2;

        if(m <= 0 && inf/2 < m) m = inf/2;
        else if(m >= 0 && sup/2 > m) m = sup/2;

        const int r = negamax(position, player, depth, m, m+1);
        
        if (r <= m) sup = r;
        else inf = r;
    }

    return  inf;
}

int ia::negamax(board position, const unsigned int player, const uint16_t depth, int alpha, int beta)
{
    if (depth == 0) return depth;
    
    //transposition table lookup
    int max;
    const uint64_t t_t_key = position.get_key(player);
    const uint32_t t_t_index = t_t_.hash(t_t_key);

    //transposition table skips
    if (t_t_.has(t_t_index, t_t_key))
    {
        t_t_skips += 1;
        max = t_t_.get(t_t_index);
    }
    else max = depth;

    if (beta > max)
    {
        beta = max;
        if (alpha >= beta) return alpha; //pruning
    }
    

    for (unsigned int i = 0; i < position.get_max_x(); i += 1)
    {
        const int move = exploration_order_[i];
        if (position.is_valid(move))
        {
            board next_pos  = position;
            next_pos.play(move, player);

            //handle all the cases: move not possible, move winning, other moves
            
            if (next_pos.win(player))//returns if player can win this turn
            {
                t_t_.set(t_t_index, t_t_key, depth);
                return depth;
            }
            
            if (next_pos.is_full()) return 0;
            const int next_val = - negamax(next_pos, (player+1)%2, depth-1, -beta, -alpha);
            
            
            if (next_val >= beta) return next_val; //prune if we find something better than what we were looking for
            if (next_val > alpha) alpha = next_val;
            
        }
    }    
    t_t_.set(t_t_index, t_t_key, alpha);
    return alpha;
}
