/*Shane Klumpp 2/10/2018 Running random test on card village

Included in makeFile for running random tests

randomtestcard1:
    gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard1.c rngs.c -o randomtestcard1 -lm -g
    
runtestcard1: randomtestcard1
	./randomtestcard1 | cat &> randomtestcard1.out
	gcov dominion.c | cat >> randomtestcard1.out
	cat dominion.c.gcov | cat >> randomtestcard1.out

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
    int preVillageHandCount, preVillageDeckCount, preVillagePlayedCardCount, preVillageNumActions;
    int testSuccessful = 0;
    int errorCount = 0;
    int iteration = 0;
	int k[10] = {curse,estate,duchy,province,copper,baron, smithy, treasure_map, minion, steward};
	
	const char* CARDNames[] = {"curse", "estate" , "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
     "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
     "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	
	srand(time(0));   
	struct gameState G;
    
    printf("Testing card village using random testing\n");
    printf("Running 100 test with random test states on village\n");
    
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
        G.numActions = rand() % 4 + 1; //random number of num actions between 1-5
        G.handCount[player] = rand() % 4 + 1; //player has handCount of random size between 1 and 5 so we can put adventurer in
        G.deckCount[player] = rand() % 8 + 2; //make deck with at least 2 cards 
        preVillageHandCount = 0;
        preVillageDeckCount = 0;
        preVillagePlayedCardCount = 0;
        preVillageNumActions = G.numActions;
        
        //make random hand for the sake of testing leaving 0 spot for village
        for(j = 1; j < G.handCount[player]; j++){
            G.hand[player][j] = rand() % CARD_COUNT; //put random card between 0-26 into hand
            preVillageHandCount++;
        }
        preVillageHandCount++; //account for manually adding in village card to hand
        //make random deck for sake of testing
        for(j = 0; j < G.deckCount[player]; j++){
            G.deck[player][j] = rand() % CARD_COUNT; //put random card between 0-26 into deck to draw from
            preVillageDeckCount++;
        }
        
#if (NOISY_TEST == 1)
      printf("Pre village play handcount %d\n", preVillageHandCount);
      printf("Pre village play deckcount %d\n", preVillageDeckCount);
      printf("Pre Village num actions %d\n", G.numActions);
      printf("Pre Village play playedCardCount %d\n", G.playedCardCount);
#endif

        G.hand[player][0] = village; //put adventurer into 0 position of player
        printf("Pre village play hand: ");
        for(j = 0; j <G.handCount[player]; j++){
               printf("%s ",CARDNames[G.hand[player][j]]);
        }
        printf("\n");
        

        playCard(0, 0, 0, 0, &G); //play card 0 which corresponds to adventurer as set earlier
        
#if (NOISY_TEST == 1)
      printf("Post village play handcount %d\n", G.handCount[player]);
      printf("Post village play deckcount %d\n", G.deckCount[player]);
      printf("Post Village num actions %d\n", G.numActions);
      printf("Post Village play playedCardCount %d\n", G.playedCardCount);
      printf("Post Village play playedCard %s\n", CARDNames[G.playedCards[0]]);
#endif
        
        printf("Post village play hand: ");
        for(j = 0; j <G.handCount[player]; j++){
               printf("%s ",CARDNames[G.hand[player][j]]);
        }
        printf("\n");
        
        //testing 
        if(G.handCount[player] != preVillageHandCount && (G.deckCount[player] != preVillageDeckCount - 1) 
        && G.playedCardCount != preVillagePlayedCardCount + 1 && G.numActions == preVillageNumActions + 1){
            printf("ERROR: gameState altered in unexpected way check NOISY_TEST\n");
            errorCount++;
        }
        else{
            testSuccessful++;
        }
        
        
        
        printf("\n"); //new line statement for easier reading between iterations
    }//end for loop testing
    
    
    printf("There were %d ERRORS\n", errorCount);
    printf("There were %d successful tests where village worked properly\n", testSuccessful);
    
    
    
    return 0;
}