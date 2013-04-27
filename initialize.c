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
 * @section DESCRIPTION
 *
 * This program will test the various components of the Wunderboard when used
 * with the corresponding host test script.
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

// Print debug messages over USART
#define VERBOSE_INITIALIZE


void initialize()
{
	CPU_PRESCALE(0);

	USART_init(BAUD_RATE);
	USART_transmit('\f');	// Send form feed to clear the terminal.

#ifdef VERBOSE_INITIALIZE
	USART_send_string("WunderBoard initializing...\r\n");
#endif

#ifdef VERBOSE_INITIALIZE
	USART_send_string("\tSetting ADC prescaler and disabling free running "
			"mode...\r\n");
#endif

	setup_ADC(ADC_PRESCALER_32, FALSE);


#ifdef VERBOSE_INITIALIZE
	USART_send_string("\tEnabling ADC...\r\n");
#endif

	ADC_enable();


#ifdef VERBOSE_INITIALIZE
	USART_send_string("\tSetting ADC reference to Vcc...\r\n");
#endif

	ADC_set_reference(ADC_REF_VCC);


	// Configure IO //

#ifdef VERBOSE_INITIALIZE
	USART_send_string("\tConfiguring IO...\r\n");
#endif

	//DDRx corresponds to PORTx/PINx, dependng on direction of data flow --
	//PORT for output, PIN for input
	DDRA = 0x00;	// Buttons and switches
	DDRB = 0xE7;	// Red enable, green enable and audio out
	DDRC = 0xff;	// Discrete LEDs
	DDRE = 0x47;	// LED Column
	DDRF = 0x00;	// Accelerometer

	// Disable pullups and set outputs low //
	PORTA = 0x00;
	PORTB = 0x01;
	PORTC = 0x81;
	PORTE = 0x00;
	PORTF = 0x00;

	//Set OC1A to toggle
	TCCR1A = 0b01000000;
	// Clk/64 and CTC mode
	TCCR1B = 0b00001011;

	OCR1A = 24;


#ifdef VERBOSE_INITIALIZE
	USART_send_string("\tSetting SPI\r\n");
#endif

	//Set the SPI bus appropriately to use the LED array
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
