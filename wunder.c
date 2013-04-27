#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "initialize.h"
#include "adc.h"
#include "diskio.h"
#include "types.h"
#include "usart.h"

int main(void)
{
	initialize(TRUE);

	while (1) {

	};
}
