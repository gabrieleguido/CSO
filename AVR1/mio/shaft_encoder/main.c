#include <util/delay.h> 
#include <stdio.h>
#include "../avr_common/uart.h"
#include <avr/io.h>

typedef int(*StateFn)(uint8_t);

StateFn state;


int State00(uint8_t next);
int State01(uint8_t next);
int State10(uint8_t next);
int State11(uint8_t next);

int State00(uint8_t next){
    if(next == 0b00001){
        state = State01;
        return 1;
    }
    if(next == 0b10000){
        state = State10;
        return -1;
    }
    return 0;
}
int State01(uint8_t next){
    if(next == 0b10001){
        state = State11;
        return 1;
    }
    if(next == 0b00000){
        state = State00;
        return -1;
    }
    return 0;
}
int State10(uint8_t next){
    if(next == 0b00000){
        state = State00;
        return 1;
    }
    if(next == 0b10001){
        state = State11;
        return -1;
    }
    return 0;
}
int State11(uint8_t next){
    if(next == 0b10000){
        state = State10;
        return 1;
    }
    if(next == 0b00001){
        state = State01;
        return -1;
    }
    return 0;
}



int main(){
    printf_init();
    state = State00;
    uint8_t mask = 0b10001;
    //attivo 8 e 12 in lettura
    DDRB &= ~mask;
    //attivo i resistori sui pin:
    PORTB |= mask;
    int k = 0;
    uint8_t prev_state = (~PINB)&mask;
    uint8_t curr_state;
    while(1){
        curr_state = (~PINB)&mask;
        //printf("state: %1d x x x %1d\n",(curr_state&0b10000)>>4,curr_state&0b1);
        // printf("state: %d\n",curr_state);
        if(prev_state != curr_state){
            k+=(*state)(curr_state);
        }
        printf("count: %d\n",k);
        prev_state = curr_state;
    }
}
