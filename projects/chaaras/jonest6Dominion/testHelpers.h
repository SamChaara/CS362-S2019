#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testCompare.h"
#include "printHelpers.h"


/***************************************
 * gameState
 ***************************************/

/* Checks if two game states have exactly the same values. */
bool isStateSame(struct gameState* state1, struct gameState* state2);



/***************************************
 * handCount
 ***************************************/

/* Returns the difference in handCount between two gameStates for a given player. */
int player_handcount_difference(struct gameState* pre, struct gameState* post, int player);

/* Returns the change amount in handCount between two gameStates for a given player. */
int player_handcount_delta(struct gameState* pre, struct gameState* post, int player);

/**
 * Returns the combined difference in handCount between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 */
int other_players_combined_handcount_delta(struct gameState* pre, struct gameState* post, int player);

/* Returns the combined difference in handCount between two gameStates for all players. */
int all_players_combined_handcount_delta(struct gameState* pre, struct gameState* post);

/* Checks if a specified player's handCount changed between two gameStates. */
bool player_handcount_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to player handCounts EXCEPT for a specified player. */
bool any_other_player_handcount_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to ANY player handCounts in the game. */
bool any_player_handcount_did_change(struct gameState* pre, struct gameState* post);



/***************************************
 * hand
 ***************************************/

/* Counts the number of cards that are different between two game states in a given player's hand. */
int player_hand_delta(struct gameState* pre, struct gameState* post, int player);

/**
 * Returns the combined difference in the hands of cards between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 */
int other_players_combined_hand_delta(struct gameState* pre, struct gameState* post, int player);

/* Returns the combined difference in hands between two gameStates for all players. */
int all_players_combined_hand_delta(struct gameState* pre, struct gameState* post);

/* Checks if a specified player's hand changed between two game states. */
bool player_hand_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to player hand EXCEPT for a specified player. */
bool any_other_player_hand_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to ANY player hands in the game. */
bool any_player_hand_did_change(struct gameState* pre, struct gameState* post);



/***************************************
 * deckCount
 ***************************************/

/* Returns the difference in deckCount between two gameStates for a given player. */
int player_deckcount_difference(struct gameState* pre, struct gameState* post, int player);

/* Returns the change amount in deckCount between two gameStates for a given player. */
int player_deckcount_delta(struct gameState* pre, struct gameState* post, int player);

/**
 * Returns the combined difference in deckCount between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 */
int other_players_combined_deckcount_delta(struct gameState* pre, struct gameState* post, int player);

/* Returns the combined difference in deckCount between two gameStates for all players. */
int all_players_combined_deckcount_delta(struct gameState* pre, struct gameState* post);

/* Checks if a specified player's deckCount changed between two gameStates. */
bool player_deckcount_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to player deckCounts EXCEPT for a specified player. */
bool any_other_player_deckcount_did_change(struct gameState* pre, struct gameState* post, int player);


/* Checks if there ware any changes to ANY player deckCounts in the game. */
bool any_player_deckcount_did_change(struct gameState* pre, struct gameState* post);



/***************************************
 * deck
 ***************************************/

/* Counts the number of cards that are different between two game states in a given player's deck. */
int player_deck_delta(struct gameState* pre, struct gameState* post, int player);

/**
 * Returns the combined difference in the decks of cards between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 */
int other_players_combined_deck_delta(struct gameState* pre, struct gameState* post, int player);

/* Returns the combined difference in decks between two gameStates for all players. */
int all_players_combined_deck_delta(struct gameState* pre, struct gameState* post);

/* Checks if a specified player's deck changed between two game states. */
bool player_deck_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to player deck EXCEPT for a specified player. */
bool any_other_player_deck_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to ANY player decks in the game. */
bool any_player_deck_did_change(struct gameState* pre, struct gameState* post);

/* Gets the value of the card currently on the top of a player's deck. */
int player_top_deck_card(struct gameState* state, int player);

/* Checks if the card on the top of a player's deck is a specific card type */
bool player_top_of_deck_is_card(struct gameState* state, int player, int card);

/**
 * Checks if the card on top of all other player's decks EXCEPT for the current
 * player are of a specific card type.
 */
bool all_other_top_of_deck_is_card(struct gameState* state, int player, int card);



