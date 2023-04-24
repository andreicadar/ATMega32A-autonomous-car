# ATMega32A-autonomous-car

Software for an autonomous car

## About

I have made this project with the help of an engineer at Continental Frankfurt. The purpose was to make an autnomous car with two distance sensors(left and right) that avoids obstacles to continue its journey.
<br>
We started by learning the basics of microcontrollers and how to program them, and eventually completed this project. It was done in 2018.
<br>
I have learned a lot of C programming techniques, including operations on bits and also learned to separate the software into three layers, the [**lowest level layer**](Basic_SFWT/Basic_SFWT_Main.c), the [**conversions and operations layer**](HAL/HAL_Main.c) and [**the application layer**](Aplicatie/Aplicatie_Main.c).

## Components

<ul>
    <li>ATMEGA32A</li>
    <li>20x4 LCD Display</li>
    <li>3.3 and 5V regulator</li>
    <li>Capacitors</li>
    <li>Rezistors</li>
    <li>NPN Tranzistors</li>
    <li>Potentiometers</li>
    <li>Custom made PCB</li>
    <li>Capacitors</li>
    <li>4x5 Keyboard</li>
    <li>Sharp distance sensors</li>
    <li>Electric motor</li>
    <li>16MHz oscilator</li>
</ul>

## ATMEGA32A

This microcontroller is the key component, the brain of the project.
<br>
It has enough ADC pins for the three sensors and enough general purpose pins for the display and the keybaord.
<br>
Its frquency of 16MHz is more than enough for our project.

## Code

I found the process of writing the code for this project to be particularly interesting. As I had previous experience with C/C++ but never programmed a microcontroller before.
<br>
In the configuration part I had to toggle certain bits of some register based on my needs

```
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
```
