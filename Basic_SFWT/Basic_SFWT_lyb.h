/*
 * Basic_SFWT_lyb.h
 *
 * Created: 05/08/2018 08:17:29
 *  Author: Andrei Cadar
 */ 
 #include <avr/io.h>

#ifndef BASIC_SFWT_LYB_H_
#define BASIC_SFWT_LYB_H_
 #define ctrl_port PORTC
 #define other_port PORTB
 #define E  0x80
 #define RS 0x02
 #define RW 0x40


extern void init_basic_sfwt();
extern void Task_10ms();
extern void send_a_command(unsigned char  command);
extern void send_a_character( unsigned char character);

extern int senzor1;
extern int senzor2;

#endif /* BASIC_SFWT_LYB_H_ */