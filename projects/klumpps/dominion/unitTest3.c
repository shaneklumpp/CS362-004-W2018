/* -----------------------------------------------------------------------
 *Written by Shane Klumpp, unitTest for: getCost
 
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unitTest3: unitTest3.c dominion.o rngs.o
 *      gcc -o unitTest3 -g  unitTest3.c dominion.o rngs.o $(CFLAGS)
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
    int seed = 1000;
    int numPlayers = 2;
    int enumHolder;
    int returnValue;
    //int bugCount = 0;
    int totalTestFail = 0; //set to false originally. If anything triggers a switch to 1 we know at least one test failed
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    
    //CARDNames enum array for string printing ease
    const char* CARDNames[] = {"curse", "estate" , "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
     "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
     "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    
    // initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    
    printf("TESTING getCost():\n");
    
#if (NOISY_TEST == 1)
    printf("Testing from range: -1 through 27. This will test every card against its return value and two\n out of bounds cases with passed values of -1 and -27\n");
#endif
    //copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState)); //copying into test case gamestate testG
    for(enumHolder = -1; enumHolder <= 27; enumHolder++){
        returnValue = getCost(enumHolder);
        
        //printf("Checking enumHolder: %d value returned: %d\n", enumHolder, returnValue);
        //printf("Card checked:%s value returned %d\n", CARDNames[enumHolder], returnValue);

        switch (returnValue){
            case -1:
                if(enumHolder >= 0 && enumHolder < 27){ //Check if enumHolder tested was inside range 0-26
                    printf("FAIL: enumHolder %d inside range that should have returned a value not -1\n", enumHolder);
                    totalTestFail++;
                }
                else{
                    printf("PASS: enumHolder %d was outside enum range and correctly returned -1\n", enumHolder);
                }
                break;
                
            case 0:
                if(enumHolder == 0 || enumHolder == 4){
                    printf("PASS: Card checked: %s CORRECTLY, returned value: %d\n", CARDNames[enumHolder], returnValue);
                }
                else{
                    printf("Wrong return value: FAIL\n");
                    totalTestFail++;
                }
                break;
                
            //no case 1
            case 2:
                if(enumHolder == 1 || enumHolder == 22){
                    printf("PASS: Card checked: %s CORRECTLY, returned value: %d\n", CARDNames[enumHolder], returnValue);
                }
                else{
                    printf("Wrong return value: FAIL\n");
                    totalTestFail++;
                }
                break;
            
            case 3:
                if(enumHolder == 5 || enumHolder == 14 || enumHolder == 16 || enumHolder == 18 || enumHolder == 20){
                    printf("PASS: Card checked: %s CORRECTLY, returned value: %d\n", CARDNames[enumHolder], returnValue);
                }
                else{
                    printf("Wrong return value: FAIL\n");
                    totalTestFail++;
                }
                break;
                
            case 4:
                if(enumHolder == 9 || enumHolder == 10 || enumHolder == 12 || enumHolder == 13 || enumHolder == 15 || enumHolder == 21
                    || enumHolder == 24 || enumHolder == 25 || enumHolder == 26){
                    printf("PASS: Card checked: %s CORRECTLY, returned value: %d\n", CARDNames[enumHolder], returnValue);
                }
                else{
                    printf("Wrong return value: FAIL\n");
                    totalTestFail++;
                }
                break;
                
            case 5:
                if(enumHolder == 2 || enumHolder == 8 || enumHolder == 11 || enumHolder == 17 || enumHolder == 19 || enumHolder == 23){
                    printf("PASS: Card checked: %s CORRECTLY, returned value: %d\n", CARDNames[enumHolder], returnValue);
                }
                else{
                    printf("Wrong return value: FAIL\n");
                    totalTestFail++;
                }
                break;
                
            case 6:
                if(enumHolder == 6 || enumHolder == 7){
                    printf("PASS: Card checked: %s CORRECTLY, returned value: %d\n", CARDNames[enumHolder], returnValue);
                }
                else{
                    printf("Wrong return value: FAIL\n");
                    totalTestFail++;
                }
                break;
            
            //no case 7
            case 8:
                if(enumHolder == 3){
                    printf("PASS: Card checked: %s CORRECTLY, returned value: %d\n", CARDNames[enumHolder], returnValue);
                }
                else{
                    printf("Wrong return value: FAIL\n");
                    totalTestFail++;
                }
                break;
        }
    }
    
    if(totalTestFail == 0){
        printf("ALL TESTS PASS!\n");
    }
    else{
        printf("TESTS FAILED: %d\n", totalTestFail);
    }
    
    return 0;
}

/*
Code I might need to reference so I'll keep here

switch( cardNumber ) 
    {
    case curse:
      return 0;
    case estate:
      return 2;
    case duchy:
      return 5;
    case province:
      return 8;
    case copper:
      return 0;
    case silver:
      return 3;
    case gold:
      return 6;
    case adventurer:
      return 6;
    case council_room:
      return 5;
    case feast:
      return 4;
    case gardens:
      return 4;
    case mine:
      return 5;
    case remodel:
      return 4;
    case smithy:
      return 4;
    case village:
      return 3;
    case baron:
      return 4;
    case great_hall:
      return 3;
    case minion:
      return 5;
    case steward:
      return 3;
    case tribute:
      return 5;
    case ambassador:
      return 3;
    case cutpurse:
      return 4;
    case embargo: 
      return 2;
    case outpost:
      return 5;
    case salvager:
      return 4;
    case sea_hag:
      return 4;
    case treasure_map:
      return 4;
    }

enum CARD
  {curse = 0, value 0
   estate, 1 value 2
   duchy, 2 value 5
   province, 3 value8

   copper, 4
   silver, 5
   gold, 6

   adventurer, 7
                    // If no/only 1 treasure found, stop when full deck seen 
   council_room, 8
   feast,                       //choice1 is supply # of card gained)
   gardens, 9
   mine, 10             // choice1 is hand# of money to trash, choice2 is supply# of
	                                //money to put in hand 
   remodel, 11                                              // choice1 is hand# of card to remodel, choice2 is supply#
   smithy, 12
   village, 13

   baron, 14                      //choice1: boolean for discard of estate 
                                  //       Discard is always of first (lowest index) estate 
   great_hall, 15
   minion, 16                    // choice1:  1 = +2 coin, 2 = redraw 
   steward, 17               // choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) 
   tribute, 18

   ambassador, 19               // choice1 = hand#, choice2 = number to return to supply /
   cutpurse, 20
   embargo, 21              // choice1 = supply# /
   outpost, 22
   salvager, 23                  // choice1 = hand# to trash /
   sea_hag, 24
   treasure_map 25
  };



*/