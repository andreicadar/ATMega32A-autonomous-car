/*
 * Basic_SFWT_Main.c
 *
 * Created: 05/08/2018 08:16:16
 *  Author: Andrei Cadar
 */ 

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <avr/delay.h>
 #include "../Aplicatie/Aplicatie_lyb.h"

 unsigned int senzor1;
 unsigned int senzor2;
 static volatile int senzoractiv;
 void Task_10ms();
 
 //DISPLAY

 void init_basic_sfwt()
 {
	DDRB = 0xFF;
/*	PB 0-7 display
	*/

	DDRD = 0xFF;
	/* PD0-3 tastatura_coloane
	   PD4 motor
	   PD5 servo
	   PD6 semnalizare1
	   PD7 semnalizare2
	*/
	//PORTD = 0xFF;
	DDRA = 0x00;
	PORTA = 0xF8;
	/*
	   PA0 senzor_distanta_1
	   PA1 senzor_distanta_2
	   PA2 senzor_temperatura
	pull up pentru_liniile_tastaturii*/

	DDRC = 0xC2;


	//TIMER 0
	TCCR0 = (1<<WGM01) + (1<<CS00) + (1<<CS01) + (0<<CS02); //prescaler 64
	OCR0 = 250;


	//TIMER 1
	TCCR1B =  (1<<WGM12) + (1<<WGM13) + (1<<CS11) + (1<<CS10); //prescaler 64, mod 12
	TCCR1A = (1<<COM1A1) + (1<<COM1B1) + (1<<WGM11);

	ICR1 = 2500;
	OCR1A = 187; // 125    187.5     250 (pozitii servo)
	OCR1B = 0;
	
	
	//TIMER 2
	TCCR2 = (1<<WGM21) + (1<<CS22) + (1<<CS21) + (1<<CS20); //prescaler 1024
	OCR2 = 156;



	TIMSK |= (1<<OCIE2);
	TIMSK |= (1<<OCIE0);

	//ADC
	
	ADCSRA = (0<<ADPS2) | (0<<ADPS0) | (1<<ADEN);
	ADCSRA |= ((1<<ADSC) + (1<<ADIE) + (1<<ADATE));
	SFIOR = 0x00;
	senzoractiv = 1;
	sei(); //activam intreruperile
	


 }

ISR(ADC_vect)
{
	int val;

	if(senzoractiv==1)
		{
	
			senzor1 = ADC;
			//senzor1v = (double)senzor1*5/1024;
			ADMUX =   (1<<REFS0) + (1<<MUX0);
			
		
			ADCSRA |=(1<<ADSC);
			senzoractiv = 2;
		
		}
		/*else
		{
			senzor2 = ADC;
			//senzor2v = (double)senzor2*5/1024;
			
				ADMUX =   (1<<REFS0);
			ADCSRA |=(1<<ADSC);
			senzoractiv = 1;
		}*/
		  
}




 ISR(TIMER2_COMP_vect)
 {
	 Task_10ms();
 }
 
 
 ISR(TIMER0_COMP_vect)
  {
	   hal_main();
  }

 void basic_sfwt_main()
 {
	
 }

 void Task_10ms()
 {
	 aplicatie_main();
	 aflare_distanta();
	 basic_sfwt_main();
 }

