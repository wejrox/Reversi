/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : JAMES MCDOWELL
 * Student Number   : S3540510
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Xiaodong Li
 **********************************************************************/
#include "player.h"
 
#define NUM_TOKENS 2

void initFirstPlayer(Player * player)
{ 
	/* Name */
	char buffer[NAMELEN + NULL_SPACE];
	
	/* Token */
	int tnum = -1;
	
	/* INIT */
	strcpy(player->name, EMPTY_STRING);
	player->token = BLANK;
	player->score = 0;
	
	/* Generate Token */
	tnum = rand() % NUM_TOKENS;
	
	/** Assign player name **/
	printf("Player 1, please enter your name\n");
	textInput(buffer);
	
	strcpy(player->name, buffer);
	
	/* Assign colour */
	switch(tnum)
	{
		case 0:
		player->token = RED;
		break;
		case 1:
		player->token = CYAN;
		break;
	}
}

void initSecondPlayer(Player * player, Cell token)
{ 
	/* Name */
	char buffer[NAMELEN + NULL_SPACE];
	
	/* INIT */
	strcpy(player->name, EMPTY_STRING);
	player->token = BLANK;
	player->score = 0;
	
	/** Assign player name **/
	printf("Player 2, please enter your name\n");
	
	textInput(buffer);
	
	strcpy(player->name, buffer);
	
	/* Assign colour */
	switch(token)
	{
		case 0:
		break;
		case 1:
		player->token = CYAN;
		break;
		case 2:
		player->token = RED;
		break;
	}
}

/**
 * Get text input for the string specified
 *
 * Input length won't exceed the length allocated to the string
 * User is informed when they have exceeded the allocated length
 * 
 * Buffer is consumed
 **/
void textInput(char * buffer)
{
	Boolean valid = FALSE;
	
	while(valid == FALSE)
	{ 
		/* Validate input within bounds */
		if(fgets(buffer, (int) sizeof(buffer), stdin) != NULL)
		{
			if(buffer[strlen(buffer) - 1] != '\n')
			{
				printf("Invalid input, please re-enter\n");
				readRestOfLine();
			}
			else
			{
				valid = TRUE;
			}
		}
	}
	buffer[strlen(buffer) - 1] = '\0';
}
