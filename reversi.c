/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : JAMES MCDOWELL
 * Student Number   : S3540510
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Xiaodong Li
 **********************************************************************/
#include "reversi.h"
#include <unistd.h> /* Sleep */
int main()
{
	/* Menu option */
	char menOp[MENUOPTIONS + NULL_SPACE][MAXOPTIONLENGTH];
	/* Selected option */
	char op[1 + NULL_SPACE];
	int i;
	
	/* Create players */
	Player player1;
	Player player2;
	
	/* Winner */
	Player *winner;
	
	/* Init options */
	strcpy(menOp[0], "Play Game");
	strcpy(menOp[1], "Exit Game");
	
	while(TRUE)
	{
		/* Reset the option */
		strcpy(op, "");
		
		printf("Welcome to Reversi!\n");
		printf("===================\n");
		printf("Select an option:\n");
		for(i = 0; i < MENUOPTIONS; ++i)
		{
			printf("%d. %s\n", i + 1, menOp[i]);
		}
		
		printf("Please enter your choice\n");
		
		/* Get input until correct */
		while(op[0] != '1' && op[0] != '2')
		{
			textInput(op);
		}
		
		/* Start game or quit */
		if(op[0] == '1')
			winner = playGame(&player1, &player2);
		else
			break;
	
		if(winner->name == NULL)
			printf("The match was a draw!\n\n");
		else
			printf("The winner of the match was %s, on %d points!\n\n", winner->name, winner->score);
    }
    
    return EXIT_SUCCESS;
}
