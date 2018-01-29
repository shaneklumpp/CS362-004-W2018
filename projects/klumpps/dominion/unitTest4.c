/* -----------------------------------------------------------------------
 *Written by Shane Klumpp, unitTest for: updateCoins
 
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unitTest4: unitTest4.c dominion.o rngs.o
 *      gcc -o unitTest4 -g  unitTest4.c dominion.o rngs.o $(CFLAGS)
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
    int i, p, r;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int handCounter;
    int bonus;
    int testCase;
    int cardArray[5];
    srand(time(0)); //used in test 2 and 3
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int maxHandCount = 10;
    //for printing card names for testing
    const char* CARDNames[] = {"curse", "estate" , "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
     "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
     "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++) //copper, silver, gold arrays filled with each card
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    
    printf("TESTING updateCoins()\n");
    
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    printf("Test 1: Checking either an empty hand or range of hand from 1-10 with all coppers, silvers, and all bonuses 0-10\n");
    printf("This is the base case of testing: Just testing the treasure cards and bonuses to assure they work correctly!\n");
    
    for(p = 0; p < numPlayer; p++){ //for max players of 2 check all handcounts
    
        for(handCounter = 0; handCounter <= maxHandCount; handCounter++){ //for handcount of 0 to handcount of 10
        
            for(bonus = 0; bonus <= maxBonus; bonus++){ //for bonus of 0 from 10
            
#if (NOISY_TEST == 1)
                printf("Testing player %d with %d treasure cards (copper/silver/gold) and %d bonus\n", p, handCounter, bonus);
#endif
                memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
                testG.handCount[p] = handCounter;
                memcpy(testG.hand[p], coppers, sizeof(int) * handCounter); //fill hand with coppers to check copper cases
                updateCoins(p, &testG, bonus); //testing updateCoins for coppers
#if (NOISY_TEST == 1)
                printf("testG.coins = %d, expected = %d\n", testG.coins, handCounter * 1 + bonus);
#endif
                assert(testG.coins == handCounter * 1 + bonus); //assert coppers work correctly
                memcpy(testG.hand[p], silvers, sizeof(int) * handCounter);
                updateCoins(p, &testG, bonus);
                
#if (NOISY_TEST == 1)
                printf("testG.coins = %d, expected = %d\n", testG.coins, handCounter * 2 + bonus);
#endif               
                assert(testG.coins == handCounter * 2 + bonus); //assert silver works correctly with bonuses
                memcpy(testG.hand[p], golds, sizeof(int) * handCounter); //set all the cards to gold to test last base case
                
                updateCoins(p, &testG, bonus);
                
#if (NOISY_TEST == 1)
                printf("testG.coins = %d, expected = %d\n", testG.coins, handCounter * 3 + bonus);
#endif 
                assert(testG.coins == handCounter * 3 + bonus); //testing for all golds and all bonuses base case
                
                
            }
        }
    }
    
    printf("ALL TEST 1 CONDITIONS PASSED!\n");
    printf("TEST2: Now testing updateCoins with a random mix of cards that includes some treasure and non-treasure cards!\n");
    printf("TEST2: 5 card hand passed to updateCoins over multiple times. This has some random testing to get random cards\n");
    
    int expectedCoins = 0;
    handCounter = 5;

    for(p = 0; p < numPlayer; p++){ //for max players of 2 check all handcounts
    
        for(testCase = 1; testCase <= 100; testCase++){ //for tests 1-100
        
            for(bonus = 0; bonus <= 3; bonus++){ //for bonus of 0 from 3 because we know bonus is going to work from the previous unit test
                expectedCoins = 0;
                
                for(i = 0; i < 5; i++){
                    r = rand() % (26 + 1);
                    cardArray[i] = r;
                    if(r == 4){ //if r = copper add value 1
                        expectedCoins = expectedCoins + 1;
                    }
                    else if(r == 5){ //if r = silver add value 2
                        expectedCoins = expectedCoins + 2;
                    }
                    else if(r == 6){ //if r = gold add value 3
                        expectedCoins = expectedCoins + 3;
                    }
                }
                
                memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
                testG.handCount[p] = handCounter; //set testG.handCount[p] of player to handCounter which is 5 cards
                memcpy(testG.hand[p], cardArray, sizeof(int) * handCounter); //fill hand with cardArray
            
                updateCoins(p, &testG, bonus); //testing updateCoins for random hand in card Array
#if (NOISY_TEST == 1)
                printf("Cards testing:");
                for(i = 0; i < 5; i++){
                    printf(" %s ",CARDNames[cardArray[i]]); //should print whats in CARDNAMES
                }
                printf("\n"); //new line
                printf("testG.coins = %d, expected = %d\n", testG.coins, expectedCoins + bonus); //print testG coins and expected coins
#endif
            
                assert(testG.coins == expectedCoins + bonus); //assertion for testing
            }
        }
    }
    printf("TEST 2 PASSED: updateCoins works correctly with treasure and non-treasure card hands\n");
    
    printf("TEST 3: testing updateCoins with only non-treasure cards. Coins should only come from bonus!\n");
    handCounter = 5;
    
    for(p = 0; p < numPlayer; p++){ //for max players of 2 check all handcounts
    
        for(testCase = 1; testCase <= 5; testCase++){ //for tests 1-100
        
            for(bonus = 0; bonus <= 3; bonus++){ //for bonus of 0 from 3 because we know bonus is going to work from the previous unit test
                
                for(i = 0; i < 5; i++){
                    r = rand() % (26 + 1);
                    cardArray[i] = r;
                    if(r == 4){ //copper enum number
                        i--; //if copper was added subtract 1 from i to reroll
                    }
                    else if(r == 5){ //silver enum number
                        i--; //silver added subtract 1 from i to reroll
                    }
                    else if(r == 6){ //if gold enum number
                        i--; //gold added subtract 1 from i to reroll
                    }
                }
                
                memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
                testG.handCount[p] = handCounter; //set testG.handCount[p] of player to handCounter which is 5 cards
                memcpy(testG.hand[p], cardArray, sizeof(int) * handCounter); //fill hand with cardArray
            
                updateCoins(p, &testG, bonus); //testing updateCoins for random hand without treasure cards in card Array
#if (NOISY_TEST == 1)
                printf("Cards testing:");
                for(i = 0; i < 5; i++){
                    printf(" %s ",CARDNames[cardArray[i]]); //should print whats in CARDNAMES
                }
                printf("\n"); //new line
                printf("testG.coins = %d, expected = %d\n", testG.coins, bonus); //print testG coins and expected coins from bonus
#endif
            
                assert(testG.coins == bonus); //assertion for testing
            }
        }
    }
    
    printf("TEST 3 PASSED: updateCoins works without any treasure cards and only non-treasure cards\n");
    
    printf("All TESTS PASSED!\n");
    
    
    return 0;
}