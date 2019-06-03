#include "randomHelpers.h"
#include "printHelpers.h"
#include "testHelpers.h"



// the number of times to test the card
#define DEFAULT_TRIALS 500

// the card being tested
#define TEST_CARD "adventurer"
#define TEST_FUNCTION "adventurerEffect"




/**
 * Runs a test case for the adventurerEffect() function and prints the test results accordingly.
 */
void checkAdventurer(struct gameState* pre, struct gameState* post, int player, int* totalPassed, int* totalFailed) {
  int TEST_CASES = 5;
  int passingTests = TEST_CASES;
  char* rule;

  // run the test case
  adventurerEffect(player, post);


  int treasure_in_deck = player_treasure_cards_in_deck(pre, player);
  int treasure_in_discard = player_treasure_cards_in_discard(pre, player);


  if (treasure_in_deck + treasure_in_discard >= 2) {
    TEST_CASES += 2;
    passingTests += 2;

    /* Test #1 -- The current player's hand count should increase by 2. */
    rule = "The current player should receive exactly 2 additional cards";
    printDebugRule(rule);
    if (!testEqualToInt(TEST_FUNCTION, rule, +2, player_handcount_difference(pre, post, player))) {
      passingTests--;
    }

    /* Test #2 -- The current player's hand should have exactly 2 additional treasure cards. */
    rule = "The current player's hand should have exactly 2 additional treasure cards";
    printDebugRule(rule);
    if (!testEqualToInt(TEST_FUNCTION, rule, +2, player_treasure_card_difference_in_hand(pre, post, player))) {
      passingTests--;
    }
  }


  if (treasure_in_deck >= 2) {
    TEST_CASES += 2;
    passingTests += 2;

    /* Test #3 -- The current player's deck count should decrease by at least 2. */
    rule = "The current player's deck count should decrease by at least 2";
    printDebugRule(rule);
    if (!testAtMostInt(TEST_FUNCTION, rule, -2, player_deckcount_difference(pre, post, player))) {
      passingTests--;
    }

    /* Test #4 -- The current player's deck should have exactly 2 fewer treasure cards. */
    rule = "The current player's deck should have exactly 2 fewer treasure cards";
    printDebugRule(rule);
    if (!testEqualToInt(TEST_FUNCTION, rule, -2, player_treasure_card_difference_in_deck(pre, post, player))) {
      passingTests--;
    }
  }


  /* Test #5 -- No other player's hand count should change. */
  rule = "No other player's hand should change";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, false, any_other_player_hand_did_change(pre, post, player))) {
    passingTests--;
  }

  /* Test #6 -- No other player's deck count should change. */
  rule = "No other player's deck should change";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, false, any_other_player_deck_did_change(pre, post, player))) {
    passingTests--;
  }

  /* Test #7 -- No other player's discard pile count should change. */
  rule = "No other player's discard pile should change";
  printDebugRule(rule);
  if (!testEqualBool(TEST_FUNCTION, rule, false, any_other_player_discard_did_change(pre, post, player))) {
    passingTests--;
  }

  /* Test #8 -- There shouldn't be any change to the pile of victory cards. */
  rule = "No state change should occur to the victory card pile";
  printDebugRule(rule);
  if (!testEqualToInt(TEST_FUNCTION, rule, 0, victory_card_delta(pre, post))) {
    passingTests--;
  }

  /* Test #9 -- There shouldn't be any change to the pile of kingdom cards. */
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

    // make sure the adventurer card is one of the kingdom cards
    if (!inArray(cards, 10, adventurer)) {
      cards[0] = adventurer;
    }

    initializeGame(numPlayers, cards, seed, &pre);
    randomizePlayerHands(cards, &pre);
    randomizePlayerDecks(cards, &pre);
    pre.whoseTurn = currentPlayer;

    rebaseGameState(&pre, &post);
    checkAdventurer(&pre, &post, pre.whoseTurn, &totalPassed, &totalFailed);
  }


  printf("** PHASE 2 :: %d TESTS :: Testing %s card on continous game...\n", TRIALS, TEST_CARD);
  for (int i = 0; i < TRIALS; i++) {
    post.whoseTurn = randIntRange(0, post.numPlayers - 1);
    rebaseGameState(&post, &pre);
    checkAdventurer(&pre, &post, pre.whoseTurn, &totalPassed, &totalFailed);
  }


  // indicate test data
  printf("\n** Total Individual Tests: %d | Passed: %d | Failed: %d\n", (totalPassed + totalFailed), totalPassed, totalFailed);
  
  return 0;
}