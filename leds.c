#include "leds.h"

/*

Strobing the LED latch:

The LED latch is bit 7 of PORTB. Strobing it means that you are turning the bit on, then
turning the bit off.

*/

void set_array_green(unsigned char rows)
{
	//write 0x00,0xFF,0x00 to SPI
	//check SPSR register, see datasheet for bit
	//Strobe LED Latch
}

void set_array_blue(unsigned char rows)
{
}

void set_array_red(unsigned char rows)
{
}

void clear_array()
{
	update_row( 0, 0, 0);
}

void update_row( uint8_t red, uint8_t green, uint8_t blue ) 
{
}

void led_red( uint8_t x, uint8_t y ) 
{
	/* Let's index this from the top left, like a normal screen.
	 * However, the LED array is indexed in hardware from the bottom right,
	 * with the bit position controlling y, and PORTE controlling x.
	 */

	//to reverse a column, you can use (1 << 7) >> (column & 0x07)


	//to reverse the row, you can use (7 - (row & 0x07)) | (PORTE & 0xF8)
}

void led_green( uint8_t x, uint8_t y ) 
{
}

void led_blue( uint8_t x, uint8_t y ) 
{
}

void led_off( void ) 
{
	update_row( 0, 0, 0);
}
