#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

bool linearSearch(int* arr, int len, int val)
{
	bool found = false;

	for (int i = 0; i < len; i++)
	{
		if(*(arr + i) == val)
		{
			found = true;
		}
	}

	return found;
}

int initializeRandomGame(int k[10], struct gameState* G)
{
	/*Generate a random number of players (2-4)*/
	int numPlayers = rand() % 2 + 2;

	/*Generate a random seed for the game*/
	int rSeed = rand();

	/***Begin generating random Kingdom cards***/
	int testedCard = adventurer;
	int allCards = 27;
	int nonKingdomCards = 7;
	int kingdomCards = allCards - nonKingdomCards;
	int kCards = 0;
	int maxKCards = 10;
	
	//Add the card being tested to k
	k[kCards] = testedCard;
	kCards++;

	//Populate the rest of k with random kingdom cards
	while(kCards < maxKCards)
	{
		//Generate a random kingdom card (exclude Base/non-Kingdom cards)
		int randomKingdomCard = (rand() % (kingdomCards)) + nonKingdomCards;

		//Add the randomnly-generated Kingdom card to k if it's not already in k
		if(linearSearch(k, maxKCards, randomKingdomCard) == false)
		{
			k[kCards] = randomKingdomCard;
			kCards++;
		}
	}
	/***End generating random Kingdom cards***/

	// for(int i = 0; i < maxKCards; i++)
	// {
	// 	printf("%d\t", k[i]);
	// }
	// printf("\n");

	return initializeGame(numPlayers, k, rSeed, G);
}

int testAdventurer(struct gameState *state)
{
	int failure = 0;
	struct gameState orig;
	memcpy(&orig, state, sizeof(struct gameState));

	int player = whoseTurn(state);
	int lastCard = state->hand[player][state->handCount[player]-1];

	int ret = adventurerEffect(state);
	//assert(ret == 0);
	if(!(ret == 0))
	{
		failure = 1;
	}

	//Assert that the player drew two cards
	//assert(state->handCount[player] == orig.handCount[player] + 2);
	if(!(state->handCount[player] == orig.handCount[player] + 2))
	{
		failure = 1;
	}

	//Get the value of the last two cards drawn and the card that preceded them
	int card1 = state->hand[player][state->handCount[player]-2];
	int card2 = state->hand[player][state->handCount[player]-1];

	//Assert that the last two cards drawn were Treasure cards
	//assert(card1 == copper || card1 == silver || card1 == gold);
	//assert(card2 == copper || card2 == silver || card2 == gold);

	if(!(card1 == copper || card1 == silver || card1 == gold))
	{
		failure = 1;
	}
	if(!(card2 == copper || card2 == silver || card2 == gold))
	{
		failure = 1;
	}

	//Assert that the card that precedes the two drawn cards is the card that
	//originally was the last card in hand.
	//assert(lastCard == state->hand[player][state->handCount[player]-3]);
	if(!(lastCard == state->hand[player][state->handCount[player]-3]))
	{
		failure = 1;
	}

	return failure;
}

int main()
{
	srand(0);

	printf("Random Tests: Adventurer\n");

	int total = 1000;
	int passed = 0;
	int failed = 0;

	for(int i = 0; i < total; i++)
	{
		struct gameState G;
		int k[10];
		int r;

		int init = initializeRandomGame(k, &G);

		if(init == 0)
		{
			r = testAdventurer(&G);
			if(r == 0)
			{
				//printf(".");
				passed++;
			}
			else
			{
				//printf("x");
				failed++;
			}
		}
	}
	printf("\n%d Tests Completed\n\nPassed:\t%d\nFailed:\t%d\n", total, passed, failed);

	return 0;
}