/**
	@file Timer_Interrupt.c for Microchip AVR Controllers
	@author Mohit
	@copyright none
	Date Created:26-Oct-2021
	Last Modified:26-Oct-2021
	
	Target->ATmega328P
	Clock Frequency->16MHz
	Connections->Sink-type wiring(active-low)
	
	ATmega328P timers:-
	TIMER0(8-bits)
	TIMER1(16-bits)
	TIMER2(8-bits)
**/

#define F_CPU 16000000UL //define the CPU Clock Frequency=16MHz

#include <avr/io.h> //contains all I/O register macros
#include <avr/util.h> //include for using delay

const uint8_t led_pin=PB5; //led pin number(5th pin of PORTB)

int main()
{
	DDRB |= (1<<led_pin); //configure led pin as ouput
	PORTB |= (1<<led_pin); //turn off the led initally
	TCCR1A = 0; //reset timer1 control register A
	
	/*enable CTC mode*/
	TCCR1B |= (1<<WGM12); //set WGM12 bit of TCCR1B register
	TCCR1B &= ~(1<<WGM13); //clear WGM13 bit of TCCR1B register
	
	/*set prescaler value to 256*/
	TCCR1B &= ~(1<<CS10); //clear CS10 bit of TCCR1B register
	TCCR1B &= ~(1<<CS11); //clear CS11 bit of TCCR1B register
	TCCR1B |= (1<<CS12); //set CS12 bit of TCCR1B register
	
	TCNT1 = 0; //reset timer1(TCCR1C = 0 in case of TIMER0 & TIMER2)
	OCR1A = 31250; //set compare match value
	TIMSK1 |= (1<<OCIE1A); //enable timer1 compare interrupt
	sei(); //enable global interrupts(SREG |= (1<<7);)
	
	while(1) //infinite loop
	{
		_delay_ms(1000); //main program
	}
	return 0;
}

ISR(TIMER1__COMPA_vect)
{
	//TCNT1 = 0; //reset timer1 here(only if the CTC mode is disabled)
	PORTB ^= (1<<led_pin); //toggle the led
}
