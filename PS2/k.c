#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "k.h"


// void add_random_tile(struct game *game){
//     int row, col;
//     // find random, but empty tile
//     do{
//         row = rand() % SIZE;
//         col = rand() % SIZE;
//     }while(game->board[row][col] != ' ');

//     // place to the random position 'A' or 'B' tile
//     if(rand() % 2 == 0){
//         game->board[row][col] = 'A';
//     }else{
//         game->board[row][col] = 'B';
//     }
// }

bool is_game_won(const struct game game)
{
   
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(game.board[i][j]=='K')
            {
                return 1;
            }
        }
    }
    return 0;
}

bool is_move_possible(const struct game game){
    
    bool ren=false;
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
           if(game.board[i][j] == ' ') {
                ren = true;
            }
            if(i < SIZE - 1 && game.board[i][j] == game.board[i + 1][j]) {
                ren = true;
            }
            if(j < SIZE - 1 && game.board[i][j] == game.board[i][j + 1])
            {
                return true;
            }
        }
    }
    return ren;
}
// int letter_value(char letter) {
//     switch (letter) {
//         case 'A': return 2;
//         case 'B': return 4;
//         case 'C': return 8;
//         case 'D': return 16;
//         case 'E': return 32;
//         case 'F': return 64;
//         case 'G': return 128;
//         case 'H': return 256;
//         case 'I': return 512;
//         case 'J': return 1024;
//         case 'K': return 2048;
//         default: return 0;
//     }
// }
void combine_tiles(char *tile1, char *tile2, int *score) {
    if (*tile1 == ' ') {
        *tile1 = *tile2;
    } else if (*tile1 == *tile2) {
        *tile1 += 1;
        *score += 1 << (*tile1 - 'A' + 1);
        *tile2 = ' ';
    }

}
void up(struct game *game,bool *game_state)
{
        for (int j = 0; j < SIZE; j++) {
                for (int i = 1; i < SIZE; i++) {
                    if (game->board[i][j] != ' ') {
                        int a = i;
                        while (a > 0 && game->board[a - 1][j] == ' ') {
                            game->board[a - 1][j] = game->board[a][j];
                            game->board[a][j] = ' ';
                            a--;
                            *game_state = true;
                        }
                        if (a > 0) {
                            combine_tiles(&game->board[a - 1][j], &game->board[a][j], &game->score);
                        }
                    }
                }
            }
    
}
void down(struct game *game,bool *game_state)
{
   for (int j = 0; j < SIZE; j++) {
                for (int i = SIZE - 2; i >= 0; i--) {
                    if (game->board[i][j] != ' ') {
                        int k = i;
                        while (k < SIZE - 1 && game->board[k + 1][j] == ' ') {
                            game->board[k + 1][j] = game->board[k][j];
                            game->board[k][j] = ' ';
                            k++;
                            *game_state = true;
                        }
                        if (k < SIZE - 1) {
                            combine_tiles(&game->board[k + 1][j], &game->board[k][j], &game->score);
                        }
                    }
                }
            }
    
}
void right(struct game *game,bool *game_state)
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 2; j >= 0; j--) {
            if (game->board[i][j] != ' ') {
                int k = j;
                while (k < SIZE - 1 && game->board[i][k + 1] == ' ') {
                    game->board[i][k + 1] = game->board[i][k];
                    game->board[i][k] = ' ';
                    k++;
                    *game_state = true;
                }
                if (k < SIZE - 1) {
                    combine_tiles(&game->board[i][k + 1], &game->board[i][k], &game->score);
                }
            }
        }
    }
}

void left(struct game *game,bool *game_state)
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (game->board[i][j] != ' ') {
                int k = j;
                while (k > 0 && game->board[i][k - 1] == ' ') {
                    game->board[i][k - 1] = game->board[i][k];
                    game->board[i][k] = ' ';
                    k--;
                    *game_state = true;
                }
                if (k > 0) {
                    combine_tiles(&game->board[i][k - 1], &game->board[i][k], &game->score);
                }
            }
        }
    }

}

bool update(struct game *game, int dy, int dx) {
    bool game_state = false;
    if((dy>1||dy<-1||dx>1||dx<-1)||(dy!=0&&dx!=0)||(dx==0&&dy==0))
    {
        return false;
    }
    
    if (dy != 0) {
        if (dy == -1) {
            up(game,&game_state);
        }
        else if (dy == 1) {
            down(game,&game_state);
        }
    }

    if (dx != 0) {
        if (dx == -1) {
           left(game,&game_state);
        }
        
        else if (dx == 1) {
            right(game,&game_state);
        }
    }

    return game_state;
}