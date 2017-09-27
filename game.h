/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : JAMES MCDOWELL
 * Student Number   : S3540510
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Xiaodong Li
 **********************************************************************/
#ifndef GAME_H
#define GAME_H

#include "gameboard.h"

/* The amount of board spaces until the edge of the board */
#define BOARD_EDGE 2 

/**
 * All directions pieces can be captured in.
 * 
 * Note you are NOT required to use this enum if you don't want to.
 */
typedef enum direction
{
    NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST
} Direction;

Player * playGame(Player * first, Player * second);
Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token);
unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token);
void swapPlayers(Player ** first, Player ** second);

#endif
