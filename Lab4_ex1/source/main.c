/*	Author: yxing024
 *  Partner(s) Name: Hao Wu
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States {start, init, B0on, wait1, B1on, wait2 } States;

int ex1Tick(int);

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    States state = start;
    while (1) {
        state = ex1Tick(state);
    }
    return 1;
}

int ex1Tick(int state) {
    static unsigned char B0;
    static unsigned char B1;
    unsigned char A0 = PINA & 0x01;
    
    switch (state) { // Transitions
        case start:
            state = init;
            break;
        case init:
            state = A0? B1on: init;
            break;
        case B1on:
            state = A0? B1on: wait1;
            break;
        case wait1:
            state = A0? B0on: wait1;
            break;
        case B0on:
            state = A0? B0on: wait2;
            break;
        case wait2:
            state = A0? B1on: wait2;
            break;
        default:
            state = start;
            break;
    }
    switch (state) { // Actions
        case start: break;
        case init: 
            B0 = 0;
            B1 = 0;
            break;
        case B1on: 
            B0 = 0;
	    B1 = 1;
            break;
        case wait1: break;
        case B0on:
            B0 = 1;
	    B1 = 0;
            break;
        case wait2: break;
    }
    PORTB = B0 | (B1<<1);
    return state;
}
