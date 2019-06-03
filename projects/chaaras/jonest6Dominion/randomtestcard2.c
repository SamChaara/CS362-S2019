#include "randomHelpers.h"
#include "printHelpers.h"
#include "testHelpers.h"



// the number of times to test the card
#define DEFAULT_TRIALS 500

// the card being tested
#define TEST_CARD "sea hag"
#define TEST_FUNCTION "seaHagEffect"



/**
 * Runs a test case for the villageEffect function and prints the test results accordingly.
 */
void checkSeaHag(struct gameState* pre, struct gameState* post, int player, int* totalPassed, int* totalFailed) {
  const int TEST_CASES = 8;
  int passingTests = TEST_CASES;
  char* rule;

  // run the test case
  seaHagEffect(player, post);


 /* Test #1 -- There should NOT be any player's whose hand count changes. */
  rule = "There should NOT be any player whose hand count changes.";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, false, any_player_handcount_did_change(pre, post))) {
    passingTests--;
  }


  /* Test #2 -- All other players should have a curse on the top of their deck. */
  rule = "All other players should have a curse on the top of their deck";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, true, all_other_top_of_deck_is_card(post, player, curse))) {
    passingTests--;
  }


  /* Test #3 -- The current player's discard count should NOT change */
  rule = "The current player's discard count should NOT change";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, false, player_discardcount_did_change(pre, post, player))) {
    passingTests--;
  }


  /* Test #4 -- All other player's discard count should increase by 1 (each). */
  rule = "All other player's discard count should increase by 1 (each)";
  printDebugRule(rule);
  if (!testEqualToInt(TEST_FUNCTION, rule, pre->numPlayers - 1, other_players_combined_discardcount_delta(pre, post, player))) {
    passingTests--;
  }


  /* Test #5 -- The current player's deck count should not change. */
  rule = "The current player's deck count should not change";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, false, player_deckcount_did_change(pre, post, player))) {
    passingTests--;
  }

  /* Test #6 -- The current player's deck should not change. */
  rule = "The current player's deck should not change";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, false, player_deck_did_change(pre, post, player))) {
    passingTests--;
  }


  /* Test #7 -- There shouldn't be any change to the pile of victory cards. */
  rule = "No state change should occur to the victory card pile";
  printDebugRule(rule);
  if (!testEqualToInt(TEST_FUNCTION, rule, 0, victory_card_delta(pre, post))) {
    passingTests--;
  }


  /* Test #8 -- There shouldn't be any change to the pile of kingdom cards. */
  rule = "No state change should occur to the kingdom card pile";
  printDebugRule(rule);
  if (!testEqualToInt(TEST_FUNCTION, rule, 0, kingdom_card_delta(pre, post))) {
    passingTests--;
  }


  *totalPassed += passingTests;
  *totalFailed += (TEST_CASES - passingTests);

  // if any tests failed, print the state for inspection.
  if (TEST_CASES - passingTests > 0) {
    fprintf(stderr, "\n\nPRE: "); printState(pre);
    fprintf(stderr, "\nPOST: "); printState(post);
  }
}




int main(int argc, char** argv) {
  // seed random
  srand(time(NULL));

  // 
  // constants
  // 
  const int TRIALS = argc >= 2 ? atoi(argv[1]) : DEFAULT_TRIALS;

  // 
  // state variables
  // 
  int seed;
  int numPlayers;
  int currentPlayer;
  int cards[10];

  struct gameState pre;
  struct gameState post;

  int totalPassed = 0;
  int totalFailed = 0;

  // 
  // trials
  // 

  printf("\nCard: %s\nFunction: %s\n\n", TEST_CARD, TEST_FUNCTION);
  printf("** PHASE 1 :: %d TESTS :: Initializing a new game for each %s card test...\n", TRIALS, TEST_CARD);

  for (int i = 0; i < TRIALS; i++) {
    // randomize the state variables
    seed = randInt();
    numPlayers = randIntRange(2, 4);
    currentPlayer = randIntRange(0, numPlayers - 1);
    getRandomKingdomCards(cards);

    // make sure the sea_hag card is one of the kingdom cards
    if (!inArray(cards, 10, sea_hag)) {
      cards[0] = sea_hag;
    }

    if (!inArray(cards, 10, curse)) {
      cards[1] = curse;
    }

    initializeGame(numPlayers, cards, seed, &pre);
    randomizePlayerHands(cards, &pre);
    randomizePlayerDecks(cards, &pre);
    
    pre.whoseTurn = currentPlayer;

    rebaseGameState(&pre, &post);
    checkSeaHag(&pre, &post, pre.whoseTurn, &totalPassed, &totalFailed);
  }


  printf("** PHASE 2 :: %d TESTS :: Testing %s card on continous game...\n", TRIALS, TEST_CARD);
  for (int i = 0; i < TRIALS; i++) {
    post.whoseTurn = randIntRange(0, post.numPlayers - 1);
    rebaseGameState(&post, &pre);

    // if the current player doesn't have any sea hag cards, then we don't
    // need to run the test cases for this player.
    if (card_first_hand_pos(&pre, pre.whoseTurn, sea_hag) == -1 || supplyCount(curse, &pre) == 0) {
      continue;
    }

    checkSeaHag(&pre, &post, pre.whoseTurn, &totalPassed, &totalFailed);
  }


  // indicate test data
  printf("\n** Total Individual Tests: %d | Passed: %d | Failed: %d\n", (totalPassed + totalFailed), totalPassed, totalFailed);
  
  return 0;
}