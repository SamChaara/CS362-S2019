/**
 * Name: testHelpers.c
 * Description: Helper functions that perform simple comparisons
 *  between gameState structures, for use with various unit tests.
 */

#include "testHelpers.h"
#include "printHelpers.h"


/***************************************
 * gameState
 ***************************************/

/**
 * Checks if two game states have exactly the same values.
 * 
 * @param state1 - a pointer to a gameState structure.
 * @param state2 - a pointer to a gameState structure.
 * @returns bool - true if the gameStates are the same, false if not.
 */
bool isStateSame(struct gameState* state1, struct gameState* state2) {
  return (memcmp(state1, state2, sizeof(struct gameState)) == 0);
}



/***************************************
 * handCount
 ***************************************/

/**
 * Returns the difference in handCount between two gameStates for a given player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the diffference in the handCount for the player
 *  starting from it's pre gameState value to its post gameState value.
 */
int player_handcount_difference(struct gameState* pre, struct gameState* post, int player) {
  if (DEBUG) print(stderr, "hand count | player: %d | pre: %-2d post: %d\n", player, pre->handCount[player], post->handCount[player]);
  return post->handCount[player] - pre->handCount[player];
}


/**
 * Returns the change amount in handCount between two gameStates for a given player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the change in the handCount for the player
 *  starting from it's pre gameState value to its post gameState value.
 */
int player_handcount_delta(struct gameState* pre, struct gameState* post, int player) {
  return abs(player_handcount_difference(pre, post, player));
}


/**
 * Returns the combined difference in handCount between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for handCount changes.
 * @return an integer that represents the diffference in the handCount for all other players in the game.
 */
int other_players_combined_handcount_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      delta += player_handcount_delta(pre, post, i);
    }
  }

  if (DEBUG) {
    print(stderr, "hand count | all other players (NOT player: %d) | combined delta: %d\n", player, delta);
  }

  return delta;
}


/**
 * Returns the combined difference in handCount between two gameStates for all players.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return an integer that represents the diffference in the handCount for all players in the game.
 */
int all_players_combined_handcount_delta(struct gameState* pre, struct gameState* post) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    delta += player_handcount_delta(pre, post, i);
  }

  if (DEBUG) {
    print(stderr, "hand count | all players | combined delta: %d\n", delta);
  }

  return delta;
}


/**
 * Checks if a specified player's handCount changed between two gameStates.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return bool - true if the player's handCount is different in the post gameState, compared to 
 *  the pre gameState, false if not.
 */
bool player_handcount_did_change(struct gameState* pre, struct gameState* post, int player) {
  return player_handcount_delta(pre, post, player) != 0;
}


/**
 * Checks if there ware any changes to player handCounts EXCEPT for a specified player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for handCount changes.
 * @return bool - true if any handCount changes occurred for any players EXCEPT for the specified
 *  player, false if not.
 */
bool any_other_player_handcount_did_change(struct gameState* pre, struct gameState* post, int player) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player && player_handcount_delta(pre, post, i) != 0) {
      return true;
    }
  }

  return false;
}


/**
 * Checks if there ware any changes to ANY player handCounts in the game.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return bool - true if any handCount changes occurred for any players, false if not.
 */
bool any_player_handcount_did_change(struct gameState* pre, struct gameState* post) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (player_handcount_delta(pre, post, i) != 0) {
      return true;
    }
  }

  return false;
}


/***************************************
 * hand
 ***************************************/

/**
 * Counts the number of cards that are different between two game states in a given player's hand.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the number of cards that are not the same between the two
 *  game state's. 
 * @note: same = same card at same index.
 * @note: any difference in handCount is added to the delta.
 */
int player_hand_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = abs(post->handCount[player] - pre->handCount[player]);
  int minCount = min(post->handCount[player], pre->handCount[player]);

  for (int i = 0; i < minCount; i++) {
    if (post->hand[player][i] != pre->hand[player][i]) {
      delta++;
    }
  }

  if (DEBUG) {
    printArrayArgs(pre->hand[player], pre->handCount[player], "hand | player: %d | %-5s", player, "pre");
    printArrayArgs(post->hand[player], post->handCount[player], "hand | player: %d | %-5s", player, "post");
    print(stderr, "hand | player: %d | %-5s: %d\n", player, "delta", delta);
  }
  
  return delta;
}


/**
 * Returns the combined difference in the hands of cards between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for hand changes.
 * @return an integer that represents the changes in the hands for all other players in the game.
 */
int other_players_combined_hand_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      delta += player_hand_delta(pre, post, i);
    }
  }

  if (DEBUG) {
    print(stderr, "hand | all other players (NOT player: %d) | combined delta: %d\n", player, delta);
  }

  return delta;
}


/**
 * Returns the combined difference in hands between two gameStates for all players.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return an integer that represents the changes in the hands of all players in the game.
 */
