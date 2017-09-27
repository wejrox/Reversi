/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : JAMES MCDOWELL
 * Student Number   : S3540510
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Xiaodong Li
 **********************************************************************/
#include "game.h"
#include <time.h>

#define OK	 0
#define NO_INPUT 1
#define TOO_LONG 2
#define BUFFERSIZE 10

Player * playGame(Player * first, Player * second)
{
	Player * player1;
	Player * player2;
	time_t t;
	Cell board[BOARD_HEIGHT][BOARD_WIDTH];
	Boolean playGame = TRUE;
	/* Board check */
	Boolean foundBlank = FALSE;
	int i, j;
	
	/* Seed random token */
	srand((unsigned) time(&t));
	
	initFirstPlayer(first);
	initSecondPlayer(second, first->token);
	
	/* Set initial Player */
	if(first->token == RED)
	{
		player1 = first;
		player2 = second;
	}
	else
	{
		player1 = second;
		player2 = first;
	}
    
    /* Initialise Board */ 
    initBoard(board);
    
    /* Play Game Loop */
    while(playGame)
    {
    	/* Update player score */
    	player1->score = gameScore(board, player1->token);

    	/* Handle game completion due to no moves */
    	for(i = 0; i < BOARD_HEIGHT; i++)
    	{
    		for(j = 0; j < BOARD_WIDTH; j++)
    		{
    			if(board[i][j] == BLANK)
    			{
    				foundBlank = TRUE;
    			}
    		}
    	}
    	if(!foundBlank)
    	{
    		printf("There are no more valid moves to make.\nThe scores will now be tallied!\n");
    		break;
    	}
    	
    	/* Show the board */
    	displayBoard(board, player1, player2);
    	
    	/* Make move for current player */
    	playGame = makeMove(player1, board);
    	
    	/* Swap player turn */
    	swapPlayers(&player1, &player2); 
    }
    
    /* Calculate Scores */
    player1->score = gameScore(board, player1->token);
    player2->score = gameScore(board, player2->token);
    
    /* Decide upon winner */
    if(player1->score > player2->score)
    {
    	return player1;
    }
    else if (player1->score < player2->score)
    {
    	return player2;
    }
    
    /* Draw */
    return NULL;
}

Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
    char buffer[BUFFERSIZE + NULL_SPACE];
    char *ptr;
    /* If it's a number */
    char * sx;
    char * sy;
    long x = 0;
    long y = 0;
    int i, j;
    Boolean moveValid = FALSE;
    /* Move availability */
    int countAvailable = 0;

    /* Set the slot we can move in, as well as how many are available */
	for(i = 0; i < BOARD_HEIGHT; i++)
	{
		for(j = 0; j < BOARD_WIDTH; j++)
		{
			if(board[i][j] == BLANK)
			{
				x = i;
				y = j;
				++countAvailable;
			}
		}
	}

	/* If there is only one available, attempt that move.
	 * If that move fails, skip the turn! */
	if(countAvailable == 1 && applyMove(board, y, x, player->token))
	{
		return TRUE;
	}
	else if ((countAvailable == 1 && !applyMove(board, y, x, player->token)) || countAvailable == 0)
	{
		/* There are no more valid moves, finish the game */
		return FALSE;
	}

	/* Show the player which token they are */
	if(player->token == 1)
		printf("It is %s's turn. (Score: %d, Token: " COLOR_RED "%s" COLOR_RESET ")\n", player->name, player->score, "O");
	else if (player->token == 2)
		printf("It is %s's turn. (Score: %d, Token: " COLOR_CYAN "%s" COLOR_RESET ")\n", player->name, player->score, "O");

    printf("Please enter a co-ordinate in the form 'x,y' to attempt a move\n");
    
    /* Loop until move is inside bounds and valid */
    while(!moveValid)
    {
    	if(fgets(buffer, BUFFERSIZE + EXTRA_SPACES, stdin) != NULL)
    	{
    		if(buffer[0] == '\n')
    			return FALSE;
    	    
    	    if(buffer[strlen(buffer) - 1] != '\n')
    	    	readRestOfLine();
    	}    	
    	
    	sx = strtok(buffer, ",\r\n\t");    	
    	sy = strtok(NULL, ",\r\n\t");
    	
    	if(sx == NULL || sy == NULL)
    	{
    		printf("Invalid input, please try again.\n");
    	    continue;
    	}
    	
    	x = strtol(sx, &ptr, 10);
    	y = strtol(sy, &ptr, 10);
    	
    	/* Array 0 based */
    	--x;
    	--y;
    	
    	/** Make sure move is Game-Valid **/
    	/* Within array bounds */
    	if(x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_WIDTH)
    	{
    		/* Try to apply move, re-loop if it's errored */ 
    		if(applyMove(board, y, x, player->token))
    			moveValid = TRUE;
    		else
    			printf("Move not allowed, please try again\n");
    			
    	}
    	else
    	{
    		printf("Position doesn't exist, please try again.\n");
    	}
    }
    
    /* Move successful */
    return TRUE;
}

Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token)
{
	Cell otherColor;
	Boolean finishedMove = FALSE;
	Boolean capComplete = FALSE;
	int nextLoc;
	int nextLocb;
	int endLoc = -1;
	int endLocb = -1;
	int i, j;
	
	/* Spot taken */
	if(board[y][x] != BLANK)
		return FALSE;
	
	/* Set the piece to take */	
	if(token == RED)
		otherColor = CYAN;
	else
		otherColor = RED;
		
	/* Above to Below */
	if(y + BOARD_EDGE < BOARD_HEIGHT)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		nextLoc = y + 1;
		while(!capComplete)
		{
			/* Found an enemy */
			if(board[nextLoc][x] == otherColor)
			{
				++nextLoc;
				continue;
			}
			/* Found our piece */
			else if(board[nextLoc][x] == token)
			{
				endLoc = nextLoc;
				if(endLoc > y + 1)
					capComplete = TRUE;
				else
					break;
			}
			/* We can't flip it */
			else if(board[nextLoc][x] == BLANK)
				break;
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
		
			/* Take pieces in between */
			for(i = y; i < endLoc; ++i)
			{
				board[i][x] = token;
			}
			
			finishedMove = TRUE;
		}
	}
	
	/* Reset capture status */
	capComplete = FALSE;
	
	/* Below to Above */
	if(y - BOARD_EDGE > 0)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		nextLoc = y - 1;
		while(!capComplete)
		{
			/* Found an enemy */
			if(board[nextLoc][x] == otherColor)
			{
				--nextLoc;
				continue;
			}
			/* Found our piece */
			else if(board[nextLoc][x] == token)
			{
				endLoc = nextLoc;
				if(endLoc < y - 1)
					capComplete = TRUE;
				else
					break;
			}
			/* We can't flip it */
			else if(board[nextLoc][x] == BLANK)
				break;
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
		
			/* Take pieces in between */
			for(i = y; i > endLoc; --i)
			{
				board[i][x] = token;
			}
			
			finishedMove = TRUE;
		}
	}
	
	/* Reset capture status */
	capComplete = FALSE;
	
	/* Left to Right */
	if(x + BOARD_EDGE < BOARD_WIDTH)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		nextLoc = x + 1;
		while(!capComplete)
		{
			/* Found an enemy */
			if(board[y][nextLoc] == otherColor)
			{
				++nextLoc;
				continue;
			}
			/* Found our piece */
			else if(board[y][nextLoc] == token)
			{
				endLoc = nextLoc;
				if(endLoc > x + 1)
					capComplete = TRUE;
				else
					break;
			}
			/* We can't flip it */
			else if(board[y][nextLoc] == BLANK)
				break;
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
		
			/* Take pieces in between */
			for(i = x; i < endLoc; ++i)
			{
				board[y][i] = token;
			}
			
			finishedMove = TRUE;
		}
	}
	
	/* Reset capture status */
	capComplete = FALSE;
	
	/* Left to Right UP */
	if(x + BOARD_EDGE < BOARD_WIDTH && y - BOARD_EDGE > 0)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		endLocb = -1;
		nextLoc = x + 1;
		nextLocb = y - 1;
		while(!capComplete)
		{
			/* Found an enemy */
			if(board[nextLocb][nextLoc] == otherColor)
			{
				++nextLoc;
				--nextLocb;
				continue;
			}
			/* Found our piece */
			else if(board[nextLocb][nextLoc] == token)
			{
				endLoc = nextLoc;
				endLocb = nextLocb;
				if(endLoc > x + 1 && endLocb < y - 1)
					capComplete = TRUE;
				else
					break;
			}
			/* We can't flip it */
			else if(board[nextLocb][nextLoc] == BLANK)
				break;
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
		
			/* Take pieces in between */
			for(i = x, j = y; i < endLoc; ++i, --j)
			{
				board[j][i] = token;
			}
			
			finishedMove = TRUE;
		}
	}

	/* Reset capture status */
	capComplete = FALSE;

	/* Left to Right DOWN */
	if(x + BOARD_EDGE < BOARD_WIDTH && y + BOARD_EDGE < BOARD_HEIGHT)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		endLocb = -1;
		nextLoc = x + 1;
		nextLocb = y + 1;
		while(!capComplete)
		{
			/* Found an enemy */
			if(board[nextLocb][nextLoc] == otherColor)
			{
				++nextLoc;
				++nextLocb;
				continue;
			}
			/* Found our piece */
			else if(board[nextLocb][nextLoc] == token)
			{
				endLoc = nextLoc;
				endLocb = nextLocb;
				if(endLoc > x + 1 && endLocb > y + 1)
					capComplete = TRUE;
				else
					break;
			}
			/* We can't flip it */
			else if(board[nextLocb][nextLoc] == BLANK)
				break;
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
		
			/* Take pieces in between */
			for(i = x, j = y; i < endLoc; ++i, ++j)
			{
				board[j][i] = token;
			}
			
			finishedMove = TRUE;
		}
	}

	/* Reset capture status */
	capComplete = FALSE;
	
	/* Right to Left */
	if(x - BOARD_EDGE > 0)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		endLocb = 1;
		nextLoc = x - 1;
		nextLocb = y + 1;
		while(!capComplete)
		{
			/* Found an enemy */
			if(board[y][nextLoc] == otherColor)
			{
				--nextLoc;
				continue;
			}
			/* Found our piece */
			else if(board[y][nextLoc] == token)
			{
				endLoc = nextLoc;
				if(endLoc < x - 1)
					capComplete = TRUE;
				else
					break;
			}
			/* We can't flip it */
			else if(board[y][nextLoc] == BLANK)
				break;
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
		
			/* Take pieces in between */
			for(i = x; i > endLoc; --i)
			{
				board[y][i] = token;
			}
			
			finishedMove = TRUE;
		}
	}

	/* Reset capture status */
	capComplete = FALSE;

	/* Right to Left UP */
	if(x - BOARD_EDGE > 0 && y - BOARD_EDGE > 0)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		endLocb = -1;
		nextLoc = x - 1;
		nextLocb = y - 1;

		while(!capComplete)
		{
			/* Found an enemy */
			if(board[nextLocb][nextLoc] == otherColor)
			{
				--nextLoc;
				--nextLocb;
				continue;
			}
			/* Found our piece */
			else if(board[nextLocb][nextLoc] == token)
			{
				endLoc = nextLoc;
				endLocb = nextLocb;

				/* Complete if we've moved more than one piece */
				if(endLoc < x - 1 && endLocb < y - 1)
				{
					capComplete = TRUE;
				}
				else
					break;
			}
			/* We can't flip it */
			else if(board[nextLocb][nextLoc] == BLANK)
			{
				break;
			}
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
		
			/* Take pieces in between */
			for(i = x, j = y; i > endLoc; --i, --j)
			{
				board[j][i] = token;
			}
			
			finishedMove = TRUE;
		}
	}

	/* Reset capture status */
	capComplete = FALSE;

	/* Right to Left DOWN */
	if(x - BOARD_EDGE > 0 && y + BOARD_EDGE < BOARD_HEIGHT)
	{
		/* Reset amount of pieces */
		endLoc = -1;
		endLocb = 1;
		nextLoc = x - 1;
		nextLocb = y + 1;

		while(!capComplete)
		{
			/* Found an enemy */
			if(board[nextLocb][nextLoc] == otherColor)
			{
				--nextLoc;
				++nextLocb;
				continue;
			}
			/* Found our piece */
			else if(board[nextLocb][nextLoc] == token)
			{
				endLoc = nextLoc;
				endLocb = nextLocb;

				/* Complete if we've moved more than one piece */
				if(endLoc < x - 1 && endLocb > y + 1)
					capComplete = TRUE;
				else
					break;
			}
			/* We can't flip it */
			else if(board[nextLocb][nextLoc] == BLANK)
				break;
		}
		
		if(capComplete)
		{
			/* Place piece */
			board[y][x] = token;
			
			/* Take pieces in between */
			for(i = x, j = y; i > endLoc; --i, ++j)
			{
				board[j][i] = token;
			}
			
			finishedMove = TRUE;
		}
	}
		
	return finishedMove; 
}

unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	int i;
	int j;
	int count = 0;
	
	for(i = 0; i < BOARD_HEIGHT; ++i)
	{
		for(j = 0; j < BOARD_WIDTH; ++j)
		{
			if(board[i][j] == token)
				++count;
		}
	}
    return count;
}

void swapPlayers(Player ** first, Player ** second)
{ 
	Player *tmp = *first;
	*first = *second;
	*second = tmp;
}
