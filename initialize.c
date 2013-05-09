/**
 * @file initialize.c
 * @author Dan Albert
 * @author Marshal Horn
 * @date Created 12/15/2010
 * @date Last updated 1/20/2013
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include "initialize.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "adc.h"
#include "diskio.h"
#include "types.h"
#include "usart.h"

// 9600 baud
#define BAUD_RATE 51

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))


void initialize(BOOL verbose)
{
	CPU_PRESCALE(0);

	USART_init(BAUD_RATE);
	USART_transmit('\f');	// Send form feed to clear the terminal.

	if (verbose)
		USART_send_string("WunderBoard initializing...\r\n");

	if (verbose)
		USART_send_string("\tSetting ADC prescaler and disabling free running "
				"mode...\r\n");

	setup_ADC(ADC_PRESCALER_32, FALSE);


	if (verbose)
		USART_send_string("\tEnabling ADC...\r\n");

	ADC_enable();


	if (verbose)
		USART_send_string("\tSetting ADC reference to Vcc...\r\n");

	ADC_set_reference(ADC_REF_VCC);


	// Configure IO //

	if (verbose)
		USART_send_string("\tConfiguring IO...\r\n");

	//DDRx corresponds to PORTx/PINx, dependng on direction of data flow --
	//PORT for output, PIN for input
	DDRA = 0b00000000;	// Buttons and switches
	DDRB = 0b11100111;	// Red enable, green enable and audio out
	DDRC = 0b11111111;	// Discrete LEDs
	DDRE = 0b01000111;	// LED Column
	DDRF = 0b00000000;	// Accelerometer

	// Disable pullups and set outputs low //
	PORTA = 0x00;
	PORTB = 0x01;
	PORTC = 0x81;
	PORTE = 0x00;
	PORTF = 0x00;


	if (verbose)
		USART_send_string("\tSetting SPI\r\n");

	//Set the SPI bus appropriately to use the LED array
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
