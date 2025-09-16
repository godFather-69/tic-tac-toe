#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

int difficulty;

typedef struct Score
{
    int playerScore;
    int compScore;
    int draw;
} Score;

Score score = {.playerScore = 0, .compScore = 0, .draw = 0};

void clearScreen(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    
    #endif
}

void inputDifficulty(){
    while(1){
        printf("\nSelect difficulty level: ");
        printf("\n1. Normal Mode");
        printf("\n2. God (Impossible to win)");
        printf("\nEnter your choice: ");

        scanf("%d", &difficulty);
        if (difficulty != 1 && difficulty != 2){
            printf("\nIncorrect choice. Enter (1/2)");
        } else {
            break;
        }
    };

        
}

int checkWinner(char board[BOARD_SIZE][BOARD_SIZE], char player){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] ==  player && board[i][2] ==  player){
            return 1;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player){
            return 1;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player){
            return 1;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player){
            return 1;
        }        
    }

    return 0;
    
}

int checkDraw(char board[BOARD_SIZE][BOARD_SIZE]){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' '){
                return 0;
            }            
        }        
    }

    return 1;
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE]){
    clearScreen();
    printf("\n-----------------------Score-----------------------");
    printf("\n Your Score = %d | ", score.playerScore);
    printf("Computer Score = %d | ", score.compScore);
    printf("Draws = %d", score.draw);

    printf("\nTic - Tac - Toe\n");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("\n");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1){
                printf("|");
            }
            
        }

        if(i < BOARD_SIZE - 1){
        printf("\n---+---+---"); 
        }
    }
    
}

int isValidRule(char board[BOARD_SIZE][BOARD_SIZE], int row, int col){
    return (row < 0 || col < 0 || row > 2 || col > 2 || board[row][col] != ' ');
}

void playerMove(char board[BOARD_SIZE][BOARD_SIZE]){
    int count = 0, x, y;

    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[i][j] == ' '){
                count++;
                x = i;
                y = j;
            } 
        }        
    }
    if (count == 1){
        board[x][y] = X;
    }

    int row, col;
    do{
    printf("\nPlayer X's turn: ");
    printf("\nEnter row and column(1-3):  ");
    scanf("%d %d", &row, &col);
    row--; col--;
    }while(isValidRule(board, row, col));

    board[row][col] = X;
}

int isMovesLeft(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ')
                return 1;
    return 0;
}

int evaluate(char board[BOARD_SIZE][BOARD_SIZE]) {
    if (checkWinner(board, O)) return +10;
    if (checkWinner(board, X)) return -10;
    return 0;
}

int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, int isMax) {
    int score = evaluate(board);
    if (score == 10 || score == -10)
        return score - depth; // favor quicker wins, slower losses
    if (!isMovesLeft(board))
        return 0;

    int best = isMax ? -1000 : 1000;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = isMax ? O : X;
                int value = minimax(board, depth + 1, !isMax);
                best = isMax ? (value > best ? value : best) : (value < best ? value : best);
                board[i][j] = ' ';
            }
        }
    }
    return best;
}

void computerMove(char board[BOARD_SIZE][BOARD_SIZE]) {
    int bestVal = -1000;
    int bestMoveRow = -1, bestMoveCol = -1;

    // Immediate win or block
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                // Check immediate win
                board[i][j] = O;
                if (checkWinner(board, O)) return;
                board[i][j] = ' ';

                // Check block
                board[i][j] = X;
                if (checkWinner(board, X)) {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // God mode using Minimax
    if (difficulty == 2) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = O;
                    int moveVal = minimax(board, 0, 0);
                    board[i][j] = ' ';
                    if (moveVal > bestVal) {
                        bestMoveRow = i;
                        bestMoveCol = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        if (bestMoveRow != -1 && bestMoveCol != -1) {
            board[bestMoveRow][bestMoveCol] = O;
            return;
        }
    }

    // Fallback: pick center, corner, or first available
    if (board[1][1] == ' ') {
        board[1][1] = O;
        return;
    }

    int corners[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
    for (int i = 0; i < 4; i++) {
        int r = corners[i][0], c = corners[i][1];
        if (board[r][c] == ' ') {
            board[r][c] = O;
            return;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ') {
                board[i][j] = O;
                return;
            }
}

void computerMovee(char board[BOARD_SIZE][BOARD_SIZE]){
    // 1. Play for Immediate win
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (checkWinner(board, O)){
                    return; 
                }
                board[i][j] = ' '; 
                
            }   
        }
    }


    // 2. Play for Immediate Block
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[i][j] == ' ')
            {
                board[i][j] = X;
                if (checkWinner(board, X)){
                    board[i][j] = O;
                    return; 
                }
                board[i][j] = ' '; 
                
            }   
        }
    }

    // GOD Mode
    if(difficulty == 2){
        // 3. Play at the center if available
        if (board[1][1] == ' '){
            board[1][1] = O;
            return;
        }
        
        // 4. Play in corner if available
        int corner[4][2] = {{0, 0}, {0, 2}, {2, 0},{2, 2}};
        for (int i = 0; i < 4; i++)
        {
            if (board[corner[i][0]][corner[i][1]] == ' '){
                board[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }

    // 5. Play first available
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[i][j] == ' '){
                board[i][j] = O;
                return;
            }   
        }
    }
}

void playGame(){
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char currentPlayer = rand() % 2 == 0 ? X : O;

    while(1){
        printBoard(board);

        if (currentPlayer == X){
            playerMove(board); 
            if (checkWinner(board, X)){
                score.playerScore++;
                printBoard(board);
                printf("\nCongratulations You've won!!!\n");
                break;
            }
            currentPlayer = O;
            printf("\nHello Hello Hello\n");
        } 
        else{
            computerMove(board);
            if (checkWinner(board, O))
            {
                score.compScore++;
                printBoard(board);
                printf("\nOh Yes!! I won the match\n");
                break;
            }
            currentPlayer = X;
        }
        if (checkDraw(board))
        {
            score.draw++;
            printBoard(board);
            printf("\nIt's a draw!");
            break;
        }
    }

}

int main(){
    srand(time(NULL));
    char choice;
    inputDifficulty();
    do
    {
        playGame();
        while(getchar() != '\n');
        printf("\nDo you want to play again?[y/n]: ");
        choice = getchar();
        
    } while (tolower(choice) == 'y');
    
    printf("\nBye bye... Thanks for playing\n");
    return 0;
}
