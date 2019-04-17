/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
			board[i][j].numTokens = 0;
            board[i][j].stack = NULL;
        }
    }
}
    
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
	int p=0, i;
	printf("\n");
	printf("Hey User! Please enter the number of players you wish to use for this game. It must be between 2 and 6.\n");
	while (p<2||p>6)
	{
		scanf("%d",&p);
		if (p<2||p>6)
		{
			printf("Sorry this is not a recognized input, please re-enter:\n");
		}
	}
	printf("Thank you. %d players will play this game.\n", p);
	printf("\n");
	while (getchar()!='\n');
	for (i=0;i<p;i++)
	{
		printf("Please enter the name for player %d\n", i+1);
		gets(players[i].name);
	}
	printf("\n");
	for (i=0;i<p;i++)
	{
		printf("Player %d: %s\n", i+1, players[i].name);
	}
return p;
}
    
   
     

