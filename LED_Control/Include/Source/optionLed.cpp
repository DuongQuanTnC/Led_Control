#include "setOptionLed.h"
#define F_CPU 8000000UL
#include "avr/io.h"
#include "util/delay.h"

void option_led() {
	setInput4bit1();
	if(!(PINB&(1<<0))){
		setOutput8bit1();
		option1();
	}
	if (!(PINB&(1<<1))) {
		setOutput8bit1();
		option2();
	}
	if (!(PINB&(1<<2))) {
		setOutput8bit1();
		option3();
	}
	if (!(PINB&(1<<3))) {
		setOutput8bit1();
		option4();
	}
}