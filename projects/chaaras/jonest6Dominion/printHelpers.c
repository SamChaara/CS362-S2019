/***
 * Name: printHelpers.c
 * Description: Helper functions that make printing
 *  various contents a little more convenient.
 */

#include "printHelpers.h"


/**
 * Helper function that wraps fprintf() and takes care of flushing
 * the output buffer after printing. This allows us to "set and forget"
 * about having to flush the output buffer after each time we print contents
 * to an output stream.
 *
 * @note The idea for this implementation came from the following source:
 * https://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
 *
 * @param stream - the output file stream to print to
 * @param format - the format of the content that is to be printed
 * @param ... - the output arguments to give to fprintf
 */
void print(FILE* stream, const char *format, ...) {
  va_list arguments;                    // holds info about the ... arguments
  va_start(arguments, format);          // points to the beginning of the arguments
  vfprintf(stream, format, arguments);  // prints the content
  va_end(arguments);                    // ends using the variable argument list
  fflush(stream);                       // flushes the output buffer
}


/**
 * Helper function that wraps fprintf() and for easy error printing by taking 
 * care of flushing the output buffer after printing. This allows us to "set and forget"
 * about having to flush the output buffer after each time we print contents to stderr.
 *
 * @note The idea for this implementation came from the following source:
 * https://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
 *
 * @param format - the format of the content that is to be printed
 * @param ... - the output arguments to give to fprintf
 */
void printErr(const char *format, ...) {
  va_list arguments;                    // holds info about the ... arguments
  va_start(arguments, format);          // points to the beginning of the arguments
  vfprintf(stderr, format, arguments);  // prints the error message
  va_end(arguments);                    // ends using the variable argument list
  fflush(stderr);                       // flushes the output buffer
}


/**
 * Helper function that wraps fprintf() and for easy error printing by taking 
 * care of flushing the output buffer after printing. This allows us to "set and forget"
 * about having to flush the output buffer after each time we print contents to stdout.
 *
 * @note The idea for this implementation came from the following source:
 * https://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
 *
 * @param format - the format of the content that is to be printed
 * @param ... - the output arguments to give to fprintf
 */
void printOut(const char *format, ...) {
  va_list arguments;                    // holds info about the ... arguments
  va_start(arguments, format);          // points to the beginning of the arguments
  vfprintf(stdout, format, arguments);  // prints the error message
  va_end(arguments);                    // ends using the variable argument list
  fflush(stdout);                       // flushes the output buffer
}


/**
 * Checks if DEBUG mode is enable. If so, prints a
 * given test rule with a pre-determined format for clarity.
 */
void printDebugRule(const char* rule) {
  if (DEBUG) print(stderr, "\n* %s\n", rule);
}


/**
 * Gets the name of a card, given the card's integer value
 * @param card - an integer representing a card.
 */
char* getCardName(int card) {
  switch (card) {
    case 0: return "curse";
    case 1: return "estate";
    case 2: return "duchy";
    case 3: return "province";
    case 4: return "copper";
    case 5: return "silver";
    case 6: return "gold";
    case 7: return "adventurer";
    case 8: return "council_room";
    case 9: return "feast";
    case 10: return "gardens";
    case 11: return "mine";
    case 12: return "remodel";
    case 13: return "smithy";
    case 14: return "village";
    case 15: return "baron";
    case 16: return "great_hall";
    case 17: return "minion";
    case 18: return "steward";
    case 19: return "tribute";
    case 20: return "ambassador";
    case 21: return "cutpurse";
    case 22: return "embargo";
    case 23: return "outpost";
    case 24: return "salvager";
    case 25: return "sea_hag";
    case 26: return "treasure_map";
    default: return "NONE";
  }
}


/**
 * Prints the contents of an integer array as a comma-separated list.
 * 
 * @param arr - an integer array
 * @param size - the number of elements in the array.
 */
