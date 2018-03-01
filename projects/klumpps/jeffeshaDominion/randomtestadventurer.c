/*Shane Klumpp 2/10/2018 Running random test on card adventurer

Included in makeFile for running random tests

adventurer:
    gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtesetadventurer.c rngs.c -o randomtestadventurer -lm -g
    
runAdventurer: adventurer
	./randomtestadventurer | cat &> randomtestadventurer.out
	gcov dominion.c | cat >> randomtestadventurer.out
	cat dominion.c.gcov | cat >> randomtestadventurer.out

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
    
    int i, j, seed, playerCount, checkGame, player, currentHandCount;
    int testSuccessful = 0;
    int errorCount = 0;
    int iteration = 0;
	int k[10] = {curse,estate,duchy,province,copper,baron, smithy, treasure_map, minion, steward};
	srand(time(0));   
	struct gameState G;
    
    printf("Testing card adventurer using random testing\n");
    printf("Running 100 test with random test states on adventurer\n");
    
    for(i = 0; i< NUM_TESTS; i++){
        
        iteration++; //next iteration
        printf("Iteration count: %d\n", iteration);
        
        //set up pre states
        int discardTreasures = 0;
        int deckTreasures = 0;
        int preHandTreasures = 0;
        int postHandTreasures = 0;
        int postAdventurerDeckTreasures = 0, postAdventurerDiscardTreasures = 0;
        playerCount = rand() % 3 + 2; //generate random player count
        seed = rand() % 100 + 1; //seed randomly generated from 1 to 100
        
        checkGame = initializeGame(playerCount, k, seed, &G);
        
        if(checkGame == -1){
            printf("Problem initalizing game rerun\n");
            exit(0);
        }
        
        //set up states to test
        player = rand() % playerCount; //get player to run cards on within the playerCount randomly generated
        G.whoseTurn = player;
        G.numActions = 1;
        G.handCount[player] = rand() % 10 + 1; //player has handCount of random size between 1 and 10 so we can put adventurer in
        
        //used 50 because sometimes we want treasures to come from deck and sometimes from discard
        //We need at least 2 treasure cards from either the deck or discard to be drawn into the hand
        //(3/26) chance of treasure cards drawn randomly * 10-100 chances 2-11 treasure cards in either deck or discard or combination 
        G.deckCount[player] = rand() % 45 + 5; //make deck out of random amount between 0 and 50
        G.discardCount[player] = rand() % 45 + 5; //make discardCount random between 0 and 50
        
        //make random deck
        for(j = 0; j < G.deckCount[player]; j++){
            G.deck[player][j] = rand() % CARD_COUNT; //put random card between 0-26 into deck to draw from
            if(G.deck[player][j] == copper || G.deck[player][j] == silver || G.deck[player][j] == gold){ //if treasure card places in deck
                deckTreasures++; //add 1 to deckTreasures for later use
            }
        }
        
        //make random hand
        //saving 0 spot for adventurer so j starts at 1
        for(j = 1; j < G.handCount[player]; j++){
            G.hand[player][j] = rand() % CARD_COUNT; //put random card between 0-26 into hand to draw from
            if(G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold){
                preHandTreasures++; //add 1 to preHandTreasures
            }
        }
       
        //make random discard pile
        for(j = 0; j < G.discardCount[player]; j++){
            G.discard[player][j] = rand() % CARD_COUNT; //put random card between 0-26 into discard pile
            if(G.discard[player][j] == copper || G.discard[player][j] == silver || G.discard[player][j] == gold){
               discardTreasures++; //add 1 to discard Treasures
           }
        }
       
    

    //pre adventurer state calls
#if (NOISY_TEST == 1)
    printf("Pre adventurer states\n");
    printf("Treasure cards in deck %d out of %d deck cards\n", deckTreasures, G.deckCount[player]); 
    printf("Treasure cards in hand %d out of handCount %d\n", preHandTreasures, G.handCount[player]);
    printf("Treasure cards in discard %d out of %d discard cards\n", discardTreasures, G.discardCount[player]);
#endif
    
        G.hand[player][0] = adventurer; //put adventurer into 0 position of player
        currentHandCount = G.handCount[player];
        playCard(0, 0, 0, 0, &G); //play card 0 which corresponds to adventurer as set earlier
        

        if(currentHandCount + 2 != G.handCount[player]){
            printf("ERROR: Couldn't put 2 cards into players hand\n");
            printf("Treasure cards in deck %d treasure cards in discard %d\n", deckTreasures, discardTreasures);
        }
        
        //check post adventurer hand pile
        for(j = 0; j < G.handCount[player]; j++){
            if(G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold){
                postHandTreasures++; //iterate post hand treasures
            }
        }
        
        //check post adventurer deck pile
        for(j = 0; j < G.deckCount[player]; j++){
            if(G.deck[player][j] == copper || G.deck[player][j] == silver || G.deck[player][j] == gold){ //if treasure card places in deck
                postAdventurerDeckTreasures++; //add 1 to deckTreasures for later use
            }
        }
        

        //check post adventurer discard pile
        for(j = 0; j < G.discardCount[player]; j++){
            if(G.discard[player][j] == copper || G.discard[player][j] == silver || G.discard[player][j] == gold){
               postAdventurerDiscardTreasures++; //add 1 to discard Treasures
            }
        }
        
        
        
        
    //post adventurer play state calls
#if (NOISY_TEST == 1)
    printf("Post adventurer states\n");
    printf("Treasure cards in deck %d\n", postAdventurerDeckTreasures); 
    printf("Treasure cards in hand %d out of handCount %d\n", postHandTreasures, G.handCount[player]);
    printf("Treasure cards in discard %d\n", postAdventurerDiscardTreasures);
#endif
        
        printf("Pre adventurer hand treasures: %d Post adventurer hand treasures: %d\n", preHandTreasures, postHandTreasures);
        
        if(preHandTreasures + 2 != postHandTreasures){
            printf("ERROR: Wasn't able to put 2 treasure cards into players hand\n");
            errorCount++;
        }
        else{
            testSuccessful++;
        }
    

    
    
    
    printf("\n"); //just a new line call to make everything easier to read
    
    }//end for loop for testing iteration
    
    printf("There were %d ERRORS\n", errorCount);
    printf("There were %d successful tests where adventurer worked properly and added 2 treasure cards to the hand\n", testSuccessful);
    
    return 0;
}