int all_players_combined_hand_delta(struct gameState* pre, struct gameState* post) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    delta += player_hand_delta(pre, post, i);
  }

  if (DEBUG) {
    print(stderr, "hand | all players | combined delta: %d\n", delta);
  }

  return delta;
}


/**
 * Checks if a specified player's hand changed between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return bool - true if the player's hand is different in the post gameState, compared to 
 *  the pre gameState, false if not.
 */
bool player_hand_did_change(struct gameState* pre, struct gameState* post, int player) {
  return player_hand_delta(pre, post, player) != 0;
}


/**
 * Checks if there ware any changes to player hand EXCEPT for a specified player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for hand changes.
 * @return bool - true if any hand changes occurred for any players EXCEPT for the specified
 *  player, false if not.
 */
bool any_other_player_hand_did_change(struct gameState* pre, struct gameState* post, int player) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      if (player_hand_delta(pre, post, i) != 0) {
        return true;
      }
    }
  }

  return false;
}


/**
 * Checks if there ware any changes to ANY player hands in the game.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return bool - true if any hand changes occurred for any players, false if not.
 */
bool any_player_hand_did_change(struct gameState* pre, struct gameState* post) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (player_hand_delta(pre, post, i) != 0) {
      return true;
    }
  }

  return false;
}




/***************************************
 * deckCount
 ***************************************/

/**
 * Returns the difference in deckCount between two gameStates for a given player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the diffference in the deckCount for the player
 *  starting from it's pre gameState value to its post gameState value.
 */
int player_deckcount_difference(struct gameState* pre, struct gameState* post, int player) {
  if (DEBUG) print(stderr, "deck count | player: %d | pre: %-2d post: %d\n", player, pre->deckCount[player], post->deckCount[player]);
  return post->deckCount[player] - pre->deckCount[player];
}


/**
 * Returns the change amount in deckCount between two gameStates for a given player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the change in the deckCount for the player
 *  starting from it's pre gameState value to its post gameState value.
 */
int player_deckcount_delta(struct gameState* pre, struct gameState* post, int player) {
  return abs(player_deckcount_difference(pre, post, player));
}


/**
 * Returns the combined difference in deckCount between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for deckCount changes.
 * @return an integer that represents the diffference in the deckCount for all other players in the game.
 */
int other_players_combined_deckcount_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      delta += player_deckcount_delta(pre, post, i);
    }
  }

  if (DEBUG) {
    print(stderr, "deck count | all other players (NOT player: %d) | combined delta: %d\n", player, delta);
  }

  return delta;
}


/**
 * Returns the combined difference in deckCount between two gameStates for all players.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return an integer that represents the diffference in the deckCount for all players in the game.
 */
int all_players_combined_deckcount_delta(struct gameState* pre, struct gameState* post) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    delta += player_deckcount_delta(pre, post, i);
  }

  if (DEBUG) {
    print(stderr, "deck count | all players | combined delta: %d\n", delta);
  }

  return delta;
}


/**
 * Checks if a specified player's deckCount changed between two gameStates.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return bool - true if the player's deckCount is different in the post gameState, compared to 
 *  the pre gameState, false if not.
 */
bool player_deckcount_did_change(struct gameState* pre, struct gameState* post, int player) {
  return player_deckcount_delta(pre, post, player) != 0;
}


/**
 * Checks if there ware any changes to player deckCounts EXCEPT for a specified player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for deckCount changes.
 * @return bool - true if any deckCount changes occurred for any players EXCEPT for the specified
 *  player, false if not.
 */
bool any_other_player_deckcount_did_change(struct gameState* pre, struct gameState* post, int player) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      if (player_deckcount_delta(pre, post, i) != 0) {
        return true;
      }
    }
  }

  return false;
}


/**
 * Checks if there ware any changes to ANY player deckCounts in the game.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return bool - true if any deckCount changes occurred for any players, false if not.
 */
bool any_player_deckcount_did_change(struct gameState* pre, struct gameState* post) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (player_deckcount_delta(pre, post, i) != 0) {
      return true;
    }
  }

  return false;
}



/***************************************
 * deck
 ***************************************/

/**
 * Counts the number of cards that are different between two game states in a given player's deck.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the number of cards that are not the same between the two
 *  game state's. 
 * @note: same = same card at same index.
 * @note: any difference in deckCount is added to the delta.
 */
int player_deck_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = abs(post->deckCount[player] - pre->deckCount[player]);
  int minCount = min(post->deckCount[player], pre->deckCount[player]);

  for (int i = 0; i < minCount; i++) {
    if (post->deck[player][i] != pre->deck[player][i]) {
      delta++;
    }
  }
  
  if (DEBUG) {
    printArrayArgs(pre->deck[player], pre->deckCount[player], "deck | player: %d | %-5s", player, "pre");
    printArrayArgs(post->deck[player], post->deckCount[player], "deck | player: %d | %-5s", player, "post");
    print(stderr, "deck | player: %d | %-5s: %d\n", player, "delta", delta);
  }

  return delta;
}