void printArray(int* arr, int size) {
  // make sure the array exists and has any values
  if (arr == NULL) { fprintf(stderr, "NULL\n"); return; }
  if (size == 0) { fprintf(stderr, "EMPTY\n"); return; }

  // print each array element
  for (int i = 0; i < size; i++) {
    char name[MAX_CARD_NAME_LENGTH];
    memset(name, '\0', MAX_CARD_NAME_LENGTH);
    strcpy(name, getCardName(arr[i]));
    print(stderr, "%s", name);

    if (i < size - 1) {
      fprintf(stderr, ", ");
    } else {
      fprintf(stderr, "\n");
    }
  }
}


/**
 * Prints an integer array, prefixed with a variadic set of output arguments
 * 
 * @param arr - an integer array to print the contents of
 * @param size - the number of elements in the array
 * @param format - the output format to give to fprintf
 * @param ... - the output arguments to give to fprintf
 */
void printArrayArgs(int* arr, int size, const char *format, ...) {
  va_list arguments;                    // holds info about the ... arguments
  va_start(arguments, format);          // points to the beginning of the arguments
  vfprintf(stderr, format, arguments);  // prints the error message
  va_end(arguments);                    // ends using the variable argument list
  fflush(stderr);                       // flushes the output buffer
  
  fprintf(stderr, ": ");
  printArray(arr, size);
}


/**
 * Prints an integer array, prefixed with a string literal
 * 
 * @param arr - an integer array to print the contents of
 * @param size - the number of elements in the array
 * @param prefix - a prefix string to prepend to the array
 */
void printArrayPrefixed(int* arr, int size, const char* prefix) {  
  fprintf(stderr, "%s: ", prefix);
  printArray(arr, size);
  fflush(stderr);
}



/**
 * Prints all the cards in the hand of a given player.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 */
void printHand(struct gameState* state, int player) {
  fprintf(stderr, "%d: ", player);

  for (int i = 0; i < state->handCount[player]; i++) {
    fprintf(stderr, "%s", getCardName(state->hand[player][i]));
    if (i < state->handCount[player] - 1) {
      fprintf(stderr, ", ");
    }
  }

  fprintf(stderr, "\n");
}


/**
 * Prints all the cards in the hand of each player in the game.
 * @param state - a pointer to a gameState structure.
 */
void printHands(struct gameState* state) {
  for (int i = 0; i < state->numPlayers; i++) {
    printHand(state, i);
  }
}


/**
 * Prints all the cards in the deck of a given player.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 */
void printDeck(struct gameState* state, int player) {
  fprintf(stderr, "%d: ", player);

  for (int i = 0; i < state->deckCount[player]; i++) {
    fprintf(stderr, "%s", getCardName(state->deck[player][i]));
    if (i < state->deckCount[player] - 1) {
      fprintf(stderr, ", ");
    }
  }

  fprintf(stderr, "\n");
}


/**
 * Prints all the cards in the deck of each player in the game.
 * @param state - a pointer to a gameState structure.
 */
void printDecks(struct gameState* state) {
  for (int i = 0; i < state->numPlayers; i++) {
    printDeck(state, i);
  }
}


/**
 * Prints all the cards in the discard of a given player.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 */
void printDiscard(struct gameState* state, int player) {
  fprintf(stderr, "%d: ", player);

  for (int i = 0; i < state->discardCount[player]; i++) {
    fprintf(stderr, "%s", getCardName(state->discard[player][i]));
    if (i < state->discardCount[player] - 1) {
      fprintf(stderr, ", ");
    }
  }

  fprintf(stderr, "\n");
}


/**
 * Prints all the cards in the discard of each player in the game.
 * @param state - a pointer to a gameState structure.
 */
void printDiscards(struct gameState* state) {
  for (int i = 0; i < state->numPlayers; i++) {
    printDiscard(state, i);
  }
}


/**
 * Prints various game state inforamation for a given game state.
 * @param state - a pointer to a gameState structure.
 */
void printState(struct gameState* state) {
    fprintf(stderr, "Players: %d   Current: %d\n", state->numPlayers, state->whoseTurn);
    fprintf(stderr, "Hands:\n"); printHands(state);
    fprintf(stderr, "Decks:\n"); printDecks(state);
    fprintf(stderr, "Discards:\n"); printDiscards(state);
}
