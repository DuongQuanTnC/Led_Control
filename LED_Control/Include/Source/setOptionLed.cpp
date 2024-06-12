#include "optionLed.h"
#define F_CPU 8000000UL
#include "avr/io.h"
#include "util/delay.h"
void setInput4bit1() {
	DDRB = 0xF0;
	PORTB = 0xFF;
}
void setOutput8bit1() {
	DDRB = 0xFF;
	PORTB = 0xFF;
}
void option1() {
	int j=0;
	while (j<2) {
		for (int i = 0 ; i < 8 ; i++) {
			PORTB &= ~(1<<i);
			_delay_ms(100);
			PORTB |= (1<<i);
		}
		j+=1;
	}
	
}
void option2() {
	int j=0;
	while (j<2) {
		for (int i = 0 ; i < 4 ; i++) {
			PORTB |= (1<<(i+4));
			PORTB &= ~(1<<i);
			_delay_ms(100);
		}
		for (int i = 0 ; i < 5 ; i++) {
			PORTB |= (1<<i);
			PORTB &= ~(1<<(i+4));
			_delay_ms(100);
		}
		j+=1;
		//optionLed();
	}
}

void option3() {
	int j=0;
	while (j<2) {
		for (int i = 0; i<8 ;i+=2) {
			PORTB &= ~(1<<i);
		}
		_delay_ms(500);
		for (int i = 0; i<8 ;i+=2) {
			PORTB |= (1<<i);
		}
		for (int i = 1; i<8 ;i+=2) {
			PORTB &= ~(1<<i);
		}
		_delay_ms(500);
		for (int i = 1; i<8 ;i+=2) {
			PORTB |= (1<<i);
		}
		j+=1;
	}
	
}

void option4() {
	int j=0;
	while (j<2) {
		for (int i = 0; i<4 ;i++) {
			PORTB &= ~(1<<i);
			PORTB &= ~(1<< (7-i));
			_delay_ms(200);
			PORTB |= (1<<i) | (1<<(7-i));
		}
		
		for (int i = 5; i<8 ;i++) {
			PORTB &= ~(1<<i);
			PORTB &= ~(1<< (7-i));
			_delay_ms(200);
			PORTB |= (1<<i) | (1<<(7-i));
		}
		j+=1;
	}
}