/**
 * Returns the combined difference in the decks of cards between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for deck changes.
 * @return an integer that represents the changes in the decks for all other players in the game.
 */
int other_players_combined_deck_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      delta += player_deck_delta(pre, post, i);
    }
  }

  if (DEBUG) {
    print(stderr, "deck | all other players (NOT player: %d) | combined delta: %d\n", player, delta);
  }

  return delta;
}


/**
 * Returns the combined difference in decks between two gameStates for all players.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return an integer that represents the changes in the decks of all players in the game.
 */
int all_players_combined_deck_delta(struct gameState* pre, struct gameState* post) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    delta += player_deck_delta(pre, post, i);
  }

  if (DEBUG) {
    print(stderr, "deck | all players | combined delta: %d\n", delta);
  }

  return delta;
}


/**
 * Checks if a specified player's deck changed between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return bool - true if the player's deck is different in the post gameState, compared to 
 *  the pre gameState, false if not.
 */
bool player_deck_did_change(struct gameState* pre, struct gameState* post, int player) {
  return player_deck_delta(pre, post, player) != 0;
}


/**
 * Checks if there ware any changes to player deck EXCEPT for a specified player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for deck changes.
 * @return bool - true if any deck changes occurred for any players EXCEPT for the specified
 *  player, false if not.
 */
bool any_other_player_deck_did_change(struct gameState* pre, struct gameState* post, int player) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      if (player_deck_delta(pre, post, i) != 0) {
        return true;
      }
    }
  }

  return false;
}


/**
 * Checks if there ware any changes to ANY player decks in the game.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return bool - true if any deck changes occurred for any players, false if not.
 */
bool any_player_deck_did_change(struct gameState* pre, struct gameState* post) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (player_deck_delta(pre, post, i) != 0) {
      return true;
    }
  }

  return false;
}


/**
 * Gets the value of the card currently on the top of a player's deck.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - the player index to look at the deck of.
 * @returns int - an integer representing a card type
 */
int player_top_deck_card(struct gameState* state, int player) {
  int topDeckCard = -1;

  if (state->deckCount[player] > 0) {
    topDeckCard = state->deck[player][state->deckCount[player] - 1];
  }

  if (DEBUG) {
    char name[MAX_CARD_NAME_LENGTH];
    memset(name, '\0', MAX_CARD_NAME_LENGTH);
    strcpy(name, getCardName(topDeckCard));
    print(stderr, "top of deck | player: %d | card: %s\n", player, name);
  }

  return topDeckCard;
}


/**
 * Checks if the card on the top of a player's deck is a specific card type
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - the player index to look at the deck of.
 * @param card - an integer reresenting a card type
 * @returns bool - true if the card on the top of the deck is the specified card type, false if not.
 */
bool player_top_of_deck_is_card(struct gameState* state, int player, int card) {
  return player_top_deck_card(state, player) == card;
}

/**
 * Checks if the card on top of all other player's decks EXCEPT for the current
 * player are of a specific card type.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - the player index to NOT check for deck changes.
 * @param card - an integer reresenting a card type
 * @returns bool - true if the card on the top of the deck is the specified card type, false if not.
 */
bool all_other_top_of_deck_is_card(struct gameState* state, int player, int card) {
  for (int i = 0; i < state->numPlayers; i++) {
    if (i != player && !player_top_of_deck_is_card(state, i, card)) {
      return false;
    }
  }

  return true;
}


/***************************************
 * discardCount
 ***************************************/

/**
 * Returns the difference in discardCount between two gameStates for a given player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the diffference in the discardCount for the player
 *  starting from it's pre gameState value to its post gameState value.
 */
int player_discardcount_difference(struct gameState* pre, struct gameState* post, int player) {
  if (DEBUG) print(stderr, "discard count | player: %d | pre: %-2d post: %d\n", player, pre->discardCount[player], post->discardCount[player]);
  return post->discardCount[player] - pre->discardCount[player];
}


/**
 * Returns the change amount in discardCount between two gameStates for a given player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the change in the discardCount for the player
 *  starting from it's pre gameState value to its post gameState value.
 */
int player_discardcount_delta(struct gameState* pre, struct gameState* post, int player) {
  return abs(player_discardcount_difference(pre, post, player));
}


/**
 * Returns the combined difference in discardCount between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discardCount changes.
 * @return an integer that represents the diffference in the discardCount for all other players in the game.
 */
int other_players_combined_discardcount_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      delta += player_discardcount_delta(pre, post, i);
    }
  }

  if (DEBUG) print(stderr, "discard count | all other players (NOT player: %d) | combined delta: %d\n", player, delta);
  return delta;
}


/**
 * Returns the combined difference in discardCount between two gameStates for all players.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return an integer that represents the diffference in the discardCount for all players in the game.
 */
