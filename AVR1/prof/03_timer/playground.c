#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUD 19600
#define MYUBRR (F_CPU/16/BAUD-1)

void UART_init(void){
  // Set baud rate
  UBRR0H = (uint8_t)(MYUBRR>>8);
  UBRR0L = (uint8_t)MYUBRR;

  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); /* 8-bit data */ 
  UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);   /* Enable RX and TX */  

}

void UART_putChar(uint8_t c){
  // wait for transmission completed, looping on status bit
  while ( !(UCSR0A & (1<<UDRE0)) );

  // Start transmission
  UDR0 = c;
}

char UART_isChar(){
  return (UCSR0A & (1<<UDRE0));
}

uint8_t UART_getChar(void){
  // Wait for incoming data, looping on status bit
  while ( !(UCSR0A & (1<<RXC0)) );
  
  // Return the data
  return UDR0;
    
}

// reads a string until the first newline or 0
// returns the size read
uint8_t UART_getString(uint8_t* buf){
  uint8_t* b0=buf; //beginning of buffer
  while(1){
    uint8_t c=UART_getChar();
    *buf=c;
    ++buf;
    // reading a 0 terminates the string
    if (c==0)
      return buf-b0;
    // reading a \n  or a \r return results
    // in forcedly terminating the string
    if(c=='\n'||c=='\r'){
      *buf=0;
      ++buf;
      return buf-b0;
    }
  }
}

void UART_putString(uint8_t* buf){
  while(*buf){
    UART_putChar(*buf);
    ++buf;
  }
}


volatile int int_count=0;
ISR(TIMER1_COMPA_vect) {
  ++int_count;
}

char buffer[128];
char bpos=0;

ISR(USART0_RX_vect) {
  buffer[bpos]=UDR0;
  ++bpos;
}

int UART_getStringInterrupt(char* dest_buffer){
  cli();
  memcpy(dest_buffer, buffer, bpos);
  bpos=0;
  sei();
}
int main(void){
  UART_init(); 
  const int timer_duration_ms=100;
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12); 
  uint16_t ocrval=(uint16_t)(15.62*timer_duration_ms);
  OCR1A = ocrval;
  TIMSK1 |= (1 << OCIE1A);
  sei();
  UART_putString("timer enabled\n");
  char buf[40];
  volatile int old_count=0;
  while(1){
    buf[0]=0;
    int size=UART_getStringInterrupt(buf);
    if (size)
      buf[size]=0;

    if(old_count!=int_count) {
      old_count=int_count;
      sprintf(buf, "got_int %d\n", int_count);
    }
    if(buf[0])
      UART_putString(buf);
  }
}
