/***
 * Name: randomHelpers.c
 * Description: Function that help with
 *  generating randomized values.
 */

#include "randomHelpers.h"


// 
// generating random integers
// 

/**
 * Generates and returns a random integer value.
 * @returns int
 */
int randInt() {
  return rand();
}

/**
 * Generates and returns a random integer value
 * in a specified range (inclusive).
 * 
 * @param min - the lowest allowed return value
 * @param max - the highest allowed return value.
 * @returns int
 */
int randIntRange(int min, int max) {
  if (min == max) {
    return min;
  }
  
  return (rand() % (max - min + 1)) + min;
}


//
// arrays
//

/**
 * Checks if a specified integer value is present in an integer array.
 * 
 * @param arr - a pointer to an integer array.
 * @param size - the number of integers in the array.
 * @param value - the value to look for.
 */
bool inArray(int* arr, int size, int value) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == value) {
      return true;
    }
  }

  return false;
}


/**
 * Populates an integer array with random integer values.
 * 
 * @param arr - a pointer to an integer array.
 * @param size - the size of the array.
 */
void randIntArr(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = randInt();
  }
}


/**
 * Populates an integer array with random integer values.
 * 
 * @param arr - a pointer to an integer array.
 * @param size - the size of the array.
 * @param min - the lowest allowed value for any array value.
 * @param max - the highest allowed value for any array value.
 */
void randIntArrRange(int* arr, int size, int min, int max) {
  for (int i = 0; i < size; i++) {
    arr[i] = randIntRange(min, max);
  }
}


/**
 * Populates an array of kingdom cards w/ random kingdom card selections.
 * @param arr - a pointer to an integer array.
 */
void getRandomKingdomCards(int* arr) {
  const int ARR_SIZE = 10;
  const int MAX_CARD = 26;

  for (int i = 0; i < ARR_SIZE; i++) {
    int val = randIntRange(0, MAX_CARD);

    while (inArray(arr, ARR_SIZE, val)) {
      val = randIntRange(0, MAX_CARD);
    }

    arr[i] = val;
  }
}



/**
 * Retrieves a random dominion card value
 */
int getRandomCard() {
  const int MAX_CARD = 26;
  return randIntRange(0, MAX_CARD);
}



/**
 * Returns a random value from an array.
 * 
 * @param arr - a pointer to an integer array.
 * @param size - the nnumber of inetegers in the array.
 * @returns int 
 */
int randFromArr(int* arr, int size) {
  return arr[rand() % size];
}


/**
 * Populates a specified player's hand with a random amount of random
 * card selections, given the current cards in the game.
 * 
 * @param cards - a pointer to an array of integers representing game cards.
 * @param state - a pointer to a gameState structure
 * @param player - an integer representing a player in the game.
 */
void randomizePlayerHand(int* cards, struct gameState* state, int player) {
  int maxRange = MAX_DECK - state->deckCount[player];
  if (maxRange < 5) maxRange = 5;
  state->handCount[player] = randIntRange(5, maxRange);

  for (int i = 0; i < state->handCount[player]; i++) {
    state->hand[player][i] = getRandomCard();
  }
}


/**
 * Populates a each player's hand with a random amount of cards
 * given a pool of cards to choose from.
 * 
 * @param cards - a pointer to an array of integers representing game cards.
 * @param state - a pointer to a gameState structure
 * @param player - an integer representing a player in the game.
 */
void randomizePlayerHands(int* cards, struct gameState* state) {
  for (int i = 0; i < state->numPlayers; i++) {
    randomizePlayerHand(cards, state, i);
  }
}


/**
 * Populates a specified player's deck with a random amount of random
 * card selections, given the current cards in the game.
 * 
 * @param cards - a pointer to an array of integers representing game cards.
 * @param state - a pointer to a gameState structure
 * @param player - an integer representing a player in the game.
 */
void randomizePlayerDeck(int* cards, struct gameState* state, int player) {
  int maxRange = MAX_DECK - state->handCount[player];
  if (maxRange < 5) maxRange = 5;

  state->deckCount[player] = randIntRange(2, maxRange);

  for (int i = 0; i < state->deckCount[player]; i++) {
    state->deck[player][i] = getRandomCard();
  }
}


/**
 * Populates a each player's deck with a random amount of cards
 * given a pool of cards to choose from.
 * 
 * @param cards - a pointer to an array of integers representing game cards.
 * @param state - a pointer to a gameState structure
 * @param player - an integer representing a player in the game.
 */
void randomizePlayerDecks(int* cards, struct gameState* state) {
  for (int i = 0; i < state->numPlayers; i++) {
    randomizePlayerDeck(cards, state, i);
  }
}


/**
 * Populates a specified player's discard with a random amount of random
 * card selections, given the current cards in the game.
 * 
 * @param cards - a pointer to an array of integers representing game cards.
 * @param state - a pointer to a gameState structure
 * @param player - an integer representing a player in the game.
 */
void randomizePlayerDiscard(int* cards, struct gameState* state, int player) {
  int maxRange = MAX_DECK - (state->discardCount[player] + state->deckCount[player]);
  if (maxRange < 5) maxRange = 5;

  state->discardCount[player] = randIntRange(0, maxRange);

  for (int i = 0; i < state->discardCount[player]; i++) {
    state->discard[player][i] = getRandomCard();
  }
}


/**
 * Populates a each player's discard with a random amount of cards
 * given a pool of cards to choose from.
 * 
 * @param cards - a pointer to an array of integers representing game cards.
 * @param state - a pointer to a gameState structure
 * @param player - an integer representing a player in the game.
 */
void randomizePlayerDiscards(int* cards, struct gameState* state) {
  for (int i = 0; i < state->numPlayers; i++) {
    randomizePlayerDiscard(cards, state, i);
  }
}