int all_players_combined_discardcount_delta(struct gameState* pre, struct gameState* post) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    delta += player_discardcount_delta(pre, post, i);
  }

  if (DEBUG) print(stderr, "discard count | all players | combined delta: %d\n", delta);
  return delta;
}


/**
 * Checks if a specified player's discardCount changed between two gameStates.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return bool - true if the player's discardCount is different in the post gameState, compared to 
 *  the pre gameState, false if not.
 */
bool player_discardcount_did_change(struct gameState* pre, struct gameState* post, int player) {
  return player_discardcount_delta(pre, post, player) != 0;
}


/**
 * Checks if there ware any changes to player discardCounts EXCEPT for a specified player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discardCount changes.
 * @return bool - true if any discardCount changes occurred for any players EXCEPT for the specified
 *  player, false if not.
 */
bool any_other_player_discardcount_did_change(struct gameState* pre, struct gameState* post, int player) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      if (player_discardcount_delta(pre, post, i) != 0) {
        return true;
      }
    }
  }

  return false;
}


/**
 * Checks if there ware any changes to ANY player discardCounts in the game.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discardCount changes.
 * @return bool - true if any discardCount changes occurred for any players, false if not.
 */
bool any_player_discardcount_did_change(struct gameState* pre, struct gameState* post) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (player_discardcount_delta(pre, post, i) != 0) {
      return true;
    }
  }

  return false;
}



/***************************************
 * discard
 ***************************************/

/**
 * Counts the number of cards that are different between two game states in a given player's discard.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return an integer that represents the number of cards that are not the same between the two
 *  game state's. 
 * @note: same = same card at same index.
 * @note: any difference in discardSize is added to the delta.
 */
int player_discard_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = abs(post->discardCount[player] - pre->discardCount[player]);
  int minCount = min(post->discardCount[player], pre->discardCount[player]);

  for (int i = 0; i < minCount; i++) {
    if (post->discard[player][i] != pre->discard[player][i]) {
      delta++;
    }
  }

  if (DEBUG) {
    printArrayArgs(pre->discard[player], pre->discardCount[player], "discard | player: %d | %-5s", player, "pre");
    printArrayArgs(post->discard[player], post->discardCount[player], "discard | player: %d | %-5s", player, "post");
    print(stderr, "discard | player: %d | %-5s: %d\n", player, "delta", delta);
  }
  
  return delta;
}


/**
 * Returns the combined difference in the discards of cards between two gameStates for all 
 * players EXCEPT a specified player (AKA all players that are NOT the given player).
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discard changes.
 * @return an integer that represents the changes in the discards for all other players in the game.
 */
int other_players_combined_discard_delta(struct gameState* pre, struct gameState* post, int player) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      delta += player_discard_delta(pre, post, i);
    }
  }

  if (DEBUG) {
    print(stderr, "discard | all other players (NOT player: %d) | combined delta: %d\n", player, delta);
  }

  return delta;
}


/**
 * Returns the combined difference in discards between two gameStates for all players.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @return an integer that represents the changes in the discards of all players in the game.
 */
int all_players_combined_discard_delta(struct gameState* pre, struct gameState* post) {
  int delta = 0;

  for (int i = 0; i < pre->numPlayers; i++) {
    delta += player_discard_delta(pre, post, i);
  }

  if (DEBUG) {
    print(stderr, "discard | all players | combined delta: %d\n", delta);
  }

  return delta;
}


/**
 * Checks if a specified player's discard changed between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index of some player in the game.
 * @return bool - true if the player's discard is different in the post gameState, compared to 
 *  the pre gameState, false if not.
 */
bool player_discard_did_change(struct gameState* pre, struct gameState* post, int player) {
  return player_discard_delta(pre, post, player) != 0;
}


/**
 * Checks if there ware any changes to player discard EXCEPT for a specified player.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discard changes.
 * @return bool - true if any discard changes occurred for any players EXCEPT for the specified
 *  player, false if not.
 */
bool any_other_player_discard_did_change(struct gameState* pre, struct gameState* post, int player) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (i != player) {
      if (player_discard_delta(pre, post, i) != 0) {
        return true;
      }
    }
  }

  return false;
}


/**
 * Checks if there ware any changes to ANY player discards in the game.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discard changes.
 * @return bool - true if any discard changes occurred for any players, false if not.
 */
bool any_player_discard_did_change(struct gameState* pre, struct gameState* post) {
  for (int i = 0; i < pre->numPlayers; i++) {
    if (player_discard_delta(pre, post, i) != 0) {
      return true;
    }
  }

  return false;
}


/***************************************
 * Resets / Emptying
 **************************************/

/**
 * Empties a player's hand by setting all the cards in the
 * hand to -1 and setting the hand count to 0.
 * 
 * @param state - a pointer to a game state.
 * @param player - an integer representing a player in the game.
 */
void empty_player_hand(struct gameState* state, int player) {
  for (int i = 0; i < MAX_HAND; i++) {
    state->hand[player][i] = -1;
  }

  state->handCount[player] = 0;
}