/***************************************
 * discard
 ***************************************/

/* Counts the number of cards that are different between two game states in a given player's discard. */
int player_discard_delta(struct gameState* pre, struct gameState* post, int player);

/**
 * Returns the combined difference in the discards of cards between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 */
int other_players_combined_discard_delta(struct gameState* pre, struct gameState* post, int player);

/* Returns the combined difference in discards between two gameStates for all players. */
int all_players_combined_discard_delta(struct gameState* pre, struct gameState* post);

/* Checks if a specified player's discard changed between two game states. */
bool player_discard_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to player discard EXCEPT for a specified player. */
bool any_other_player_discard_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to ANY player discards in the game. */
bool any_player_discard_did_change(struct gameState* pre, struct gameState* post);



/***************************************
 * discardCount
 ***************************************/

/* Returns the difference in discardCount between two gameStates for a given player. */
int player_discardcount_difference(struct gameState* pre, struct gameState* post, int player);

/* Returns the change amount in discardCount between two gameStates for a given player. */
int player_discardcount_delta(struct gameState* pre, struct gameState* post, int player);

/**
 * Returns the combined difference in discardCount between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 */
int other_players_combined_discardcount_delta(struct gameState* pre, struct gameState* post, int player);

/* Returns the combined difference in discardCount between two gameStates for all players. */
int all_players_combined_discardcount_delta(struct gameState* pre, struct gameState* post);

/* Checks if a specified player's discardCount changed between two gameStates. */
bool player_discardcount_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to player discardCounts EXCEPT for a specified player. */
bool any_other_player_discardcount_did_change(struct gameState* pre, struct gameState* post, int player);

/* Checks if there ware any changes to ANY player discardCounts in the game. */
bool any_player_discardcount_did_change(struct gameState* pre, struct gameState* post);



/***************************************
 * Resets / Emptying
 **************************************/

/**
 * Empties a player's hand by setting all the cards in the
 * hand to -1 and setting the hand count to 0.
 */
void empty_player_hand(struct gameState* state, int player);

/**
 * Empties a player's deck by setting all the cards in the
 * deck to -1 and setting the deck count to 0.
 */
void empty_player_deck(struct gameState* state, int player);

/**
 * Empties a player's discard by setting all the cards in the
 * discard to -1 and setting the discard count to 0.
 */
void empty_player_discard(struct gameState* state, int player);



/***************************************
 * total player cards
 ***************************************/

/* Return the total number of cards in a given player's card circulation while inspecting a given game state. */
int player_total_cards_in_state(struct gameState* state, int player);

/* Return the difference in total number of cards in a given player's card circulation after some change */
int player_total_cards_difference(struct gameState* pre, struct gameState* post, int player);

/* Return the change in total number of cards in a given player's card circulation after some change */
int player_total_cards_delta(struct gameState* pre, struct gameState* post, int player);



/***************************************
 * card supplies
 ***************************************/

/* Returns the difference in the amount supply count of a specified card between two game states. */
int card_supplycount_difference(struct gameState* pre, struct gameState* post, int card);

/* Returns the change in the amount supply count of a specified card between two game states. */
int card_supplycount_delta(struct gameState* pre, struct gameState* post, int card);

/* Checks if the supply count for a specified card changed between two game states. */
bool did_card_supplycount_change(struct gameState* pre, struct gameState* post, int card);

/* Returns the change amount in the amount of victory cards between two gameStates. */
int victory_card_delta(struct gameState* pre, struct gameState* post);

/* Returns the change amount in the amount of kingfom cards between two gameStates. */
int kingdom_card_delta(struct gameState* pre, struct gameState* post);



/***************************************
 * individual card instances
 ***************************************/

/**
 * Returns the index of the nth instance of a specific
 * card in a given player's hand. If the card does not
 * have n instances in the player's hand, then -1 is returned.
 */
int card_nth_hand_pos(struct gameState* state, int player, int card, int n);

/**
 * Returns the index of the first instance of a specific
 * card in a given player's hand. If there are no instances
 * of the specified card in the player's hand, then the function
 * returns -1.
 */
int card_first_hand_pos(struct gameState* state, int player, int card);

/**
 * Returns the index of the last instance of a specific
 * card in a given player's hand. If there are no instances
 * of the specified card in the player's hand, then the function
 * returns -1.
 */
