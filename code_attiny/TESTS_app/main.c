/*
 * TESTS_app.c
 *
 * Created: 03/05/2023 16:44:32
 * Author : Dimitri
 */ 
/*
				 _____________________
				 |					 |
				-|					 |- VCC
				 |					 |
				-|			PB2/INT0 |- radio PWM signal
				 |					 |
manual/auto_pin -| PB4				 |-
				 |					 |
			GND -|  			 PB0 |- pin manual/auto final board
				 |___________________|
*/	




#include <avr/io.h>
#define  F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

unsigned char start_counting = 0;
uint16_t time_counter = 0;


ISR(TIMER1_COMPA_vect) //timer interrupt service routine
{
	/* counter value with time
	1 ms   = 40
	1.5 ms = 60
	2 ms   = 80 
	*/
	cli();
	
	time_counter++;
	sei();
}

ISR (INT0_vect)        // extern Interrupt service routine
{	cli();
	if((PINB &(1<<PB2))) //if logic 1 front montant
	{
		time_counter = 0;
		start_counting = 1;
	}
	
	else /*if(!(PINB &(1<<PB2)))*/ //if logic 0
	{
		start_counting = 0;
		
		if(time_counter >60)
			PORTB |= (1<<4);
		else
			PORTB &= ~(1<<4);
		//time_counter   = 0;
	}
	sei();
}

void init_GPIO()
{
	DDRB |= (1<<PB4)|(1<<PB0);
	
}
void init_interrupt()
{					
	GIMSK |= (1<<INT0);     // enabling the INT0 (external interrupt)
	MCUCR |= (1<<ISC00);    // Configuring as falling edge
	DDRB &= ~(1<<PB2);
	DDRB|=(1<<PB0);			//configure PB2 as input
	PORTB &=~(1<<PB0);		//pull down
	GIMSK|= (1<<PCIE);		//enable interrupt on INT0
	sei();	//enabling global interrupt
}
void init_timer()
{
	TCCR1 |= (1 << CTC1);  // clear timer on compare match
	TCCR1 |= (1 << CS11); //clock prescaler 8192
	OCR1C = 100; // compare match value
	TIMSK |= (1 << OCIE1A); // enable compare match interrupt
}


int main(void)
{
	init_GPIO();
	init_timer();
	init_interrupt();
	
    while (1) 
    {
		if(time_counter > 2000)
		{
			time_counter = 0;
			PORTB |= (1<<4);
		}
    }
	
}