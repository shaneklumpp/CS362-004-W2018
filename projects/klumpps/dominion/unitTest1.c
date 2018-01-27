/* -----------------------------------------------------------------------
 *Written by Shane Klumpp, unit Tests for getWinners function in dominion.

 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unitTest1: unitTest1.c dominion.o rngs.o
 *      gcc -o unitTest1 -g  unitTest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main(){
    //variables needed for basic testing
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("TESTING updateCoins():\n");
    
#if (NOISY_TEST == 1)
    printf("Test %d players with player 0 having more VP\n", numPlayer);
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    
    
    return 0;
}