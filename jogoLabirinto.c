#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// -1 -> parede
// -2 -> ''
// -3 -> jogador
// -4 -> moeda
// -5 -> chave
// -6 -> porta

#define lin 2
#define col 5
#define prof 10

void escreverGame(int game[][prof]) {
    system("cls");

    printf("\n");
    printf("Tips: \nU/u -> move to up; D/d -> move to down; R/r -> move to right; L/l -> move to left\n");
    printf("# -> Walls; \033[34m @ \033[0m -> Player; \033[31m * \033[0m -> Coin; \033[33m ! \033[0m -> Key; \033[29m | \033[0m -> Door\n\n");

    int x,y;
    for( x = 0 ; x < col ; x++ ) {
        for( y = 0 ; y < prof ; y++ ) {
            if(game[x][y] == -1) printf("\033[00m###\033[0m");
            else if(game[x][y] == -2) printf("   ");
            else if(game[x][y] == -3) printf("\033[34m @ \033[0m");
            else if(game[x][y] == -4) printf("\033[31m * \033[0m");
            else if(game[x][y] == -5) printf("\033[33m ! \033[0m");
            else if(game[x][y] == -6) printf("\033[29m | \033[0m");
            else printf("%i ", game[x][y]);
        }
        printf("\n");
    }
}

int movingDone(int game[][prof], char toWhere, int playerLoc[2], int over, int thereIs, int *p) {
    int playerX = playerLoc[0];
    int playerY = playerLoc[1];

    if(toWhere == 'U' || toWhere == 'u') {
        if(game[playerX-1][playerY] == -4) over++;
        
        if((game[playerX-1][playerY] == -6 && thereIs) || (game[playerX-1][playerY] <= -2 && game[playerX-1][playerY] >= -5)) {   
            if(game[playerX-1][playerY] == -5) *p = 1;

            game[playerX-1][playerY] = -3;
            game[playerX][playerY] = -2; 
            playerLoc[0]--; 
        }
    } else if(toWhere == 'R' || toWhere == 'r') {
        if(game[playerX][playerY+1] == -4) over++;

        if((game[playerX][playerY+1] == -6 && thereIs) || (game[playerX][playerY+1] <= -2 && game[playerX][playerY+1] >= -5)) {
            if(game[playerX][playerY+1] == -5) *p = 1;

            game[playerX][playerY+1] = -3;
            game[playerX][playerY] = -2;
            playerLoc[1]++;
        }
    } else if(toWhere == 'D' || toWhere == 'd') {
        if(game[playerX+1][playerY] == -4) over++;

        if((game[playerX+1][playerY] == -6 && thereIs) || (game[playerX+1][playerY] <= -2 && game[playerX+1][playerY] >= -5)) {
            if(game[playerX+1][playerY] == -5) *p = 1;

            game[playerX+1][playerY] = -3;
            game[playerX][playerY] = -2;
            playerLoc[0]++;
        }
    } else if(toWhere == 'L' || toWhere == 'l') {
        if(game[playerX][playerY-1] == -4) over++;
        
        if((game[playerX][playerY-1] == -6 && thereIs) || (game[playerX][playerY-1] <= -2 && game[playerX][playerY-1] >= -5)) {
            if(game[playerX][playerY-1] == -5) *p = 1;

            game[playerX][playerY-1] = -3;
            game[playerX][playerY] = -2;
            playerLoc[1]--;
        }
    }

    return over;
}

void acharPlayer(int game[][prof], int locPlayer[2]) {
    int x,y;
    for( x = 0 ; x < col ; x++ ) {
        for( y = 0 ; y < prof ; y++ ) {
            if(game[x][y] == -3) {
                locPlayer[0] = x;
                locPlayer[1] = y;
            }
        }
    }
}

void preencherMapa(int game[][col][prof], int round[][prof], int profu) {
    int x,y;
    for( x = 0 ; x < col ; x++ ) {
        for( y = 0 ; y < prof ; y++ ) {
            round[x][y] = game[profu][x][y];
        }
    } 
}

int main() {
    int game[lin][col][prof] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                                -1,-2,-3,-2,-2,-5,-1,-4,-2,-1,
                                -1,-2,-1,-1,-1,-1,-1,-1,-2,-1,
                                -1,-2,-2,-6,-2,-2,-2,-2,-2,-1,
                                -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,//
                                -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                                -1,-2,-3,-2,-2,-5,-1,-4,-2,-1,
                                -1,-2,-1,-1,-1,-1,-1,-1,-2,-1,
                                -1,-2,-2,-6,-4,-2,-2,-2,-2,-1,
                                -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};

                            //    {-1,-1,-1,-1,-1,
                            //     -1,-2,-3,-2,-1,
                            //     -1,-1,-2,-1,-1,
                            //     -1,-2,-2,-2,-1,
                            //     -1,-2,-1,-5,-1,
                            //     -1,-6,-1,-1,-1,
                            //     -1,-2,-1,-2,-1,
                            //     -1,-2,-1,-1,-1
                            //     -1,-2,-2,-4,-1,
                            //     -1,-1,-1,-1,-1,//
                            //     -1,-1,-1,-1,-1,
                            //     -1,-1,-3,-4,-1,
                            //     -1,-1,-2,-1,-1,
                            //     -1,-2,-2,-2,-1,
                            //     -1,-2,-1,-5,-1,
                            //     -1,-6,-1,-1,-1,
                            //     -1,-2,-1,-2,-1,
                            //     -1,-2,-1,-1,-1
                            //     -1,-2,-2,-4,-1,
                            //     -1,-1,-1,-1,-1}

    int round[col][prof];
    int profu = 0;
    preencherMapa(game, round, profu);

    escreverGame(round);


    int over = 0, playerLoc[2], thereIs = 0, *p = &thereIs;

    int x,y,z;

    for( x = 0 ; x < lin ; x++ ) {
        acharPlayer(round, playerLoc);
        while(!over) {
            char move;
            printf("\nWrite the next move: ");
            scanf("%c", &move);
            over = movingDone(round, move, playerLoc, over, thereIs, p);

            escreverGame(round);
        }
        printf("\nCongrutalion, you find the coin!\n");
        over--;
        profu++;
        // printf("%i\n", profu);
        // getch();
        if(profu < lin) preencherMapa(game, round, profu);
    }

    // for(x = 0; x < col; x++) {
    //     for(y = 0; y < prof; y++) {
    //         printf("%i", round[x][y]);
    //     }
    //     printf("\n");
    // }
    getch();
    system("cls");
    escreverGame(round);
    printf("\nThank u for play my game! :)\n");

    return 0;
}