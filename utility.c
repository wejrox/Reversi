/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : JAMES MCDOWELL
 * Student Number   : S3540510
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Xiaodong Li
 **********************************************************************/
#include "utility.h"

void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}
