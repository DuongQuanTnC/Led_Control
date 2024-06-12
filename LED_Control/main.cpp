/*
 * Tuan1.cpp
 *
 * Created: 22/04/2024 21:31:50
 * Author : duong
 */ 
#define F_CPU 8000000UL
// #define BAUD 9600
// #define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>

#include "optionLed.h"
#include "setOptionLed.h"
volatile uint16_t overflow_count = 0;
volatile uint8_t led_mode = 0; // LED mode: 0 = OFF, 1 = Blink

void timer1_init() {
    DDRB = 0xFF; // set port B for output
    overflow_count = 0; // initialize overflow count
    TCNT1 = 0x00; // initial value of counter register
    TCCR1A = 0b00000000; // normal mode
    TCCR1B = 0b00000001; // no prescaler, internal clock
    TIMSK = (1<<TOIE1); // enable overflow interrupt
}

void USART_init(void) {
    // Asynchronous mode, no parity, 1 stop bit, 8 data bits
    UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
    // Normal speed, disable multi-proc
    UCSRA = 0x00;
    // Baud rate 1200bps, assuming 1MHz clock
    UBRRL = 0x33;
    UBRRH = 0x00;
    // Enable Tx and Rx, disable interrupts
    UCSRB = (1<<RXEN) | (1<<TXEN);
}

void USART_send(unsigned char data) {
    // Wait until UDRE flag = 1
    while (!(UCSRA & (1<<UDRE)));
    // Write char to UDR for transmission
    UDR = data;
}

unsigned char USART_receive(void) {
    // Wait until RXC flag = 1
    while (!(UCSRA & (1<<RXC)));
    // Read the received char from UDR
    return UDR;
}

void delay_ms(uint16_t ms) {
    while (ms--) {
        overflow_count = 0;
        TCNT1 = 0x00; // Reset timer
        while (overflow_count < 1); // Wait for ~1ms
    }
}

ISR(TIMER1_OVF_vect) {
    overflow_count++; // Increment overflow count
    if (overflow_count >= 4) { // approximately 1 ms delay
        overflow_count = 0;
    }
}

ISR(USART_RXC_vect) {
    unsigned char received_data = UDR;
    // Control LED mode based on received data
    if (received_data == '1') {
        led_mode = 1; // option 1
    } else if (received_data == '2') {
        led_mode = 2; // option 2
    } else if (received_data == '3') {
		led_mode = 3; // option 3
    } else if (received_data == '4') {
		led_mode = 4; // option 4
    }
}

void setup() {
    timer1_init();
    USART_init();
    sei(); // Enable global interrupts
    UCSRB |= (1<<RXCIE); // Enable RX Complete Interrupt
}

int main(void) {
	
	setOutput8bit1();
    setup();

    while (1) 
	{
        if (led_mode == '1')
		{
			option1();
		}
        else if (led_mode == '2') 
		{             
			option2();
        }
        else if (led_mode == '3') 
		{
            option3();
        }
        else if(led_mode == '4')
		{
            option4();
		}
    }
    return 0;
}
