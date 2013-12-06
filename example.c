#include <msp430.h> 
#include "sensors.h"

/*
 * main.c
 */
void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	 initializeSensors();
	 P1DIR |= 0x41;                            // Set P1.0 to output direction

	for (;;) {


		checkRightSensor();
		if (ADC10MEM < 0x222) {

			P1OUT &= ~BIT6;						// Clear P1.6 LED off
		} else {

			P1OUT |= BIT6;						// Set P1.6 LED on
		}
		_delay_cycles(100000);

		checkLeftSensor();
		if (ADC10MEM < 0x222) {
			P1OUT &= ~BIT0;                       // Clear P1.0 LED off

		} else {
			P1OUT |= BIT0;                        // Set P1.0 LED on

		}
		_delay_cycles(100000);
	}

}

