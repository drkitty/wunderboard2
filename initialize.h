#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <stdint.h>
#include "types.h"


/*
 * Initialize the Wunderboard. Call this in main() before doing anything else.
 *
 * verbose: TRUE  = print debug messages (over USART)
 *          FALSE = don't print debug messages
 */
void initialize(BOOL verbose);

#endif