/**
 * Empties a player's deck by setting all the cards in the
 * deck to -1 and setting the deck count to 0.
 * 
 * @param state - a pointer to a game state.
 * @param player - an integer representing a player in the game.
 */
void empty_player_deck(struct gameState* state, int player) {
  for (int i = 0; i < MAX_DECK; i++) {
    state->deck[player][i] = -1;
  }

  state->deckCount[player] = 0;
}


/**
 * Empties a player's discard by setting all the cards in the
 * discard to -1 and setting the discard count to 0.
 * 
 * @param state - a pointer to a game state.
 * @param player - an integer representing a player in the game.
 */
void empty_player_discard(struct gameState* state, int player) {
  for (int i = 0; i < state->discardCount[player]; i++) {
    state->discard[player][i] = -1;
  }

  state->discardCount[player] = 0;
}




/***************************************
 * total player cards
 ***************************************/

/**
 * Return the total number of cards in a given player's card circulation
 * while inspecting a given game state.
 * 
 * @param state - a pointer to a gameState structure
 * @param player - an integer that indicates a particular player to count total cards for.
 * @returns int - the total cards in circulation for the player.
 */
int player_total_cards_in_state(struct gameState* state, int player) {
  return state->discardCount[player] + state->handCount[player] + state->deckCount[player];
}


/**
 * Return the difference in total number of cards in a given player's card 
 * circulation after some change in game state.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discardCount changes.
 * @returns int - the difference in total cards
 */
int player_total_cards_difference(struct gameState* pre, struct gameState* post, int player) {
  int preCards = player_total_cards_in_state(pre, player);
  int postCards = player_total_cards_in_state(post, player);

  if (DEBUG) print(stderr, "total cards | player: %d | pre: %-2d post: %d\n", player, preCards, postCards);
  return postCards - preCards;
}


/**
 * Return the change in total number of cards in a given player's card 
 * circulation after some change in game state.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - the player index to NOT check for discardCount changes.
 * @returns int - the amount of change in total cards.
 */
int player_total_cards_delta(struct gameState* pre, struct gameState* post, int player) {
  return abs(player_total_cards_difference(pre, post, player));
}




/***************************************
 * card supplies
 ***************************************/

/**
 * Returns the difference in the amount supply count of a specified card between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param card - an integer representing a specific card to check the supply count difference for.
 * @returns - int - the difference in supply count in the post gameState as opposed to the supplyCount
 *  of the same card in the pre gameState/
 * @note - a positive result means that the supplyCount increased from pre to post gameState, and
 *  a negative result means that the supplyCount decreased from pre to post gameState.
 */
int card_supplycount_difference(struct gameState* pre, struct gameState* post, int card) {
  int preSupply = supplyCount(card, pre);
  int postSupply = supplyCount(card, post);

  if (DEBUG) {
    char name[MAX_CARD_NAME_LENGTH];
    memset(name, '\0', MAX_CARD_NAME_LENGTH);
    strcpy(name, getCardName(card));
    print(stderr, "supply count | card: %-12s | pre: %-2d post: %d\n", name, preSupply, postSupply);
  }

  return postSupply - preSupply;
}


/**
 * Returns the change in the amount supply count of a specified card between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param card - an integer representing a specific card to check the supply count difference for.
 * @returns - int - the difference in supply count in the post gameState as opposed to the supplyCount
 *  of the same card in the pre gameState/
 * @note - a positive result means that the supplyCount increased from pre to post gameState, and
 *  a negative result means that the supplyCount decreased from pre to post gameState.
 */
int card_supplycount_delta(struct gameState* pre, struct gameState* post, int card) {
  return abs(card_supplycount_difference(pre, post, card));
}


/**
 * Checks if the supply count for a specified card changed between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param card - an integer representing a specific card to check for a supply count change.
 * @returns - bool - true if the supply count changed, false if not.
 */
bool did_card_supplycount_change(struct gameState* pre, struct gameState* post, int card) {
  return supplyCount(card, post) - supplyCount(card, pre) != 0;
}


/**
 * Returns the change amount in the amount of victory cards between two gameStates.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @returns an integer that represents the change in the victory card decks in the game.
 */
int victory_card_delta(struct gameState* pre, struct gameState* post) {
  return card_supplycount_delta(pre, post, estate)
    + card_supplycount_delta(pre, post, duchy)
    + card_supplycount_delta(pre, post, province)
    + card_supplycount_delta(pre, post, gardens)
    + card_supplycount_delta(pre, post, great_hall);
}


/**
 * Returns the change amount in the amount of kingfom cards between two gameStates.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @returns an integer that represents the change in the kingdom card decks in the game.
 */
