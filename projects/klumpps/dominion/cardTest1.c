/* -----------------------------------------------------------------------
 *Written by Shane Klumpp, cardTest for smithy
 
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardTest1: cardTest1.c dominion.o rngs.o
 *      gcc -o cardTest1 -g  cardTest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main(){
    //int i, j;
    int seed = 1000;
    int numPlayer = 2;
    int bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handpos = 1;
    int newCards = 3; //should be 3 new cards
    int bugCount = 0;
    int testPassed = 0;
    printf("TESTING Smithy()\n");
    
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    
    printf("Playing smithy within cardEffect for player 0\n");
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("Test 1: check that player 0 received exactly 3 cards\n");
    
#if (NOISY_TEST == 1)
    printf("hand count = %d, expected = %d\n", testG.handCount[0], G.handCount[0] + newCards -1); //should have received 3 cards - 1 card that gets discarded
#endif

    if(testG.handCount[0] == G.handCount[0] + newCards - 1){ //test passed or didnt pass + bug counter
        printf("Test 1 PASSED. Exactly 3 cards were drawn!\n");
        testPassed++;
    }
    else{//not three cards drawn
        printf("Test 1 FAILED. A different amount of cards were drawn. BUG!!!\n");
        bugCount++;
    }
    
    printf("Test 2: check that player 0 cards came from his own deck\n");

#if (NOISY_TEST == 1)
    printf("original deck count of player 0: %d, new deck count %d\n", G.deckCount[0], testG.deckCount[0]);
    printf("original deck count of player 1: %d, new deck count player 1 check %d\n", G.deckCount[1], testG.deckCount[1]);
#endif
    
    if(G.deckCount[0] != testG.deckCount[0]){
        printf("Test 2: PASSED. Cards (regardless of number) came from player 0's deck\n");
        testPassed++;
    }
    else{
        printf("Test 2: FAILED. Cards didn't come from player 0's deck BUG!!!\n");
        bugCount++;
    }
    
    printf("Test 3: check that gameState playedCardCount has increased by 1\n");
    
#if (NOISY_TEST == 1)
    printf("original playerCardCount count: %d, tested state playerCardCount: %d\n", G.playedCardCount, testG.playedCardCount);
#endif
    
    if(testG.playedCardCount -1 == G.playedCardCount){
        printf("Test 3: PASSED! playedCardCount has increased\n");
        testPassed++;
    }
    else{
        printf("Test 3: FAILED! playedCardCount didn't increase in the test gameState\n");
        bugCount++;
    }
    
    printf("Test 4: check that no state change happened for player 1\n");
    
#if (NOISY_TEST == 1)
    printf("original deck count of player 1: %d, new deck count player 1 check %d\n", G.deckCount[1], testG.deckCount[1]);
    printf("original hand count of player 1: %d, new hand count player 1 check %d\n", G.handCount[1], testG.handCount[1]);
    printf("original discard count of player 1: %d, new discard count player 1 check %d\n", G.discardCount[1], testG.discardCount[1]);
#endif
    
    if(G.deckCount[1] != testG.deckCount[1] || G.handCount[1] != testG.handCount[1] || G.discardCount[1] != testG.discardCount[1]){
        printf("BUG!! state change to player 1. Check NOISE_TEST 1 for details\n");
        bugCount++;
    }
    else{
        printf("Test 4 PASSED! No state change happened to player 1\n");
        testPassed++;
    }
    
    printf("Test 5: check for state changes to victory card piles\n");
    
#if (NOISY_TEST == 1)
    printf("Original victory card supply estate: %d, Tested victory card supply estate %d\n", G.supplyCount[estate], testG.supplyCount[estate]);
    printf("Original victory card supply duchy: %d, Tested victory card supply duchy %d\n", G.supplyCount[duchy], testG.supplyCount[duchy]);
    printf("Original victory card supply province: %d, Tested victory card supply province %d\n", G.supplyCount[province], testG.supplyCount[province]);
#endif
    //check victory cards
    if(G.supplyCount[estate] == testG.supplyCount[estate] && G.supplyCount[duchy] == testG.supplyCount[duchy] && G.supplyCount[province] == testG.supplyCount[province]){
        printf("Test 5 PASSED! no state changes to victory card piles\n");
        testPassed++;
    }
    else{
        printf("TEST 5 FAILED! there was a state change to victory card piles\n");
        bugCount++;
    }
    
    printf("Test 6: check for state changes to kingdom card piles\n");
    
    /*I understand that this is a terrible way to run this test and I will complete it better in further uses of these cases
    but I am strapped for time right now trying to get this all done so I thought I would brute force it instead of play around
    with the most efficient way and lose time...*/
    
#if (NOISY_TEST == 1)
    printf("Original kingdom card supply adventurer: %d, Tested kingdom card supply adventurer %d\n", G.supplyCount[adventurer], testG.supplyCount[adventurer]);
    printf("Original kingdom card supply council_room: %d, Tested kingdom card supply council_room %d\n", G.supplyCount[council_room], testG.supplyCount[council_room]);
    printf("Original kingdom card supply feast: %d, Tested kingdom card supply feast %d\n", G.supplyCount[feast], testG.supplyCount[feast]);
    printf("Original kingdom card supply gardens: %d, Tested kingdom card supply gardens %d\n", G.supplyCount[gardens], testG.supplyCount[gardens]);
    printf("Original kingdom card supply mine: %d, Tested kingdom card supply mine %d\n", G.supplyCount[mine], testG.supplyCount[mine]);
    printf("Original kingdom card supply remodel: %d, Tested kingdom card supply remodel %d\n", G.supplyCount[remodel], testG.supplyCount[remodel]);
    printf("Original kingdom card supply smithy: %d, Tested kingdom card supply smithy %d\n", G.supplyCount[smithy], testG.supplyCount[smithy]);
    printf("Original kingdom card supply village: %d, Tested kingdom card supply village %d\n", G.supplyCount[village], testG.supplyCount[village]);
    printf("Original kingdom card supply baron: %d, Tested kingdom card supply baron %d\n", G.supplyCount[baron], testG.supplyCount[baron]);
    printf("Original kingdom card supply great_hall: %d, Tested kingdom card supply great_hall %d\n", G.supplyCount[great_hall], testG.supplyCount[great_hall]);
#endif

    if(G.supplyCount[adventurer] != testG.supplyCount[adventurer] || G.supplyCount[council_room] != testG.supplyCount[council_room] || G.supplyCount[feast] != testG.supplyCount[feast] || 
        G.supplyCount[gardens] != testG.supplyCount[gardens] || G.supplyCount[mine] != testG.supplyCount[mine] || G.supplyCount[remodel] != testG.supplyCount[remodel] || 
        G.supplyCount[smithy] != testG.supplyCount[smithy] || G.supplyCount[village] != testG.supplyCount[village] || G.supplyCount[baron] != testG.supplyCount[baron] || 
        G.supplyCount[great_hall] != testG.supplyCount[great_hall]){
            
            printf("Test 6 FAILED: state change of a kingdom card pile changed check NOISE_TEST 1\n");
            bugCount++;
        } 
    else{
        printf("Test 6 PASSED! no state change to kingdomCards!\n");
        testPassed++;
    }
    
    
    if(bugCount == 0){
        printf("All tests passed and no bugs were found!\n");
    }
    else{
        printf("There were %d tests that passed\n", testPassed);
        printf("There were %d bugs found\n", bugCount);
    }
    
    

    return 0;
}