/*Shane Klumpp 2/10/2018 Running random test on card smithy

Included in makeFile for running random tests

randomtestcard2:
    gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard2.c rngs.c -o randomtestcard2 -lm -g
    
runtestcard2: randomtestcard2
	./randomtestcard2 | cat &> randomtestcard2.out
	gcov dominion.c | cat >> randomtestcard2.out
	cat dominion.c.gcov | cat >> randomtestcard2.out

*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#define NUM_TESTS 100
#define CARD_COUNT treasure_map

#define NOISY_TEST 0

int main(){
    int i, j, seed, playerCount, checkGame, player;
    int testSuccessful = 0;
    int errorCount = 0;
    int iteration = 0;
	int k[10] = {curse,estate,duchy,province,copper,baron, smithy, treasure_map, minion, steward};
	
	const char* CARDNames[] = {"curse", "estate" , "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
     "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
     "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	
	srand(time(0));   
	struct gameState G;
    
    printf("Testing card smithy using random testing\n");
    printf("Running 100 random tests with random test states on village\n");
    
    for(i = 0; i < NUM_TESTS; i++){
        
        iteration++; //next iteration
        printf("Iteration count: %d\n", iteration);
        
        //gameState set up
        playerCount = rand() % 3 + 2; //generate random player count
        seed = rand() % 100 + 1; //seed randomly generated from 1 to 100
        
        checkGame = initializeGame(playerCount, k, seed, &G);
        
        if(checkGame == -1){
            printf("Problem initalizing game rerun\n");
            exit(0);
        }
        
        //state set up
        player = rand() % playerCount; //get player to run cards on within the playerCount randomly generated
        G.whoseTurn = player;
        G.playedCardCount = 0;
        G.numActions = 1; 
        G.handCount[player] = rand() % 4 + 1; //player has handCount of random size between 1 and 5 so we can put adventurer in
        G.deckCount[player] = rand() % 8 + 4; //make deck with at least 4 cards 
        int preSmithyHandCount = 0;
        int preSmithyDeckCount = 0;
        int preSmithyPlayedCardCount = 0;
        int preSmithyNumActions = G.numActions;
        
        //make random hand for the sake of testing leaving 0 spot for village
        for(j = 1; j < G.handCount[player]; j++){
            G.hand[player][j] = rand() % CARD_COUNT; //put random card between 0-26 into hand
            preSmithyHandCount++;
        }
        preSmithyHandCount++; //account for manually adding in village card to hand
        //make random deck for sake of testing
        for(j = 0; j < G.deckCount[player]; j++){
            G.deck[player][j] = rand() % CARD_COUNT; //put random card between 0-26 into deck to draw from
            preSmithyDeckCount++;
        }
        
#if (NOISY_TEST == 1)
      printf("Pre smithy play handcount %d\n", preSmithyHandCount);
      printf("Pre smithy play deckcount %d\n", preSmithyDeckCount);
      printf("Pre smithy play playedCardCount %d\n", G.playedCardCount);
#endif        
        
        G.hand[player][0] = smithy; //put adventurer into 0 position of player
        printf("Pre village play hand: ");
        for(j = 0; j <G.handCount[player]; j++){
               printf("%s ",CARDNames[G.hand[player][j]]);
        }
        printf("\n");
        
        playCard(0, 0, 0, 0, &G); //play card 0 which corresponds to smithy as set earlier
        
#if (NOISY_TEST == 1)
      printf("Post smithy play handcount %d\n", G.handCount[player]);
      printf("Post smithy play deckcount %d\n", G.deckCount[player]);
      printf("Post smithy play playedCardCount %d\n", G.playedCardCount);
#endif            
        
        printf("Post smithy play hand: ");
        for(j = 0; j <G.handCount[player]; j++){
               printf("%s ",CARDNames[G.hand[player][j]]);
        }
        printf("\n");
        
        //testing 
        if(G.handCount[player] != preSmithyHandCount + 3 - 1){ //+3 draws minus a played card
            printf("ERROR: Handcount didn't increase by 2, either drew too many cards or didn't discard check NOISY_TEST\n");
            errorCount++;
        }
        else if(G.deckCount[player] != preSmithyDeckCount - 3){//-3 cards that were drawn
            printf("ERROR: Deckcount didn't decrease by 3, something went wrong check NOISY_TEST\n");
            errorCount++;
        }
        else if(G.playedCardCount != preSmithyPlayedCardCount + 1){ //+1 to played card count
            printf("ERROR: playedCardCount didn't increase by 1 check NOISY_TEST\n");
            errorCount++;
        }
        else if(G.numActions != preSmithyNumActions - 1){
            printf("ERROR: num actions didn't decrease 1 by check NOISY_TEST\n");
            errorCount++;
        }
        else{
            printf("Test successful!\n");
            testSuccessful++;
        }
        
        
        printf("\n");
    }//end for loop for testing
    
    printf("There were %d ERRORS\n", errorCount);
    printf("There were %d successful tests where village worked properly\n", testSuccessful);
    
    
    
    return 0;
}