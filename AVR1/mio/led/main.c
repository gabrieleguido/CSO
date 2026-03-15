#include <util/delay.h> 
#include <stdio.h>
#include "../avr_common/uart.h"
#include <avr/io.h>
// #include <avr/io.h>
int main(){
    printf_init();
    uint8_t mask = 0b100000;
    uint8_t pin8 = (1<<1);
    DDRB |= mask;
    int k = 0;
    while(1){
        if(k == 0){
            PORTB = mask|pin8;
            k = 1;
        }else{
            PORTB = pin8;
            k = 0;
        }
        if((PINB&pin8) == 0b10){
            printf("acceso\n");
        }else{
            printf("spento\n");
        }
        _delay_ms(500);
    }
}
