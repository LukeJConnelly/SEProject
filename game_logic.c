/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
	int i, j, selectedSquare=0;
	int minNumOfTokens=0;
	printf("It's time to place the counters. On your turn, please enter the corresponding vertical number to where you would like to place your counter on the board\n");
	for (i=0;i<4;i++)
	{
		for (j=0;j<numPlayers;j++)
		{
			printf("Player %d: Please choose where you would like your counter %d to be placed.\n", j+1, i+1);
			scanf("%d",&selectedSquare);
			while(selectedSquare>=NUM_ROWS||selectedSquare<0)
			{
				printf("Sorry, A token cannot be place here as it is off the board\n");
				scanf("%d",&selectedSquare);
			}
			if (board[selectedSquare][0].stack!=NULL)
			{
				while(board[selectedSquare][0].numTokens>minNumOfTokens)
				{
					printf("Sorry, a token can not be placed here as it currently has more tokens than the other squares.\nPlease re-enter:\n");
					scanf("%d",&selectedSquare);
				}
				while(board[selectedSquare][0].stack->col==players[j].col)
				{
					printf("Sorry, a token can not be placed here as it currently holds one of your tokens on top of the stack.\nPlease re-enter:\n");
					scanf("%d",&selectedSquare);
				}
			}
			board[selectedSquare][0].stack=(token*)malloc(sizeof(token));
			board[selectedSquare][0].stack->col=players[j].col;
			board[selectedSquare][0].numTokens++;
			if(((numPlayers*i)+j+1)%NUM_ROWS==0)
			{
				minNumOfTokens++;
			}
		}
	}
}


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int i, dice, vertMove, X, Y;
	srand(time(NULL));
	printf("It's time to play the game. On your turn, the dice will be rolled, you will be given the option to move a piece vertically and then you will move a token in the column corresponding to the dice. Lets play!\n");
	for (i=0;i<numPlayers;i++)
	{
		dice=(rand()%6)+1;
		printf("Hi player %d! The dice has rolled: %d", i, dice);
		printf("Would you like to move a piece vertically? 0 for no, 1 for yes\n");
		scanf("%d", &vertMove);
		while (vertMove!=0&&vertMove!=1)
		{
			printf("This wasn't recognized as an input. Please re-enter:\n");
			scanf("%d", &vertMove);
		}
		if (vertMove==1)
		{
			printf("Please enter the xy value of the token you would like to move.\n");
			printf("x:");
			scanf("%d", &X);
			printf("y:");
			scanf("%d", &Y);
			while(board[Y][X].stack->col!=players[i].col)
			{
				printf("We couldn't find one of your tokens here. Please re-enter.\n");
				printf("x:");
				scanf("%d", &X);
				printf("y:");
				scanf("%d", &Y);
			}
			printf("Okay, would you like to move up or down? Please enter 0 for down, 1 for up.\n");
			scanf("%d", &vertMove);
			while (vertMove!=0&&vertMove!=1)
			{
				printf("This wasn't recognized as an input. Please re-enter:\n");
				scanf("%d", &vertMove);
			}
			printf("Sure thing!\n");
			// NEEDS A LINE TO REMOVE THE COLOUR FROM THE STACK HERE
			board[Y][X].numTokens--;
			if(vertMove==0)
			{
				board[Y+1][X].stack=(token*)malloc(sizeof(token));
				board[Y+1][X].stack->col=players[i].col;
				board[Y+1][X].numTokens++;
			}
			else
			{
				board[Y-1][X].stack=(token*)malloc(sizeof(token));
				board[Y-1][X].stack->col=players[i].col;
				board[Y-1][X].numTokens++;
			}
		}
		printf("Please enter the x value of the token you would like to move in row %d.\n", dice-1);
		printf("x:");
		scanf("%d", &X);
		while(board[dice-1][X].stack->col!=players[i].col)
		{
			printf("We couldn't find one of your tokens here. Please re-enter.\n");
			printf("x:");
			scanf("%d", &X);
		}
		printf("Sure thing, I'll move that token now!\n");
		// NEEDS A LINE TO REMOVE THE COLOUR FROM THE STACK HERE
		board[dice-1][X].numTokens--;
		board[dice-1][X+1].stack=(token*)malloc(sizeof(token));
		board[dice-1][X+1].stack->col=players[i].col;
		board[dice-1][X+1].numTokens++;
		if(X+1==8)
		{
			printf("This token has reached the end!\n");
			players[i].numTokensLastCol++;
		}
		if(players[i].numTokensLastCol==3)
		{
			printf("Congratulations to player %d! They have won the game!\n", i);
			//some kind of endgame function will go here, or like some break statements
		}
		else
		{
			printf("End of turn.\n\n");
			//could print the board a couple times in this whole process but atm cba because of stacks
		}
	}
}



