/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : JAMES MCDOWELL
 * Student Number   : S3540510
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Xiaodong Li
 **********************************************************************/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "player.h"

#define BOARD_HEIGHT 8
#define BOARD_WIDTH BOARD_HEIGHT
#define BOARD_CHAR_WIDTH 36

void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
void displayBoard(
    Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second);

#endif
