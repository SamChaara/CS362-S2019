/**
 * Name: testCompare.h
 * Description: Helper functions that perform simple comparisons
 *  between gameState structures, for use with various unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef _TEST_COMPARE_H
#define _TEST_COMPARE_H

#ifndef PRINT_ON_SUCCESS
#define PRINT_ON_SUCCESS 1
#endif


/* Returns the minimum of two integer values */
int min(int a, int b);

/* Returns the maximum of two integer values */
int max(int a, int b);

/* Helper function that returns a string representation of a boolean value. */
char* boolToStr(bool value);


/**
 * Compares two boolean values for equality. If the two values are equal,
 * the function prints a passing message. If the two values are not equal,
 * the function prints a failing message.
 */
bool testEqualBool(char* fn, char* rule, int expected, int actual);

/**
 * Compares two boolean values for equality. If the two values are equal,
 * the function prints a failing message. If the two values are not equal,
 * the function prints a passing message.
 */
bool testNotEqualBool(char* fn, char* rule, int expected, int actual);

/**
 * Compares two integer values for equality. If the two values are equal,
 * the function prints a passing message. If the two values are not equal,
 * the function prints a failing message.
 */
bool testEqualToInt(char* fn, char* rule, int expected, int actual);

/**
 * Compares two integer values for equality. If the two values are equal,
 * the function prints a failing message. If the two values are not equal,
 * the function prints a passing message.
 */
bool testNotEqualToInt(char* fn, char* rule, int expected, int actual);

/**
 * Compares two integer values for inequality. Checks that the actual value
 * is greater than an expected value. If the actual value is greater than the
 * expected value, then a passing message is printed. If the actual value is
 * NOT greater than the expected value, then a failing message is printed.
 */
bool testGreaterThanInt(char* fn, char* rule, int expected, int actual);

/**
 * Compares two integer values for inequality. Checks that the actual value
 * is at least an expected value (AKA at minimum). If the actual value is at least 
 * as great as the expected value, then a passing message is printed. If the actual 
 * value is lesser than the expected value, then a failing message is printed.
 */
bool testAtLeastInt(char* fn, char* rule, int expected, int actual);

/**
 * Compares two integer values for inequality. Checks that the actual value
 * is lesser than an expected value. If the actual value is lesser than the
 * expected value, then a passing message is printed. If the actual value is
 * NOT lesser than the expected value, then a failing message is printed.
 */
bool testLesserThanInt(char* fn, char* rule, int expected, int actual);

/**
 * Compares two integer values for inequality. Checks that the actual value
 * is at most an expected value (AKA at maximum). If the actual value is at most 
 * as great as the expected value, then a passing message is printed. If the actual 
 * value is greater than the expected value, then a failing message is printed.
 */
bool testAtMostInt(char* fn, char* rule, int expected, int actual);

/**
 * Compares an integer value to an allowed range of values. If the actual value
 * is within the range (inclusive), then the function prints a success message.
 * Otherwise, the function prints a failure message.
 */
bool testInRangeInt(char* fn, char* rule, int rangeMin, int rangeMax, int actual);


#endif