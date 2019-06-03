/**
 * Name: testCompare.c
 * Description: Helper functions that perform simple comparisons
 *  between gameState structures, for use with various unit tests.
 */

#include "testCompare.h"
#include "printHelpers.h"



/**
 * Returns the minimum of two integer values
 * 
 * @param a - an integer value to compare
 * @param b - an integer value to compare
 * @returns the minimum of the two values
 */
int min(int a, int b) {
  return a < b ? a : b;
}

/**
 * Returns the maximum of two integer values
 * 
 * @param a - an integer value to compare
 * @param b - an integer value to compare
 * @returns the maximum of the two values
 */
int max(int a, int b) {
  return a > b ? a : b;
}


/**
 * Helper function that returns a string representation
 * of a boolean value.
 * 
 * @param value - a boolean value
 * @returns the string representation of the boolean.
 */
char* boolToStr(bool value) {
  return value ? "true" : "false";
}


/**
 * Compares two boolean values for equality. If the two values are equal,
 * the function prints a success message. If the two values are not equal,
 * the function prints a failure message.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected boolean value
 * @param actual - the actual boolean value
 * @returns bool - true if the test passed, false if not
 */
bool testEqualBool(char* fn, char* rule, int expected, int actual) {
  if (expected == actual) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: %s, ACTUAL: %s)\n", fn, rule, boolToStr(expected) , boolToStr(actual));
    return false;
  }
}


/**
 * Compares two boolean values for equality. If the two values are equal,
 * the function prints a failure message. If the two values are not equal,
 * the function prints a success message.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected boolean value
 * @param actual - the actual boolean value 
 * @returns bool - true if the test passed, false if not
 */
bool testNotEqualBool(char* fn, char* rule, int expected, int actual) {
  if (expected != actual) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: %s, ACTUAL: %s)\n", fn, rule, boolToStr(!expected) , boolToStr(actual));
    return false;
  }
}


/**
 * Compares two integer values for equality. If the two values are equal,
 * the function prints a success message. If the two values are not equal,
 * the function prints a failure message.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected integer value
 * @param actual - the actual integer value
 * @returns bool - true if the test passed, false if not
 */
bool testEqualToInt(char* fn, char* rule, int expected, int actual) {
  if (expected == actual) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: %d, ACTUAL: %d)\n", fn, rule, expected, actual);
    return false;
  }
}


/**
 * Compares two integer values for equality. If the two values are equal,
 * the function prints a failure message. If the two values are not equal,
 * the function prints a success message.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected integer value
 * @param actual - the actual integer value
 * @returns bool - true if the test passed, false if not
 */
bool testNotEqualToInt(char* fn, char* rule, int expected, int actual) {
  if (expected != actual) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: !%d, ACTUAL: %d)\n", fn, rule, expected, actual);
    return false;
  }
}


/**
 * Compares two integer values for inequality. Checks that the actual value
 * is greater than an expected value. If the actual value is greater than the
 * expected value, then a success message is printed. If the actual value is
 * NOT greater than the expected value, then a failure message is printed.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected integer value
 * @param actual - the actual integer value 
 * @returns bool - true if the test passed, false if not
 */
bool testGreaterThanInt(char* fn, char* rule, int expected, int actual) {
  if (actual > expected) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: >%d, ACTUAL: %d)\n", fn, rule, expected, actual);
    return false;
  }
}


/**
 * Compares two integer values for inequality. Checks that the actual value
 * is at least an expected value (AKA at minimum). If the actual value is at least 
 * as great as the expected value, then a success message is printed. If the actual 
 * value is lesser than the expected value, then a failure message is printed.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected integer value
 * @param actual - the actual integer value 
 * @returns bool - true if the test passed, false if not
 */
bool testAtLeastInt(char* fn, char* rule, int expected, int actual) {
  if (actual >= expected) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: >%d, ACTUAL: %d)\n", fn, rule, expected, actual);
    return false;
  }
}


/**
 * Compares two integer values for inequality. Checks that the actual value
 * is lesser than an expected value. If the actual value is lesser than the
 * expected value, then a success message is printed. If the actual value is
 * NOT lesser than the expected value, then a failure message is printed.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected integer value
 * @param actual - the actual integer value 
 * @returns bool - true if the test passed, false if not
 */
bool testLesserThanInt(char* fn, char* rule, int expected, int actual) {
  if (actual < expected) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: <%d, ACTUAL: %d)\n", fn, rule, expected, actual);
    return false;
  }
}


/**
 * Compares two integer values for inequality. Checks that the actual value
 * is at most an expected value (AKA at maximum). If the actual value is at most 
 * as great as the expected value, then a success message is printed. If the actual 
 * value is greater than the expected value, then a failure message is printed.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected integer value
 * @param actual - the actual integer value 
 * @returns bool - true if the test passed, false if not
 */
bool testAtMostInt(char* fn, char* rule, int expected, int actual) {
  if (actual <= expected) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: >%d, ACTUAL: %d)\n", fn, rule, expected, actual);
    return false;
  }
}


/**
 * Compares an integer value to an allowed range of values. If the actual value
 * is within the range (inclusive), then the function prints a success message.
 * Otherwise, the function prints a failure message.
 * 
 * @param fn - the name of the function being tested
 * @param rule - the specific rule being tested
 * @param expected - the expected integer value
 * @param actual - the actual integer value 
 * @returns bool - true if the test passed, false if not
 */
bool testInRangeInt(char* fn, char* rule, int rangeMin, int rangeMax, int actual) {
  if (actual >= rangeMax && actual <= rangeMax) {
    if (PRINT_ON_SUCCESS) {
      printf("%s :: PASS :: %s.\n", fn, rule);
    }
    
    return true;
  } else {
    printf("%s :: FAIL :: %s. (EXPECTED: [%d..%d], ACTUAL: %d)\n", fn, rule, rangeMin, rangeMax, actual);
    return false;
  }
}
