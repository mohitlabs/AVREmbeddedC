/**
	@file Push_Button.c for Microchip AVR Controllers
	@author Mohit
	@copyright none
	Date reated: 26-Oct-2021
	Last Modified: 26-Oct-2021
	
	Target->ATmega328P
	Clock Frequency->16MHz
	Connections->Sink-type wiring(active-low)
**/

#define F_CPU 16000000UL //define the CPU Clock Frequency=16MHz

#include <avr/io.h> //contains all I/O register macros
#include <avr/util.h> //include for using delay

const uint8_t btn_pin=PD2; //button pin number(2nd pin of PORTD)
const uint8_t led_pin=PD5; //led pin number(5th pin of PORTD)
bool current_state=false; //boolean to store current state

int main()
{
	DDRD &= ~(1<<btn_pin); //configure button pin as input
	DDRD |= (1<<led_pin); //configure led pin as ouput
	PORTD |= (1<<btn_pin); //enable internal pull-up for button pin
	PORTD |= (1<<led_pin); //turn off the led initally
	
	while(1) //infinite loop
	{
		if(((PIND & (1<<btn_pin))>>btn_pin)==false) //check whether the button is pressed
		{
			_delay_ms(50); //skip the electrical transient
			while(((PIND & (1<<btn_pin))>>btn_pin)==false); //wait until button is released
			current_state=!current_state //toggle current state
			if(current_state==true) //check the status of current state
			{
				PORTD &= ~(1<<led_pin); //turn the led on
			}
			else
			{
				PORTD |= (1<<led_pin); //turn the led off
			}
		}
	}
	return 0;
}
