/***
 * Name: printHelpers.h
 * Description: Function declarations for the printing
 *  helper functions defined in printHelpers.c
 */

#ifndef _PRINT_HELPERS_H
#define _PRINT_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "dominion.h"


#ifndef MAX_CARD_NAME_LENGTH
#define MAX_CARD_NAME_LENGTH 14
#endif

#ifndef DEBUG
#define DEBUG 1
#endif



/***************************************
 * card names
 ***************************************/

/* Gets the name of a card, given the card's integer value */
char* getCardName(int card);

/**
 * Helper function that wraps fprintf() and takes care of 
 * flushing the output buffer after printing.
 */
void print(FILE* stream, const char *format, ...);

/**
 * Helper function that wraps fprintf(stderr) and for easy error printing
 * by taking care of flushing the output buffer after printing.
 */
void printErr(const char *format, ...);

/**
 * Helper function that wraps fprintf(stdout) and for easy error 
 * printing by taking care of flushing the output buffer after printing.
 */
void printOut(const char *format, ...);

/* Prints a given test rule, if DEBUG is enabled */
void printDebugRule(const char* rule);

/* prints the contents of an integer array */
void printArray(int* arr, int size);

/* Prints an integer array, prefixed with a variadic set of output arguments */
void printArrayArgs(int* arr, int size, const char *format, ...);

/* Prints an integer array, prefixed with a string literal */
void printArrayPrefixed(int* arr, int size, const char* prefix);



/* Prints all the cards in the hand of a given player. */
void printHand(struct gameState* state, int player);

/* Prints all the cards in the hand of each player in the game. */
void printHands(struct gameState* state);

/* Prints all the cards in the deck of a given player. */
void printDeck(struct gameState* state, int player);

/* Prints all the cards in the deck of each player in the game. */
void printDecks(struct gameState* state);

/* Prints all the cards in the discard of a given player. */
void printDiscard(struct gameState* state, int player);

/* Prints all the cards in the discard of each player in the game. */
void printDiscards(struct gameState* state);

/* Prints various game state inforamation for a given game state. */
void printState(struct gameState* state);


#endif