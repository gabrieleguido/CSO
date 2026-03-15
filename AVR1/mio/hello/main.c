#include <util/delay.h> 
#include <stdio.h>
#include "../avr_common/uart.h"
// #include <avr/io.h>

int main(){
    printf_init();

    int k = 0;
    while(1){
        printf("ciaoooooo %d\n",k);
        k++;
        _delay_ms(500);
    }
}
