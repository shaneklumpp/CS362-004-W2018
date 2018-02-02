#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

//adding cardEffect function prototypes here -Shane Klumpp
int smithyFunc(struct gameState *state, int handPos, int currentPlayer);
int villageFunc(struct gameState *state, int handPos, int *bonus, int currentPlayer);
int minionFunc(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer, int i, int j);
int adventurerFunc(struct gameState *state, int z, int drawntreasure, int currentPlayer, int temphand[], int handPos);
int outpostFunc(struct gameState *state, int handPos, int currentPlayer);
	       

#endif
