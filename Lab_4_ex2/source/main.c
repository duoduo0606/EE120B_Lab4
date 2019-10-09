/*	Author: yxing024
 *  Partner(s) Name: Hao Wu
 *	Lab Section:4
 *	Assignment: Lab #  Exercise2 #
 *	Exercise Description: [count]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States {start, init, add, rls, minus, reset } States;

int ex2Tick(int);

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    States state = start;
    while (1) {
        state = ex2Tick(state);
    }
    return 1;
}

int ex2Tick(int state) {
    
    static unsigned char cntC;
    unsigned char A0 = PINA & 0x01;
    unsigned char A1 = PINA & 0x02;
    switch (state) { // Transitions
        case start:
            state = init;
            break;
        case init:
	  if (A0 & !A1) { state = add;}
	  if (A1 & !A0) { state = minus;}
	  if (A0 & A1) { state = reset;}
          if (!A0 & !A1) { state = init;}
            break;
        case add:
          if (A0) { state = add;}
	  if (A1) { state = minus;}
	  if (A0 & A1) { state = reset;}
            break;
        case waitA1:
            state = A1? pressA1: waitA1;
            break;
        case pressA1:
            state = A1? pressA1: waitA0;
            break;
        default:
            state = start;
            break;
    }
    switch (state) { // Actions
        case start: break;
        case waitA0: 
            b = 0;
            cntA0 = 0;
            break;
        case pressA0: 
            cntA0++;
            break;
        case waitA1: break;
        case pressA1:
            b = cntA0 > 100? 0x0F: 0xF0;
            break;
    }
    PORTB = b;
    return state;
}
