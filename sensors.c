/*
 * sensors.c
 *
 *  Created on: Dec 4, 2013
 *      Author: C15Nikolas.Taormina
 */
#include "msp430.h"
#include "sensors.h"

void initializeSensors() {
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
	ADC10CTL1 |= ADC10SSEL1 | ADC10SSEL0;                // Select SMCLK

}

int checkRightSensor() {
	ADC10CTL0 &= ~ENC;             // clears ADC10 control register

	ADC10CTL1 = INCH_5;                       // input A5
	ADC10AE0 |= BIT5;                         // PA.1 ADC option select
	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);
	return ADC10MEM;
}

int checkLeftSensor() {
	ADC10CTL0 &= ~ENC;             // clears ADC10 control register
	ADC10CTL1 = INCH_3;                       // input A3
	ADC10AE0 |= BIT3;                         // PA.1 ADC option select
	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);
	return ADC10MEM;
}

int checkCenterSensor() {
	ADC10CTL0 &= ~ENC;             // clears ADC10 control register
	ADC10CTL1 = INCH_4;                       // input A4
	ADC10AE0 |= BIT4;                         // PA.1 ADC option select
	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);
	return ADC10MEM;
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
	__bic_SR_register_on_exit(CPUOFF);
}