int kingdom_card_delta(struct gameState* pre, struct gameState* post) {
  return card_supplycount_delta(pre, post, adventurer)
    + card_supplycount_delta(pre, post, council_room)
    + card_supplycount_delta(pre, post, feast)
    + card_supplycount_delta(pre, post, gardens)
    + card_supplycount_delta(pre, post, mine)
    + card_supplycount_delta(pre, post, remodel)
    + card_supplycount_delta(pre, post, smithy)
    + card_supplycount_delta(pre, post, village)
    + card_supplycount_delta(pre, post, baron)
    + card_supplycount_delta(pre, post, great_hall)
    + card_supplycount_delta(pre, post, minion)
    + card_supplycount_delta(pre, post, steward)
    + card_supplycount_delta(pre, post, tribute)
    + card_supplycount_delta(pre, post, ambassador)
    + card_supplycount_delta(pre, post, cutpurse)
    + card_supplycount_delta(pre, post, embargo)
    + card_supplycount_delta(pre, post, outpost)
    + card_supplycount_delta(pre, post, salvager)
    + card_supplycount_delta(pre, post, sea_hag)
    + card_supplycount_delta(pre, post, treasure_map);
}



/***************************************
 * individual card instances
 ***************************************/

/**
 * Returns the index of the nth instance of a specific
 * card in a given player's hand. If the card does not
 * have n instances in the player's hand, then -1 is returned.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @param n - and integer representing which instance of the card to look for.
 * @returns int
 */
int card_nth_hand_pos(struct gameState* state, int player, int card, int n) {
  int numFound = 0;
  int pos = -1;
  int i = 0;

  if (n > 0) {
    // look from start to end.
    while (i < state->handCount[player] && numFound < n) {
      if (state->hand[player][i] == card) {
        numFound++;
        pos = i;
      }

      i++;
    }
  } else if (n < 0) {
    i = state->handCount[player];
    n = -n;

    // look from end to start.
    while (i >= 0 && numFound < n) {
      if (state->hand[player][i] == card) {
        numFound++;
        pos = i;
      }

      i--;
    }
  }

  return numFound == n ? pos : -1;
}


/**
 * Returns the index of the first instance of a specific
 * card in a given player's hand. If there are no instances
 * of the specified card in the player's hand, then the function
 * returns -1.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @returns int
 */
int card_first_hand_pos(struct gameState* state, int player, int card) {
  return card_nth_hand_pos(state, player, card, 1);
}


/**
 * Returns the index of the last instance of a specific
 * card in a given player's hand. If there are no instances
 * of the specified card in the player's hand, then the function
 * returns -1.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @returns int
 */
int card_last_hand_pos(struct gameState* state, int player, int card) {
  return card_nth_hand_pos(state, player, card, -1);
}




/**
 * Returns the index of the nth instance of a specific
 * card in a given player's deck. If the card does not
 * have n instances in the player's deck, then -1 is returned.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @param n - and integer representing which instance of the card to look for.
 * @returns int
 */
int card_nth_deck_pos(struct gameState* state, int player, int card, int n) {
  int numFound = 0;
  int pos = -1;
  int i = 0;

  if (n > 0) {
    // look from start to end.
    while (i < state->deckCount[player] && numFound < n) {
      if (state->deck[player][i] == card) {
        numFound++;
        pos = i;
      }

      i++;
    }
  } else if (n < 0) {
    i = state->deckCount[player];
    n = -n;

    // look from end to start.
    while (i >= 0 && numFound < n) {
      if (state->deck[player][i] == card) {
        numFound++;
        pos = i;
      }

      i--;
    }
  }

  return numFound == n ? pos : -1;
}


/**
 * Returns the index of the first instance of a specific
 * card in a given player's deck. If there are no instances
 * of the specified card in the player's deck, then the function
 * returns -1.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @returns int
 */
int card_first_deck_pos(struct gameState* state, int player, int card) {
  return card_nth_deck_pos(state, player, card, 1);
}


/**
 * Returns the index of the last instance of a specific
 * card in a given player's deck. If there are no instances
 * of the specified card in the player's deck, then the function
 * returns -1.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @returns int
 */
int card_last_deck_pos(struct gameState* state, int player, int card) {
  return card_nth_deck_pos(state, player, card, -1);
}




/**
 * Returns the index of the nth instance of a specific
 * card in a given player's discard. If the card does not
 * have n instances in the player's discard, then -1 is returned.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @param n - and integer representing which instance of the card to look for.
 * @returns int
 */
int card_nth_discard_pos(struct gameState* state, int player, int card, int n) {
  int numFound = 0;
  int pos = -1;
  int i = 0;

  if (n > 0) {
    // look from start to end.
    while (i < state->discardCount[player] && numFound < n) {
      if (state->discard[player][i] == card) {
        numFound++;
        pos = i;
      }

      i++;
    }
  } else if (n < 0) {
    i = state->discardCount[player];
    n = -n;

    // look from end to start.
    while (i >= 0 && numFound < n) {
      if (state->discard[player][i] == card) {
        numFound++;
        pos = i;
      }

      i--;
    }
  }

  return numFound == n ? pos : -1;
}


