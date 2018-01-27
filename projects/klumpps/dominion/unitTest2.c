/* -----------------------------------------------------------------------
 *Written by Shane Klumpp, unitTest for: isGameOver
 
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unitTest2: unitTest2.c dominion.o rngs.o
 *      gcc -o unitTest2 -g  unitTest2.c dominion.o rngs.o $(CFLAGS)
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

int main() {
    //standard starting material needed for a game
    int i, j; //counters
    int seed = 1000;
    int numPlayers = 2;
    int testResult;
    int bugCount = 0;
    int totalTestFail = 0; //set to false originally. If anything triggers a switch to 1 we know at least one test failed
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    
    printf("Testing isGameOver():");
    
#if (NOISY_TEST == 1)
    printf("Testing gamestate with province = 0\n");
#endif
    //copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    testG.supplyCount[province] = 0;
    testResult = isGameOver(&testG);
    if(testResult == 1){
        printf("TESTING WITH GAMESTATE PROVINCE = 0: PASS\n");
    }
    else{
        printf("TESTING WITH GAMESTATE PROVINCE = 0: FAIL\n");
    }
 
#if (NOISY_TEST == 1)
    printf("TESTING WITH GAMESTATE PROVINCE > 0 from 1-12 IN THE FOLLOWING TESTS: \n");
#endif

	//cycle through province values of 1-12
	for(i = 1; i <= 12; i++){
	    // copy the game state to a test case
	    memcpy(&testG, &G, sizeof(struct gameState));
	    
	    testG.supplyCount[province] = i;
        testResult = isGameOver(&testG);
        
        //game is not over so testResult should pass back 0. Test result will pass back 1 if the game is over
        if(testResult == 0){
        printf("TESTING WITH GAMESTATE PROVINCE WITH VALUE %d: PASS\n", i);
        }
        else{
            printf("TESTING WITH GAMESTATE PROVINCE WITH VALUE %d: FAIL\n", i);
            totalTestFail++;
        }
	}
    
#if (NOISY_TEST == 1)
    printf("TESTING WITH GAMESTATE PROVINCE = -1: \n");
#endif    
    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
    
    testG.supplyCount[province] = -1;
    testResult = isGameOver(&testG);
    
    if(testResult == 0){
        printf("BUG: isGameOver doesn't check for < 0 values in province\n");
        bugCount++;
    }
    else{
        printf("TEST PASSED isGameOver CHECKS FOR NEGATIVE VALUES OF PROVINCE\n");
    }
    
#if (NOISY_TEST == 1)
    printf("TESTING WITH GAMESTATE SUPPLYCOUNT = 0 FOR ALL CARDS, OR FOR 1 CARD = 0, 2 CARDS = 0, 3 CARDS =0, 4 CARDS = 0, 5 CARDS = 0: \n");
#endif   
    int supplyCards;
    for(j = 0; j <= 5; j++){ //j = 0, 1, 2 cards that should have no cards in them = 0 count. j = 3 means 3 cards should be empty and should end the game
        supplyCards = 25;
        // copy the game state to a test case
	    memcpy(&testG, &G, sizeof(struct gameState)); 
	    
        for(i = 0; i < 25; i++){
            testG.supplyCount[i] = 5; //set to value above 0;
            if(i > supplyCards-j-1){ //if i is above supplyCards = 25 - j (0, 1, or 2) maketestG.supplyCount[i] = 0 to simulate empty card
                testG.supplyCount[i] = 0;
            }
        }
        
        testResult = isGameOver(&testG);
        
        if(j < 3){
            //game is not over so testResult should pass back 0. Test result will pass back 1 if the game is over
            if(testResult == 0){
                printf("TESTING WITH GAMESTATE SUPPLYCOUNT > 0 FOR %d cards, %d cards with 0 supply: PASS\n", supplyCards-j, j);
            }
            else{
                printf("TESTING WITH GAMESTATE SUPPLYCOUNT > 0 FOR %d cards, %d cards with 0 supply FAIL\n", supplyCards-j, j);
                totalTestFail++;
            }
        }
        else{ //j = 3 so the game should end and testResult should == 1
            if(testResult == 1){
                printf("TESTING WITH GAMESTATE SUPPLYCOUNT > 0 FOR %d cards, %d cards with 0 supply. Game ended: PASS\n", supplyCards-j, j);
            }
            else{
                printf("TESTING WITH GAMESTATE SUPPLYCOUNT > 0 FOR %d cards, %d cards with 0 supply. Game did not end: FAIL\n", supplyCards-j, j);
                totalTestFail++;
            }
        }
        
    }
    
#if (NOISY_TEST == 1)
    printf("TESTING WITH GAMESTATE SUPPLYCOUNT = -1 FOR ALL CARDS \n");
#endif    
    supplyCards = 25;
    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState)); 
	    
    for(i = 0; i < 25; i++){
        testG.supplyCount[i] = -1; //set to -1;
    }
    
    testResult = isGameOver(&testG);
    
    if(testResult == 1){
        printf("TESTING WITH GAMESTATE SUPPLYCOUNT = -1 FOR ALL CARDS Game ended: PASS\n");
    }
    else{
        printf("BUG: TESTING WITH GAMESTATE SUPPLYCOUNT = -1 FOR ALL CARDS Game didn't end: BUG!\n");
        bugCount++;
    }
    
    
    if(totalTestFail == 0){
        printf("ALL TESTS PASSED!\n");
        if(bugCount == 0){
            printf("NO BUGS FOUND!");
        }
        else{
            printf("THERE WAS %d BUG(s) FOUND\n", bugCount);
        }
    }
    else{
        printf("THERE WAS %d TEST(s) THAT FAILED\n", totalTestFail);
        printf("THERE WAS %d BUG(s) FOUND\n", bugCount);
    }
 
    return 0;   
}