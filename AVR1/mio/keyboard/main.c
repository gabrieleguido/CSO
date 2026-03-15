#include <util/delay.h> 
#include <stdio.h>
#include "../avr_common/uart.h"
#include <avr/io.h>

#define ROW0 0b000100
#define ROW1 0b001000
#define ROW2 0b010000
#define ROW3 0b100000

#define COL0 0b0001
#define COL1 0b0010
#define COL2 0b0100
#define COL3 0b1000

#define ROWS 4
#define COLUMNS 4


int main(){
    printf_init();

    DDRB &= 0b0000; //B legge una colonna (pin) per volta
    DDRD |= 0b111100; //D scrive GND su un pin alla volta

    PORTD |= 0b111100; //attivo le righe su 1
    PORTB |= 0b1111; //attivo i resistori su B

    uint8_t rows[ROWS];
    rows[0] = ROW0;
    rows[1] = ROW1;
    rows[2] = ROW2;
    rows[3] = ROW3;
    uint8_t columns[COLUMNS];
    columns[0] = COL0;
    columns[1] = COL1;
    columns[2] = COL2;
    columns[3] = COL3;
    
    while(1){
        for(int r = 0;r<ROWS;r++){
            PORTD &= ~(rows[r]);//metto Ri su GND
            for(int c = 0;c<COLUMNS;c++){
                if((PINB&(columns[c])) == 0){
                    printf("premuto [%d,%d]\n",r+2,c+8);
                }
                _delay_us(100);
            }
            PORTD |= 0b111100; //rimetto le righe su 5v
        }
    }
}