/**
 * Returns the index of the first instance of a specific
 * card in a given player's discard. If there are no instances
 * of the specified card in the player's discard, then the function
 * returns -1.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @returns int
 */
int card_first_discard_pos(struct gameState* state, int player, int card) {
  return card_nth_discard_pos(state, player, card, 1);
}


/**
 * Returns the index of the last instance of a specific
 * card in a given player's discard. If there are no instances
 * of the specified card in the player's discard, then the function
 * returns -1.
 * 
 * @param state - a pointer to a gameState structure.
 * @param player - an integer representing a player in the game.
 * @param card - an integer representing a specific card type
 * @returns int
 */
int card_last_discard_pos(struct gameState* state, int player, int card) {
  return card_nth_discard_pos(state, player, card, -1);
}




/**
 * Returns the number of instances of a specific card that are in a 
 * given player's hand for a given game state.
 * 
 * @param state - a pointer to a gameState structure.
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_total_in_hand(struct gameState* state, int card, int player) {
  int total = 0;

  for (int i = 0; i < state->handCount[player]; i++) {
    if (state->hand[player][i] == card) total++;
  }

  if (DEBUG) {
    char name[MAX_CARD_NAME_LENGTH];
    memset(name, '\0', MAX_CARD_NAME_LENGTH);
    strcpy(name, getCardName(card));
    print(stderr, "# of card type in hand | card: %-12s | player: %d | total: %d\n", name, player, total);
  }
    
  return total;
}


/**
 * Returns the number of instances of a specific card that are in a 
 * given player's deck for a given game state.
 * 
 * @param state - a pointer to a gameState structure.
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_total_in_deck(struct gameState* state, int card, int player) {
  int total = 0;

  for (int i = 0; i < state->deckCount[player]; i++) {
    if (state->deck[player][i] == card) total++;
  }

  if (DEBUG) {
    char name[MAX_CARD_NAME_LENGTH];
    memset(name, '\0', MAX_CARD_NAME_LENGTH);
    strcpy(name, getCardName(card));
    print(stderr, "# of card type in deck | card: %-12s | player: %d | total: %d\n", name, player, total);

  }

  return total;
}


/**
 * Returns the number of instances of a specific card that are in a player's full deck
 * 
 * @param state - a pointer to a gameState structure.
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_total_in_full_deck(struct gameState* state, int card, int player) {
  int total = fullDeckCount(player, card, state);

  if (DEBUG) {
    char name[MAX_CARD_NAME_LENGTH];
    memset(name, '\0', MAX_CARD_NAME_LENGTH);
    strcpy(name, getCardName(card));
    print(stderr, "full deck count | card: %-12s | player: %d | total: %d\n", name, player, total);

  }

  return total;
}


/**
 * Returns the number of instances of a specific card that are in a 
 * given player's discard pile for a given game state.
 * 
 * @param state - a pointer to a gameState structure.
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_total_in_discard(struct gameState* state, int card, int player) {
  int total = 0;

  for (int i = 0; i < state->discardCount[player]; i++) {
    if (state->discard[player][i] == card) total++;
  }

  if (DEBUG) {
    char name[MAX_CARD_NAME_LENGTH];
    memset(name, '\0', MAX_CARD_NAME_LENGTH);
    strcpy(name, getCardName(card));
    print(stderr, "# of card type in discard | card: %-12s | player: %d | total: %d\n", name, player, total);
  }

  return total;
}


/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's hand between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_difference_in_hand(struct gameState* pre, struct gameState* post, int card, int player) {
  if (DEBUG) print(stderr, "%-4s | ", "pre");
  int numCardTypePre = player_card_type_total_in_hand(pre, card, player);

  if (DEBUG) print(stderr, "%-4s | ", "post");
  int numCardTypePost = player_card_type_total_in_hand(post, card, player);

  return numCardTypePost - numCardTypePre;
}


/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's deck between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_difference_in_deck(struct gameState* pre, struct gameState* post, int card, int player) {
  if (DEBUG) print(stderr, "%-4s | ", "pre");
  int numCardTypePre = player_card_type_total_in_deck(pre, card, player);

  if (DEBUG) print(stderr, "%-4s | ", "post");
  int numCardTypePost = player_card_type_total_in_deck(post, card, player);

  return numCardTypePost - numCardTypePre;
}


/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's discard pile between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_difference_in_discard(struct gameState* pre, struct gameState* post, int card, int player) {
  if (DEBUG) print(stderr, "%-4s | ", "pre");
  int numCardTypePre = player_card_type_total_in_discard(pre, card, player);

  if (DEBUG) print(stderr, "%-4s | ", "post");
  int numCardTypePost = player_card_type_total_in_discard(post, card, player);

  return numCardTypePost - numCardTypePre;
}


/**
 * Returns the difference in the number of instances of a specific card type
 * in a player's full deck between two game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param card - an integer representing a specific card type
 * @param player - an integer representing a player in the game.
 * @returns int
 */
