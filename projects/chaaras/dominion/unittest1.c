#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int testAdventurer(struct gameState *state)
{
	struct gameState orig;
	memcpy(&orig, state, sizeof(struct gameState));

	int player = whoseTurn(state);
	int lastCard = state->hand[player][state->handCount[player]-1];

	int ret = adventurerEffect(state);
	assert(ret == 0);

	//Assert that the player drew two cards
	assert(state->handCount[player] == orig.handCount[player] + 2);

	//Get the value of the last two cards drawn and the card that preceded them
	int card1 = state->hand[player][state->handCount[player]-2];
	int card2 = state->hand[player][state->handCount[player]-1];

	//Assert that the last two cards drawn were Treasure cards
	assert(card1 == copper || card1 == silver || card1 == gold);
	assert(card2 == copper || card2 == silver || card2 == gold);

	//Assert that the card that precedes the two drawn cards is the card that
	//originally was the last card in hand.
	assert(lastCard == state->hand[player][state->handCount[player]-3]);

	return ret;
}

int main()
{
	int init;
	int r;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, 
				 sea_hag, tribute, smithy, great_hall, steward};

	printf("Unit Test: Adventurer.\n");

	init = initializeGame(2, k, 1, &G);

	r = testAdventurer(&G);
	if(r == 0)
	{
		printf("Test passed.");
	}
	else
	{
		printf("Test failed.");
	}
	



	return 0;
}