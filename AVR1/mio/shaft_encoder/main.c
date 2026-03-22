#include <util/delay.h> 
#include <stdio.h>
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define PINMASK 0b11

volatile uint8_t prev_pin;
volatile uint8_t curr_pin;

volatile uint8_t int_occurred = 0;
volatile int8_t int_count = 0;

uint8_t str_buff[1024];

static int8_t transition[16] = {
    [0b0000] = 0,
    [0b0001] = 1,
    [0b0010] = -1,
    [0b0011] = 0,
    [0b0100] = -1,
    [0b0101] = 0,
    [0b0110] = 0,
    [0b0111] = 1,
    [0b1000] = 1,
    [0b1001] = 0,
    [0b1010] = 0,
    [0b1011] = -1,
    [0b1100] = 0,
    [0b1101] = -1,
    [0b1110] = 1,
    [0b1111] = 0
};
ISR(TIMER1_COMPA_vect){
    int_occurred = 1;
}

ISR(PCINT0_vect){
    prev_pin = curr_pin;
    curr_pin = (~PINB)&PINMASK;
    int_count+= transition[(prev_pin<<2)|curr_pin];
}

int main(void){
    UART_init();
    //TIMER CONF:
    TCCR1A = 0;
    TCCR1B = (1<<WGM12)|(1<<CS12)|(1<<CS10); //prescaler 1024

    //COMPARE VALUE
    OCR1A = 156;

    //ATTIVO INTERRUPT SU OCR1A 
    cli();
    TIMSK1 = (1<<OCIE1A);

    //PCINT CONF:
    DDRB &= ~PINMASK;
    PORTB |= PINMASK;

    PCICR |= (1<<PCIE0);
    PCMSK0 |= PINMASK;

    sei();
    while(1){
        while(!int_occurred);
        int_occurred = 0;
        // printf("pos %d, prev:%x , curr:%x!\n",int_count,prev_pin,curr_pin);
        snprintf((char*)str_buff,1024,"pos %d, prev:%x , curr:%x!\n",int_count,prev_pin,curr_pin);
        UART_putString(str_buff);
    }
}
