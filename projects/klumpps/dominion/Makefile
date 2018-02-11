CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	
adventurer:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c -o randomtestadventurer -lm -g
    
runAdventurer: adventurer
	./randomtestadventurer | cat &> randomtestadventurer.out
	gcov dominion.c | cat >> randomtestadventurer.out
	cat dominion.c.gcov | cat >> randomtestadventurer.out
	
randomtestcard1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard1.c rngs.c -o randomtestcard1 -lm -g
    
runtestcard1: randomtestcard1
	./randomtestcard1 | cat &> randomtestcard1.out
	gcov dominion.c | cat >> randomtestcard1.out
	cat dominion.c.gcov | cat >> randomtestcard1.out


playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
unitTest1: unitTest1.c dominion.o rngs.o
	gcc -o unitTest1 -g  unitTest1.c dominion.o rngs.o $(CFLAGS)
	
unitTest2: unitTest2.c dominion.o rngs.o
	gcc -o unitTest2 -g  unitTest2.c dominion.o rngs.o $(CFLAGS)

unitTest3: unitTest3.c dominion.o rngs.o
	gcc -o unitTest3 -g  unitTest3.c dominion.o rngs.o $(CFLAGS)

unitTest4: unitTest4.c dominion.o rngs.o
	gcc -o unitTest4 -g  unitTest4.c dominion.o rngs.o $(CFLAGS)
	
cardTest1: cardTest1.c dominion.o rngs.o
	gcc -o cardTest1 -g  cardTest1.c dominion.o rngs.o $(CFLAGS)
	
cardTest2: cardTest2.c dominion.o rngs.o
	gcc -o cardTest2 -g  cardTest2.c dominion.o rngs.o $(CFLAGS)
	
cardTest3: cardTest3.c dominion.o rngs.o
	gcc -o cardTest3 -g  cardTest3.c dominion.o rngs.o $(CFLAGS)
	
cardTest4: cardTest4.c dominion.o rngs.o
	gcc -o cardTest4 -g  cardTest4.c dominion.o rngs.o $(CFLAGS)
	
unittestresults.out: playdom player cardTest1 cardTest2 cardTest3 cardTest4 unitTest1 unitTest2 unitTest3 unitTest4
	./cardTest1 > unittestresults.out
	./cardTest2 >> unittestresults.out
	./cardTest3 >> unittestresults.out
	./cardTest4 >> unittestresults.out
	./unitTest1 >> unittestresults.out
	./unitTest2 >> unittestresults.out
	./unitTest3 >> unittestresults.out
	./unitTest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unitTest2.exe unitTest3.exe unitTest2 unitTest3.exe unitTest3 unitTest1.exe unitTest1 unitTest4.exe unitTest4 cardTest1.exe cardTest1 cardTest2.exe cardTest2 cardTest3.exe cardTest3 cardTest4.exe cardTest4 randomtestadventurer randomtestcard1