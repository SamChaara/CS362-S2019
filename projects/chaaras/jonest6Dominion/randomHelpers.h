/***
 * Name: printHelpers.h
 * Description: Function declarations for the printing
 *  helper functions defined in printHelpers.c
 */

#ifndef _RANDOM_HELPERS_H
#define _RANDOM_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "dominion.h"


#ifndef MAX_CARD_NAME_LENGTH
  #define MAX_CARD_NAME_LENGTH 14
#endif

#ifndef DEBUG
  #define DEBUG 1
#endif


/* Generates and returns a random integer value. */
int randInt();

/**
 * Generates and returns a random integer value
 * in a specified range (inclusive).
 */
int randIntRange(int min, int max);

/* Checks if a specified integer value is present in an integer array */
bool inArray(int* arr, int size, int value);

/* Populates an integer array with random integer values. */
void randIntArr(int* arr, int size);

/* Populates an integer array with random integer values. */
void randIntArrRange(int* arr, int size, int min, int max);

/* Populates an array of kingdom cards w/ random kingdom card selections. */
void getRandomKingdomCards(int* arr);



/* Returns a random value from an array. */
int randFromArr(int* arr, int size);

/**
 * Populates a specified player's hand with a random amount of random
 * card selections, given the current cards in the game.
 */
void randomizePlayerHand(int* cards, struct gameState* state, int player);

/**
 * Populates a each player's hand with a random amount of cards
 * given a pool of cards to choose from.
 */
void randomizePlayerHands(int* cards, struct gameState* state);

/**
 * Populates a specified player's deck with a random amount of random
 * card selections, given the current cards in the game.
 */
void randomizePlayerDeck(int* cards, struct gameState* state, int player);

/**
 * Populates a each player's deck with a random amount of cards
 * given a pool of cards to choose from.
 */
void randomizePlayerDecks(int* cards, struct gameState* state);

/**
 * Populates a specified player's discard with a random amount of random
 * card selections, given the current cards in the game.
 */
void randomizePlayerDiscard(int* cards, struct gameState* state, int player);

/**
 * Populates a each player's discard with a random amount of cards
 * given a pool of cards to choose from.
 */
void randomizePlayerDiscards(int* cards, struct gameState* state);


#endif