int card_last_hand_pos(struct gameState* state, int player, int card);

/**
 * Returns the index of the nth instance of a specific
 * card in a given player's deck. If the card does not
 * have n instances in the player's deck, then -1 is returned.
 */
int card_nth_deck_pos(struct gameState* state, int player, int card, int n);

/**
 * Returns the index of the first instance of a specific
 * card in a given player's deck. If there are no instances
 * of the specified card in the player's deck, then the function
 * returns -1.
 */
int card_first_deck_pos(struct gameState* state, int player, int card);

/**
 * Returns the index of the last instance of a specific
 * card in a given player's deck. If there are no instances
 * of the specified card in the player's deck, then the function
 * returns -1.
 */
int card_last_deck_pos(struct gameState* state, int player, int card);

/**
 * Returns the index of the nth instance of a specific
 * card in a given player's discard. If the card does not
 * have n instances in the player's discard, then -1 is returned.
 */
int card_nth_discard_pos(struct gameState* state, int player, int card, int n);

/**
 * Returns the index of the first instance of a specific
 * card in a given player's discard. If there are no instances
 * of the specified card in the player's discard, then the function
 * returns -1.
 */
int card_first_discard_pos(struct gameState* state, int player, int card);

/**
 * Returns the index of the last instance of a specific
 * card in a given player's discard. If there are no instances
 * of the specified card in the player's discard, then the function
 * returns -1.
 */
int card_last_discard_pos(struct gameState* state, int player, int card);


/**
 * Returns the number of instances of a specific card that are in a 
 * given player's hand for a given game state.
 */
int player_card_type_total_in_hand(struct gameState* state, int card, int player);

/**
 * Returns the number of instances of a specific card that are in a 
 * given player's deck for a given game state.
 */
int player_card_type_total_in_deck(struct gameState* state, int card, int player);

/**
 * Returns the number of instances of a specific card that are in a 
 * given player's discard pile for a given game state.
 */
int player_card_type_total_in_discard(struct gameState* state, int card, int player);

/**
 * Returns the number of instances of a specific card that are in a player's full deck.
 */
int player_card_type_total_in_deck(struct gameState* state, int card, int player);

/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's hand between two game states.
 */
int player_card_type_difference_in_hand(struct gameState* pre, struct gameState* post, int card, int player);

/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's deck between two game states.
 */
int player_card_type_difference_in_deck(struct gameState* pre, struct gameState* post, int card, int player);

/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's discard pile between two game states.
 */
int player_card_type_difference_in_discard(struct gameState* pre, struct gameState* post, int card, int player);

/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's discard pile between two game states.
 */
int player_card_type_difference_in_full_deck(struct gameState* pre, struct gameState* post, int card, int player);



/***************************************
 * treasure cards
 ***************************************/

/* Checks if a given card represents a treasure card */
bool is_treasure_card(int card);

/* Get the total number of treasure cards in a player's hand in a given game state. */
int player_treasure_cards_in_hand(struct gameState* state, int player);

/* Get the total number of treasure cards in a player's deck in a given game state. */
int player_treasure_cards_in_deck(struct gameState* state, int player);

/* Get the total number of treasure cards in a player's discard in a given game state.*/
int player_treasure_cards_in_discard(struct gameState* state, int player);

/* Returns the difference in treasure cards in a player's hand between two different game states. */
int player_treasure_card_difference_in_hand(struct gameState* pre, struct gameState* post, int player);

/* Returns the difference in treasure cards in a player's deck between two different game states. */
int player_treasure_card_difference_in_deck(struct gameState* pre, struct gameState* post, int player);



/***************************************
 * actions
 ***************************************/

/* Returns the difference in the number of actions available between two different game states. */
int game_actions_difference(struct gameState* pre, struct gameState* post);

/* Returns the difference in the number of total cards played between two different game states. */
int cards_played_difference(struct gameState* pre, struct gameState* post);

/* Returns the difference in the number of buys between two different game states. */
int game_buys_difference(struct gameState* pre, struct gameState* post);



/***************************************
 * actions
 ***************************************/

/* Makes a copy of a game state */
void rebaseGameState(struct gameState* pre, struct gameState* post);


#endif