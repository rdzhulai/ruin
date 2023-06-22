#include "game.h"
#include "world.h"
#include <stdlib.h>

int main()
{
    struct game *game = create_game();
    play_game(game);
    game = destroy_game(game);
    return 0;
}