int player_card_type_difference_in_full_deck(struct gameState* pre, struct gameState* post, int card, int player) {
  if (DEBUG) print(stderr, "%-4s | ", "pre");
  int numCardTypePre = player_card_type_total_in_full_deck(pre, card, player);

  if (DEBUG) print(stderr, "%-4s | ", "post");
  int numCardTypePost = player_card_type_total_in_full_deck(post, card, player);

  return numCardTypePost - numCardTypePre;
}



/***************************************
 * treasure cards
 ***************************************/

/**
 * Checks if a given card represents a treasure card
 * 
 * @param card - an integer representing a card type
 * @returns bool - true if the card is a treasure card, false if not.
 */
bool is_treasure_card(int card) {
  return card == copper || card == silver || card == gold;
}


/**
 * Get the total number of treasure cards in a player's hand in a given game state.
 * 
 * @param state - the game state containing the player's hand information.
 * @param player - an integer representing the player
 * @returns int
 */
int player_treasure_cards_in_hand(struct gameState* state, int player) {
  int total = 0;

  for (int i = 0; i < state->handCount[player]; i++) {
    if (is_treasure_card(state->hand[player][i])) total++;
  }

  if (DEBUG) print(stderr, "treasure cards in hand | player: %d | total: %d\n", player, total);
  return total;
}


/**
 * Get the total number of treasure cards in a player's deck in a given game state.
 * 
 * @param state - the game state containing the player's deck information.
 * @param player - an integer representing the player
 * @returns int
 */
int player_treasure_cards_in_deck(struct gameState* state, int player) {
  int total = 0;

  for (int i = 0; i < state->deckCount[player]; i++) {
    if (is_treasure_card(state->deck[player][i])) total++;
  }

  if (DEBUG) print(stderr, "treasure cards in deck | player: %d | total: %d\n", player, total);
  return total;
}


/**
 * Get the total number of treasure cards in a player's discard in a given game state.
 * 
 * @param state - the game state containing the player's discard information.
 * @param player - an integer representing the player
 * @returns int
 */
int player_treasure_cards_in_discard(struct gameState* state, int player) {
  int total = 0;

  for (int i = 0; i < state->discardCount[player]; i++) {
    if (is_treasure_card(state->discard[player][i])) total++;
  }

  if (DEBUG) print(stderr, "treasure cards in discard | player: %d | total: %d\n", player, total);
  return total;
}


/**
 * Returns the difference in treasure cards in a player's hand between two different game states.
 *
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - an integer representing a player in the game.
 */
int player_treasure_card_difference_in_hand(struct gameState* pre, struct gameState* post, int player) {
  if (DEBUG) print(stderr, "%-4s | ", "pre");
  int treasurePre = player_treasure_cards_in_hand(pre, player);

  if (DEBUG) print(stderr, "%-4s | ", "post");
  int treasurePost = player_treasure_cards_in_hand(post, player);

  return treasurePost - treasurePre;
}


/**
 * Returns the difference in treasure cards in a player's deck between two different game states.
 *
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 * @param player - an integer representing a player in the game.
 */
int player_treasure_card_difference_in_deck(struct gameState* pre, struct gameState* post, int player) {
  if (DEBUG) print(stderr, "%-4s | ", "pre");
  int treasurePre = player_treasure_cards_in_deck(pre, player);

  if (DEBUG) print(stderr, "%-4s | ", "post");
  int treasurePost = player_treasure_cards_in_deck(post, player);

  return treasurePost - treasurePre;
}


/***************************************
 * actions
 ***************************************/

/**
 * Returns the difference in the number of actions available between two different game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 */
int game_actions_difference(struct gameState* pre, struct gameState* post) {
  if (DEBUG) print(stderr, "actions | pre: %-2d post: %d\n", pre->numActions, post->numActions);
  return post->numActions - pre->numActions;
}

/**
 * Returns the difference in the number of total cards played between two different game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 */
int cards_played_difference(struct gameState* pre, struct gameState* post) {
  if (DEBUG) print(stderr, "cards played | pre: %-2d post: %d\n", pre->playedCardCount, post->playedCardCount);
  return post->playedCardCount - pre->playedCardCount;
}

/**
 * Returns the difference in the number of buys between two different game states.
 * 
 * @param pre - a pointer to a gameState structure (assumed before some action has taken place).
 * @param post - a pointer to a gameState structure (assumed after some action has taken place).
 */
int game_buys_difference(struct gameState* pre, struct gameState* post) {
  if (DEBUG) print(stderr, "buys | pre: %-2d post: %d\n", pre->numBuys, post->numBuys);
  return post->numBuys - pre->numBuys;
}


/***************************************
 * state
 ***************************************/

/**
 * Resets one gameState to match another by copying the 'base' gamestate
 * into the 'copy' version of the state.
 */
void rebaseGameState(struct gameState* pre, struct gameState* post) {
  memcpy(post, pre, sizeof(struct gameState));
}