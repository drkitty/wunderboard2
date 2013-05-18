#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <stdbool.h>


/*
 * Initialize the Wunderboard. Call this in main() before doing anything else.
 *
 * verbose: true  = print debug messages (over USART)
 *          false = don't print debug messages
 */
void initialize(bool verbose);

#endif
