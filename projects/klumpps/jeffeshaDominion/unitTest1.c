/* -----------------------------------------------------------------------
 *Written by Shane Klumpp, unitTest for: gainCard
 
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
#define NOISY_TEST 0

int main(){
    int i;
    int returnValue;
    int seed = 1000;
    int numPlayer = 2;
    int totalTestFail = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    
    const char* CARDNames[] = {"curse", "estate" , "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
     "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
     "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

    printf ("TESTING gainCard()\n");
    
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    printf("Test 1 gainCard should return -1 if supplyCount is empty\n");
    
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    
    testG.handCount[0] = 0; //set handcount originally to 0
    testG.discardCount[0] = 0; //set discardCount to 0
    testG.deckCount[0] = 0; //set deckCount to 0
    
    //set supply count to 0 for all cards for testing
    for(i = 0; i < 27; i++){
        testG.supplyCount[i] = 0;
    }
    
    //test that if all cards supply position is 0 that the return value will be -1
    for(i = 0; i < 27; i++){
        returnValue = gainCard(i, &testG, 0, 0);
        if(returnValue == -1){
            assert(returnValue == -1); //I didn't want to have to print this out 26 times so I put print statement into noisy test
            assert(testG.handCount[0] == 0); //check hand pile for correct count of the cards added
            assert(testG.discardCount[0] == 0); //check discardCount is 0
            assert(testG.deckCount[0] == 0); //check deckCount is 0
            assert(testG.supplyCount[i] == 0); //check supply count for card. Make sure it is 0
            
            if(returnValue == -1){
                #if (NOISY_TEST == 1)
                printf("PASSED: returned -1 when supply was 0\n");
                #endif
            }
            else{
                printf("FAIL: didn't return -1 when supply was 0\n");
                totalTestFail++;
            }
            
        }
    }
    
    if(totalTestFail == 0){
        printf("All of test 1 conditions PASSED!\n");
    }
    else{
        printf("Something in test 1 FAILED\n");
    }
    
    //Now to check gainCard into discard deck, regular deck, or hand. Also need to check supply count for each
    
    printf("TEST 2: Gaincard takes from each supplyCount and adds to player hand then supplyCount is decremented\n");
    
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    
    //set supply count to 1 for all cards for testing
    for(i = 0; i < 27; i++){
        testG.supplyCount[i] = 1;
    }
    testG.handCount[0] = 0; //set handcount originally to 0
    testG.discardCount[0] = 0; //set discardCount to 0
    testG.deckCount[0] = 0; //set deckCount to 0
    testG.hand[0][0] = 3; //I put in the hand a random card from a 6 sided dice roll for testing purposes. Shoutout to xkcd
    
    for(i = 0; i < 27; i++){
        returnValue = gainCard(i, &testG, 2, 0);
        
        if(returnValue == 0){
            #if (NOISY_TEST == 1)
                printf("Handpile count: %d expected hand pile count %d\n", testG.handCount[0], i+1);
                printf("card = %d, expected card = %s\n", testG.hand[0][i], CARDNames[i]);
                printf("supply count for %s = %d, expected supply is: 0\n",CARDNames[i], testG.supplyCount[i]);
                printf("PASS\n");
            #endif
        }
        else{
            printf("FAIL\n");
            totalTestFail++;
        }
        
        assert(testG.discardCount[0] == 0); //assert discardCount wasn't changed
        assert(testG.deckCount[0] == 0); //assert deckCount wasn't changed
        
        assert(testG.handCount[0] == i + 1); //check hand pile for correct count of the cards added
        assert(testG.hand[0][i] == i); //check and pile for card.
        assert(testG.supplyCount[i] == 0); //check supply count for card. Make sure it has decremented to 0
        
    }
    
    if(totalTestFail == 0){
        printf("All of test 2 conditions PASSED!\n");
    }
    else{
        printf("Something in test 1 FAILED\n");
    }
    

    printf("TEST 3: Gaincard takes from each supplyCount and adds to discard deck then supplyCount is decremented\n");
    
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    
    //set supply count to 1 for all cards for testing
    for(i = 0; i < 27; i++){
        testG.supplyCount[i] = 1;
    }
    
    testG.handCount[0] = 0; //set handcount originally to 0
    testG.deckCount[0] = 0; //set deckCount to 0
    testG.discardCount[0] = 0; //set discardcount originally to 0
    testG.discard[0][0] = 3; //I put in the discard a random card from a 6 sided dice roll for testing purposes. Shoutout to xkcd
    
    for(i = 0; i < 27; i++){
        returnValue = gainCard(i, &testG, 0, 0);
        
        if(returnValue == 0){
            #if (NOISY_TEST == 1)
                printf("discard pile count: %d expected discard pile count %d\n", testG.discardCount[0], i+1);
                printf("card = %d, expected card = %s\n", testG.discard[0][i], CARDNames[i]);
                printf("supply count for %s = %d, expected supply is: 0\n",CARDNames[i], testG.supplyCount[i]);
                printf("PASS\n");
            #endif
        }
        else{
            printf("FAIL\n");
            totalTestFail++;
        }
        
        assert(testG.handCount[0] == 0); //assert handCount not changed
        assert(testG.deckCount[0] == 0); //assert deckCount not changed
        assert(testG.discardCount[0] == i + 1); //check hand pile for correct count of the cards added
        assert(testG.discard[0][i] == i); //check to make sure card was placed in the discard pile
        assert(testG.supplyCount[i] == 0); //check supply count for card. Make sure it has decremented to 0
        
    }
    if(totalTestFail == 0){
        printf("All of test 3 conditions PASSED!\n");
    }
    else{
        printf("Something in test 1 FAILED\n");
    }
    
    
    printf("TEST 4: Gaincard takes from each supplyCount and adds to player deck then supplyCount is decremented\n");
    
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    
    //set supply count to 1 for all cards for testing
    for(i = 0; i < 27; i++){
        testG.supplyCount[i] = 1;
    }
    
    testG.handCount[0] = 0; //set handcount originally to 0
    testG.discardCount[0] = 0; //set discardcount originally to 0
    testG.deckCount[0] = 0; //set discardcount originally to 0
    testG.deck[0][0] = 3; //I put in the discard a random card from a 6 sided dice roll for testing purposes. Shoutout to xkcd
    
    for(i = 0; i < 27; i++){
        returnValue = gainCard(i, &testG, 1, 0);
        
        if(returnValue == 0){
            #if (NOISY_TEST == 1)
                printf("deck pile count: %d expected deck pile count %d\n", testG.deckCount[0], i+1);
                printf("card = %d, expected card = %s\n", testG.deck[0][i], CARDNames[i]);
                printf("supply count for %s = %d, expected supply is: 0\n",CARDNames[i], testG.supplyCount[i]);
                printf("PASS\n");
            #endif
        }
        else{
            printf("FAIL\n");
            totalTestFail++;
        }
        
        assert(testG.handCount[0] == 0); //assert handCount not changed
        assert(testG.discardCount[0] == 0); //assert discardCount not changed
        assert(testG.deckCount[0] == i + 1); //check hand pile for correct count of the cards added
        assert(testG.deck[0][i] == i); //check to make sure card was placed in the discard pile
        assert(testG.supplyCount[i] == 0); //check supply count for card. Make sure it has decremented to 0
        
    }
    if(totalTestFail == 0){
        printf("All of test 4 conditions PASSED!\n");
    }
    else{
        printf("Something in test 1 FAILED\n");
    }
    
    
    
    
    if(totalTestFail == 0){
        printf("ALL TESTS PASSED!\n");
    }
    else{
        printf("THERE WERE %d FAILED TESTS\n",totalTestFail);
    }
    return 0;
}