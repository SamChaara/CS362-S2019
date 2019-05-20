#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool linearSearch(int* arr, int len, int val)
{
	bool found = false;
	int sizeOfInt = sizeof(int);
	int i = 0;

	for (i = 0; i < (len * sizeOfInt); i += sizeOfInt)
	{
		if(*(arr + i) == val)
		{
			found = true;
		}
	}

	return found;
}

int initializeRandomGame(struct gameState* G)
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
	int k[10];
	int kCards = 0;
	int maxKCards = 10;
	int returnValue;
	
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
	
	returnValue = initializeGame(numPlayers, k, rSeed, &G);
	return returnValue;
}

int main()
{
	srand(0);

	printf("Random Tests: Adventurer.\n");

	int init = initializeRandomGame;

	printf("initializeRandomGame return value: %d", init);

	return 0;
}