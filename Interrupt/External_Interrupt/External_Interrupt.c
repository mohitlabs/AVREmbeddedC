/**
	@file External_Interrupt.c for Microchip AVR Controllers
	@author Mohit
	@copyright none
	Date Created:26-Oct-2021
	Last Modified:26-Oct-2021
	
	Target->ATmega328P
	Clock Frequency->16MHz
	Connections->Sink-type wiring(active-low)
	
	ATmega328P Interrupts:-
	INTERRUPT0(PD2)
	INTERRUPT1(PD3)
**/

#define F_CPU 16000000UL //define the CPU Clock Frequency=16MHz

#include <avr/io.h> //contains all I/O register macros
#include <avr/util.h> //include for using delay

volatile bool isr=0; //for long interrupt service routine
const uint8_t btn_pin=PD2; //button pin number(2nd pin of PORTD)
const uint8_t led_pin=PD5; //led pin number(5th pin of PORTD)

int main()
{
	DDRD &= ~(1<<btn_pin); //configure button pin as input
	DDRD |= (1<<led_pin); //configure led pin as ouput
	PORTD |= (1<<btn_pin); //enable internal pull-up for button pin
	PORTD |= (1<<led_pin); //turn off the led initally
	
	/*set interrupt trigger condition as falling edge*/
	EICRA &= ~(1<<ISC00); //clear ISC00 bit of EICRA register
	EICRA |= (1<<ISC01); //set ISC01 bit of EICRA register
	
	EIMSK |= (1<<INT0); //enable external interrupt 0(2nd pin of PORTD)
	sei(); //enable global interrupts(SREG |= (1<<7);)
	
	while(1) //infinite loop
	{
		_delay_ms(1000); //main program
	}
	if(isr)
	{
		PORTD ^= (1<<led_pin); //toggle the led
	}
	return 0;
}

ISR(INT0_vect)
{
	isr=1; //interrupt service routine program
}
