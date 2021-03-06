#include<avr/io.h>
#include "uart.h"

unsigned char d5,d4,d3,d2,d1;
unsigned int temp,a;

void hextobcd(unsigned int hex) {
	d1= hex/10000;
	temp = hex%10000;
	d2 = temp/1000;
	temp = hex%1000;
	d3 = temp/100;
	temp = hex%100;
	d4 = temp/10;
	d5 = temp%10;
}

int main (void) {
	uart_init();
	ADMUX = 0x40; /*Modify this*/
	ADCSRA = 0xE7;
	while(1) {
		while(!(ADCSRA & (1<<ADIF)));
		a=ADC;
		hextobcd(a);
		uart_tx_char(d1+0x30);
		uart_tx_char(d2+0x30);
		uart_tx_char(d3+0x30);
		uart_tx_char(d4+0x30);
		uart_tx_char(d5+0x30);
		uart_tx_char('\n');
		uart_tx_char('\r');
	}
	return 0;
}