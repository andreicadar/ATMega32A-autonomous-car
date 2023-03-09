/*
 * configuration.h
 *
 * Created: 09.05.2014 17:50:04
 *  Author: uid94206
 */ 


#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

/* BSW */

#define F_CPU 16000000


/*
#define ENCODER_1_PINA ((PINF >> PF0) & 0x01)
#define ENCODER_1_PINB ((PINF >> PF1) & 0x01)
#define ENCODER_2_PINA ((PINF >> PF2) & 0x01)
#define ENCODER_2_PINB ((PINF >> PF3) & 0x01)
*/
#define BUTTON_1_PIN ((PING >> PG4) & 0x01)
#define BUTTON_2_PIN ((PING >> PG3) & 0x01)

#define TOGGLE_MOTOR1_STEP_PIN()  (PORTD ^= (1 << PD4))
#define GET_MOTOR1_STEP_PIN() ((PORTD & (1 << PD4)) >> PD4)
#define SET_MOTOR1_DIR_PIN() (PORTD |= 0x20)   /* Pin 5 */
#define RESET_MOTOR1_DIR_PIN() (PORTD &= 0xDF) /* Pin 5 */

#define TOGGLE_MOTOR2_STEP_PIN()  (PORTD ^= (1 << PD6))
#define GET_MOTOR2_STEP_PIN() ((PORTD & (1 << PD6)) >> PD6)
#define SET_MOTOR2_DIR_PIN() (PORTD |= 0x80)   /* Pin 7 */
#define RESET_MOTOR2_DIR_PIN() (PORTD &= 0x7F) /* Pin 7 */


#define PIN_E 0x04      /*  Port D Pin 2 */
#define PIN_RW 0x01     /*  Port D Pin 1 */
#define PIN_RS 0x02     /*  Port D Pin 0 */

#define KEYBOARD_STIMU_PORT PORTA
#define KEYBOARD_STIMU_DPORT DDRA
#define KEYBOARD_STIMU_PORT_MASK 0x1F

#define KEYBOARD_READ_PORT PINE
#define KEYBOARD_READ_DPORT DDRE
#define KEYBOARD_READING_PORT PORTE
#define KEYBOARD_READ_PORT_POSITION 4
#define KEYBOARD_READ_PORT_MASK 0xF0


#define TARGET_SPEED_MAX 3
#define DEBOUNCE_THRESHOLD 5 /* 50 ms */


#define I2C_INTERFACE 0x01
#define PORT_INTERFACE 0x02

#define DISPLAY_MEMORY_SIZE 80


//#define MAIN_TASK_LOOP_TIME 10

#define LOGO_TIME 500uL

//#define TOGGLE_DEBUG_PIN1()  (PORTA ^= (1 << PA0))
//#define TOGGLE_DEBUG_PIN2()  (PORTA ^= (1 << PA1))
//#define DEBUG_PINS_OUTPUT()  (DDRA = 0x03)

#endif /* CONFIGURATION_H_ */