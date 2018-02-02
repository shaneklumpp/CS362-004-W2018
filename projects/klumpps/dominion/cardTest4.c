/* -----------------------------------------------------------------------
 *Written by Shane Klumpp, cardTest for adventurerFunc
 
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardTest4: cardTest4.c dominion.o rngs.o
 *      gcc -o cardTest4 -g  cardTest4.c dominion.o rngs.o $(CFLAGS)
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
#define NOISY_TEST 2

int main(){
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int handpos = 1;
    int bugCount = 0;
    int testPassed = 0;
    
    const char* CARDNames[] = {"curse", "estate" , "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
     "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
     "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    
    
    printf("TESTING adventurerFunc()\n");
    printf("TESTING adventurerFunc() with starting initalized deck of 7 coppers and 3 estates to test normal conditions\n");
    printf("For tests 1-7 normal conditions are tested\n");
    
    initializeGame(numPlayers, k, seed, &G); // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    
    
    for( i=0; i < numPlayers; i++) {
#if (NOISY_TEST == 1)
        printf("Player %d\n", i);
        printf("Verify starting coins in original state: %d\n", G.coins);
        printf("Verify starting deckCount in original state: %d\n", G.deckCount[i]);
        printf("Verify starting handCount in original state: %d\n", G.handCount[i]);
        printf("Verify starting discardCount in original state: %d\n", G.discardCount[i]);
        printf("Verify starting coins in test state: %d\n", testG.coins);
        printf("Verify starting deckCount in test state: %d\n", testG.deckCount[i]);
        printf("Verify starting handCount in test state: %d\n", testG.handCount[i]);
        printf("Verify starting discardCount in test state: %d\n\n", testG.discardCount[i]);
#endif
     }
    
    //start of tests
    //play card adventurer
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    
    printf("Test 1: Hand count of player 0 who played adventurer is incremented by 1\n");
    printf("Hand is updated by adding two treasure cards and discarding all other drawn cards + playing adventurer\n");
    
#if (NOISY_TEST == 1)
    //+2 - 1 because 2 treasure cards are drawn and 1 card is played. Handcount increase by 1
    printf("Expected hand count: %d, Actual hand count %d\n", G.handCount[0] + 2 - 1, testG.handCount[0]); 
#endif
    
    if(testG.handCount[0] == (G.handCount[0] + 2 - 1)){
        printf("Test 1 PASSED: Handcount was increased by 1 cards\n");
        testPassed++;
    }
    else{
        printf("Test 1 FAILED: Handcount wasn't increased by 1 card check NOISY_TEST\n");
        bugCount++;
    }
    
    printf("Test 2: The two cards that were drawn are treasure cards in player 0's hand\n");
    
#if (NOISY_TEST == 1)
    printf("Top two cards drawn are numbers %d and %d\n", testG.hand[0][testG.handCount[0]-1], testG.hand[0][testG.handCount[0]-2]);
    printf("Top two card names are %s and %s\n", CARDNames[testG.hand[0][testG.handCount[0]-1]], CARDNames[testG.hand[0][testG.handCount[0]-2]]);
#endif    
    
    if((testG.hand[0][testG.handCount[0]-1] == copper || silver || gold) && (testG.hand[0][testG.handCount[0]-2] == copper || silver || gold)){
        printf("Test 2 passed. Top two cards in hand are treasure cards!\n");
        testPassed++;
    }
    else{
        printf("Test 2 failed. Top two cards aren't both treasure check NOISY_TEST\n");
        bugCount++;
    }
    
    printf("Test 3: Test that player 0's deck count has decreased by at least 2\n");
    
#if(NOISY_TEST == 1)
    printf("original deck count %d, espected deck count <= %d, actual deck count %d\n", G.deckCount[0], G.deckCount[0] - 2, testG.deckCount[0]);
#endif
    
    if(testG.deckCount[0] <= G.deckCount[0] - 2){
        printf("Test 3 PASSED: deckCount was decremented by at least 2\n");
        testPassed++;
    }
    else{
        printf("Test 3 FAILED: deckCount wasn't decremented by at least 2, check NOISY_TEST\\n");
        bugCount++;
    }
    
    
    printf("Test 4: playedCardCount has increased by 1 when adventurer is played\n");
    
#if (NOISY_TEST == 1)
    printf("After adventurer playedCardCount = %d, expected = %d, original playedCardCount %d\n", testG.playedCardCount, G.playedCardCount + 1, G.playedCardCount);
#endif

    if(testG.playedCardCount == G.playedCardCount + 1){
        printf("TEST 4 PASSED: playedCardCount increased by 1\n");
        testPassed++;
    }
    else{
        printf("TEST 4 FAILED: playedCardCount didn't increase by exactly 1 check NOISY_TEST\n");
        bugCount++;
    }
    
    printf("Test 5: check that no state change happened for player 1\n");
    
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
        printf("Test 5 PASSED! No state change happened to player 1\n");
        testPassed++;
    }
    
    printf("Test 6: check for state changes to victory card piles\n");
    
#if (NOISY_TEST == 1)
    printf("Original victory card supply estate: %d, Tested victory card supply estate %d\n", G.supplyCount[estate], testG.supplyCount[estate]);
    printf("Original victory card supply duchy: %d, Tested victory card supply duchy %d\n", G.supplyCount[duchy], testG.supplyCount[duchy]);
    printf("Original victory card supply province: %d, Tested victory card supply province %d\n", G.supplyCount[province], testG.supplyCount[province]);
#endif
    //check victory cards
    if(G.supplyCount[estate] == testG.supplyCount[estate] && G.supplyCount[duchy] == testG.supplyCount[duchy] && G.supplyCount[province] == testG.supplyCount[province]){
        printf("Test 6 PASSED! no state changes to victory card piles\n");
        testPassed++;
    }
    else{
        printf("TEST 6 FAILED! there was a state change to victory card piles\n");
        bugCount++;
    }
    
    printf("Test 7: check for state changes to kingdom card piles\n");
    
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
            
            printf("Test 7 FAILED: state change of a kingdom card pile changed check NOISE_TEST 1\n");
            bugCount++;
        } 
    else{
        printf("Test 7 PASSED! no state change to kingdomCards!\n");
        testPassed++;
    }
    
    
    printf("\n\nResetting deck of player 0 to contain estate, copper, mine, minion, gold to test functionality of adventurer when the first 2 cards aren't copper\n");
    printf("Resetting memstate to original\n");    
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    
    printf("Setting G/testG state handCount to 1 with adventurer. Setting player 0 deck in order to estate, copper, mine, minion, gold\n");
    printf("Only player 0 state should have changed. Check NOISY_TEST to confirm if necessary\n");
    
    G.hand[0][0] = adventurer;
    G.handCount[0] = 1;
    G.deck[0][0] = estate;
    G.deck[0][1] = copper;
    G.deck[0][2] = mine;
    G.deck[0][3] = minion;
    G.deck[0][4] = gold;
    
    testG.hand[0][0] = adventurer;
    testG.handCount[0] = 1;
    testG.deck[0][0] = estate;
    testG.deck[0][1] = copper;
    testG.deck[0][2] = mine;
    testG.deck[0][3] = minion;
    testG.deck[0][4] = gold;
    
    
    for( i=0; i < numPlayers; i++) {
#if (NOISY_TEST == 2)
        printf("Player %d\n", i);
        printf("Verify starting coins in original state: %d\n", G.coins);
        printf("Verify starting deckCount in original state: %d\n", G.deckCount[i]);
        printf("Verify starting handCount in original state: %d\n", G.handCount[i]);
        printf("Verify starting discardCount in original state: %d\n", G.discardCount[i]);
        printf("Verify starting coins in test state: %d\n", testG.coins);
        printf("Verify starting deckCount in test state: %d\n", testG.deckCount[i]);
        printf("Verify starting handCount in test state: %d\n", testG.handCount[i]);
        printf("Verify starting discardCount in test state: %d\n\n", testG.discardCount[i]);
#endif
     }
     
    handpos = 0; 
    
    printf("Test 8: cards should stop drawing when two treasures are drawn when adventurer is played\n");
    printf("Test 8 conditions: deck count should decrease by 4 since order of draw is gold, minion, mine, copper\n");
    printf("Test 8 conditions: discard count should increase by 2 with minion and mine discarded\n");
    printf("Test 8 conditions: handCount should increase by 1 as copper and gold are added and adventurer played\n");
    
    //play adventurer with deck/hand that we have created for test 8
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
#if (NOISY_TEST == 2)
    printf("Original deck count %d, espected deck count = %d, actual deck count %d\n", G.deckCount[0], G.deckCount[0] - 4, testG.deckCount[0]);
    printf("Original discardCount %d, expected discardCount %d, actual discardCount %d\n", G.discardCount[0], G.discardCount[0]+2, testG.discardCount[0]);
    printf("Original handCount %d, Expected handCount: %d, Actual hand count %d\n",G.handCount[0], G.handCount[0] + 2 - 1, testG.handCount[0]);
#endif
    
    if(G.deckCount[0] - 4 == testG.deckCount[0] && G.discardCount[0]+2 == testG.discardCount[0] && (G.handCount[0] + 2 - 1) == testG.handCount[0]){
        printf("Test 8 PASSED: All conditions were met\n");
        testPassed++;
    }
    else{
        printf("Test 8 FAILED: All conditions were not met check NOISY_TEST for details\n");
        bugCount++;
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