#include "gtest/gtest.h"

#include "MB_04_10.hpp"

int main()
{
    Player player = Player();
    Opponent opponent = Opponent();
    
    Game game = Game();
    game.playOneRound(player, opponent);
        
    return 0;
}
