CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

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

#########


randomtestresults: dominion.c randomtestcard1.c randomtestcard2.c randomtestcardadventurer.c randomHelpers.c printHelpers.c testHelpers.c testCompare.c
	make clean

	# 
	# random tests
	# 
	echo "*****  RANDOM TESTS  ***** " > randomtestresults.out
	echo "\n*\tNOTE: A lot of test cases are printed here. In order to show only the" >> randomtestresults.out
	echo "*\tfailing tests, change the value of the PRINT_ON_SUCCESS variable in the" >> randomtestresults.out
	echo "*\ttestCompare.h file from 1 to 0.\n" >> randomtestresults.out

	# random test card 1
	echo "\n--- randomtestcard1.c ---" >> randomtestresults.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.c randomHelpers.c printHelpers.c testHelpers.c testCompare.c $(CFLAGS)
	./randomtestcard1 >> randomtestresults.out
	echo "" >> randomtestresults.out
	gcov -nb dominion.c >> randomtestresults.out

	# random test card 2
	echo "\n--- randomtestcard2.c ---" >> randomtestresults.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.c randomHelpers.c printHelpers.c testHelpers.c testCompare.c $(CFLAGS)
	./randomtestcard2 >> randomtestresults.out
	echo "" >> randomtestresults.out
	gcov -nb dominion.c >> randomtestresults.out

	# random test card adventurer
	echo "\n--- randomtestcardadventurer.c ---" >> randomtestresults.out
	gcc -o randomtestcardadventurer -g randomtestcardadventurer.c dominion.c rngs.c randomHelpers.c printHelpers.c testHelpers.c testCompare.c $(CFLAGS)
	./randomtestcardadventurer >> randomtestresults.out
	echo "" >> randomtestresults.out
	gcov -nb dominion.c >> randomtestresults.out

	# detailed random test card gcov results
	echo "\n\n*****  COVERAGE DETAILS  *****\n" >> randomtestresults.out
	gcov dominion.c -fb >> randomtestresults.out



#########

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 


#########

clean:
	rm -f *.o playdom.exe playdom player player.exe testDrawCard testDrawCard.exe
	rm -f *.gcov *.gcda *.gcno *.so *.out *.info
	rm -f randomtestcard1 randomtestcard2 randomtestcardadventurer
	rm -rf *.dSYM
