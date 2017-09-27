/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : JAMES MCDOWELL
 * Student Number   : S3540510
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Xiaodong Li
 **********************************************************************/
#include "gameboard.h"

void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{ 
	int i;
	int j;
	
	/* Set all to blank */
	for(i = 0; i < BOARD_HEIGHT; ++i)
	{
		for(j = 0; j < BOARD_WIDTH; ++j)
		{
			board[i][j] = BLANK;
		}
	}
	
	/* Initialise the 4 squares */
	board[3][3] = RED;
	board[3][4] = CYAN;
	board[4][3] = CYAN;
	board[4][4] = RED;
}

void displayBoard(
    Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second)
{
	int i;
	int j;
	
	/** First Line **/
	/* Initial space */
	printf("  ");
	for(i = 0; i < BOARD_WIDTH; ++i)
	{
		printf("   %d", i + 1);
	}
	printf("\n");
	
	/** Second Line **/
	for(i = 0; i < BOARD_CHAR_WIDTH; ++i)
	{
		printf("=");
	}
	printf("\n");
	
	/** Begin display loop **/
	/* For each horizontal line */
	for(i = 0; i < BOARD_HEIGHT; ++i)
	{
		printf(" %d |", i + 1);
		/* For each array element in that line */
		for(j = 0; j < BOARD_WIDTH; ++j)
		{
			/* Print whatever is contained */
			if(board[i][j] == RED)
			{
				printf(COLOR_RED " %s " COLOR_RESET, "O");
				printf("|");
			}
			else if (board[i][j] == CYAN)
			{
				printf(COLOR_CYAN " %s " COLOR_RESET, "O");
				printf("|");
			}
			/* Print blank if not either of those colours */
			else
			{
				printf("   |");
			}
		}
		
		/* Go to next line to print */
		printf("\n");
		
		/* Print the '-' or '=' */
		if(i < BOARD_HEIGHT - 1)
		{
			for(j = 0; j <= BOARD_CHAR_WIDTH - 1; ++j)
			{
				printf("-");
			}
		}
		else
		{
			for(j = 0; j <= BOARD_CHAR_WIDTH - 1; ++j)
			{
				printf("=");
			}
		}
		
		printf("\n");
	}
	
}
