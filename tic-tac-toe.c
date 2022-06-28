#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];

struct moves {
    char PLAYER;
    char COMPUTER;
}e;

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinnner(char);

int main() {
    
    e.PLAYER = 'X';
    e.COMPUTER = 'Y';
    char winner = ' ';
    resetBoard();
    while (winner = ' ' && checkFreeSpaces() != 0) {
        printBoard();

        playerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }

        computerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }
    }

    printBoard();
    printWinnner(winner);
    return 0;
}
void resetBoard() {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpaces() {
    int freeSpaces = 9;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove() {
    int x;
    int y;
    do
    {
        printf("Enter Row Number (1-3) : ");
        scanf("%d", &x);
        x--;
        printf("Enter Column Number (1-3) : ");
        scanf("%d", &y);
        y--;
        if (board[x][y] != ' ') {
            printf("Invalid Move\n");
        }
        else {
            board[x][y] = e.PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
    
}

void computerMove() {
    srand(time(0));
    int x;
    int y;

    if (checkFreeSpaces() > 0) {
        do
        {
            x = rand()%3;
            y = rand()%3;
        } while (board[x][y] != ' ');
        
        board[x][y] = e.COMPUTER;
    }
    else {
        printWinnner(' ');
    }
}

char checkWinner() {
    //rows
    for (int i=0; i<3; i++) {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    //columns
    for (int i=0; i<3; i++) {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return board[0][i];
        }
    }
    //diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }

    return ' ';
}

void printWinnner(char winner) {
    FILE *p;
    p = fopen("outcome.txt", "w");
    if (winner == e.PLAYER) {
        fprintf(p, "%s", "You Win\n");
        printf("You win\n");
        fclose(p);
    }
    else if (winner == e.COMPUTER) {
        fprintf(p, "%s", "You Lose\n");
        printf("You lose\n");
        fclose(p);
    }
    else {
        fprintf(p, "%s", "It's a tie\n");
        printf("It's a tie");
        fclose(p);
    }
}

