
#include <chrono>

#include "Board.h"
#include "IA.h"
#include <iostream>


int main(int argc, char* argv[])
{
    //board definition
    board b;
    unsigned int input, x, y;

    std::cout << "With how many columns (x) do you want to play ?\n--> ";
    std::cin >> x;

    std::cout << "With how many rows (y) do you want to play ?\n--> ";
    std::cin >> y;

    if (x*y > 64-y or x*y == 0)
    {
        b = board();
        std::cout << "You entered invalid dimentions !\nThe board will therefore take its default size\n";
    }
    else b = board(x , y);

    //IA definition
    ia i = ia(b);
    
    std::cout << "Do you want to play with an AI ?\nPress [1] if yes\n--> ";
    std::cin >> input;
    
    bool play_with_robot = false;
    if (input == 1) play_with_robot = true;
    
    bool playing = true;
    int move, current_player = -1;

    while (playing)
    {
        current_player = (current_player+1)%2;
        std::cout << "\n\n------------------------------------\n"
                     "This is the current board :\n\n" << b.to_str();

        //play
        if (current_player <= 1 and play_with_robot) 
        {
            auto start = std::chrono::high_resolution_clock::now();
            move = i.solve(b, current_player);
            std::cout << "\nIA took: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() << " s, to calculate this position\n";
        }
        else
        {
            std::cout << "What move do you wanna make, player " << current_player+1 <<" ?\n--> ";
            std::cin >> move;
            while (not b.is_valid(move - 1))
            {
                std::cout << "This move isn't possible\nWhat move do you wanna make, player " << current_player+1 <<" ?\n--> ";
                std::cin >> move;
            }
            move -= 1;
        }
        

        
        b.play(move, current_player);
        
        if (b.win(current_player))
        {
            std::cout << "\nGame over\n\n" << b.to_str() << "\n\n";
            std::cout << "Player " << current_player+1 << " won\n";
            playing = false;
        }
        
        else{ if (b.is_full())
        {
            std::cout << "\nGame over\n\n" << b.to_str() << "\n\n";
            std::cout << "It's a draw\n";
            playing = false;
        }}
    }

    std::cout << "\nPress a random key, and then [Enter] to exit the window\n";
    std::cin >> input; //has_AI is just a placeholder
    
    return 0;
}
