/*
 * HAL_Main.c
 *
 * Created: 05/08/2018 08:21:37
 *  Author: Andrei Cadar
 */ 

 #include "../Aplicatie/Aplicatie_lyb.h"
 #include "../Basic_SFWT/Basic_SFWT_lyb.h"
 #include "../configuration.h"
  #include <avr/delay.h>
 #define numar_iterari 2
typedef enum DISPLAY_MAINSTATE
{
	HDD4478U_IDLE,
	HD44780U_STEP1,
	HD44780U_DELAY1,
	HD44780U_STEP2,
	HD44780U_DELAY2,
	HD44780U_STEP3,
	HD44780U_DELAY3
} DISPLAY_MAINSTATE_t ;

double distanta[100] =  {5.65,  6.73 , 8.26 , 9.13 , 10.86 , 11.73 , 12.17 , 13.04 , 14.34 , 17.17 , 19.13 , 20.65 , 22.60 , 25.43 , 29.13 , 33.04 , 36.52 , 38.91 , 42.17 , 44.56 , 47.60 , 50.43 , 52.70 , 58.47 , 60.65 , 64.56 , 68.47 , 71.30 , 78.59};
double voltaj[100] =    {3.15,  2.98 , 2.63 , 2.46 , 2.21 ,  2.11 ,  2.05,   1.95 ,  1.78 ,  1.58 ,  1.42 ,  1.35 ,  1.27 ,  1.16 ,  1.04 ,  0.97 ,  0.90 ,  0.86 ,  0.82 ,  0.77 ,  0.75 ,  0.71 , 0.70 ,	0.64 ,  0.61 ,	0.59 ,	0.57 ,	0.54 ,	0.53};
int iteratie = 0;
int verificare = 1;
int colo;
unsigned int delay_counter;
double voltaj1;
double voltaj2;
double distanta1;
double distanta2;
double distanta_1_total;
double distanta_2_total;
double dist_1_partial;
double dist_2_partial;
double distante1[10];
double distante2[10];
DISPLAY_MAINSTATE_t HD44780_MainState = HD44780U_STEP1;
typedef struct LCD_Port
{
	unsigned char Port_Data;
	unsigned char Port_Control;
}LCD_Port_t;

LCD_Port_t STEP1_LCD[] = {{0x38,E + 0x00},{0x38,0x00},{0x38,E + 0x00},{0x0C,E + 0x00},{0x0C,0x00},{0x0C,E + 0x00},{0x06,E + 0x00},{0x06,0x00},{0x06,E + 0x00}};

LCD_Port_t STEP2_LCD[] = {{0x01,0x00 + E},{0x01,0x00},{0x01,0x00 + E},{0x01,0x00 + E},{0x01,0x00 + E},{'!',0x00 + E}};

LCD_Port_t STEP3_LCD[160];
unsigned char *Display_array; 

unsigned char Display_array_empty[DISPLAY_MEMORY_SIZE] ="                                                                                ";
/*                                                       0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ*/
/*                                              Row      11111111111111111111333333333333333333332222222222222222222244444444444444444444*/

unsigned char Display_array_0[DISPLAY_MEMORY_SIZE] =    "   Masina Autonoma                                                    v2.0 2019 ";
/*                                                       0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ*/
/*                                              Row      11111111111111111111333333333333333333332222222222222222222244444444444444444444*/

unsigned char Display_array_1[DISPLAY_MEMORY_SIZE] =    "   Bine ai venit!                              Andrei          < Informatii >    ";
/*                                                       0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ*/
/*                                              Row      11111111111111111111333333333333333333332222222222222222222244444444444444444444*/

unsigned char Display_array_2[DISPLAY_MEMORY_SIZE] =    " Informatii Masina   Dreapta: xx,yy cm   Stanga: xx,yy cm    Temperatura: xx,y0C ";
/*                                                       0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ*/
/*                                              Row      11111111111111111111333333333333333333332222222222222222222244444444444444444444*/

unsigned char Display_array_3[DISPLAY_MEMORY_SIZE] =    "    Putere Motor             xx%                                                ";
/*                                                       0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ*/
/*                                              Row      11111111111111111111333333333333333333332222222222222222222244444444444444444444*/

char a[5][4] =
{
	{'F','F','#','*'},
	{'1','2','3','^'},
	{'4','5','6','?'},
	{'7','8','9','x'},
	{'<','0','>','E'}
	
	
	
	
};


 void hal_main()
  {
	  afisare_distanta();
  }

  void init_hal()
  {
		Display_array = Display_array_0;
  }
  int determinare_coloana()
  {

	  if((PINA &  0xF8)  == 0b11110000)
	  {
		  return 0;
	  }
	  if((PINA & 0b11111000) == 0b11101000)
	  {
		  return 1;
	  }
	  if((PINA & 0b11111000) == 0b11011000)
	  {
		  return 2;
	  }
	  if((PINA & 0b11111000) == 0b10111000)
	  {
		  return 3;
	  }
	  if((PINA & 0b11111000) == 0b01111000)
	  {
		  return 4;
	  }
	  
	  
	  return 10;
  }
  
  char verificare_tasta()
  {
	  int  i;
	  char tasta="a";
	 if(verificare==1)
	 {
			PORTD=(PORTD| 0x0F) & (0x0F & 0x0E);
			colo = determinare_coloana();
			if(colo!=10)
			  tasta = (char)a[colo][3];
			  else
			  tasta=10;
			 
	  }

	  if(verificare==2)
	  {
		    PORTD=(PORTD| 0x0F) & (0x0F & 0x0D);
			colo = determinare_coloana();
			if(colo!=10)
			tasta = (char)a[colo][2];
			else
			tasta=10;
	  }
	

	if(verificare==3)
	  {
			PORTD=(PORTD| 0x0F) & (0x0F & 0x0B);
			  colo = determinare_coloana();
			  if(colo!=10)
			 tasta = (char)a[colo][1];
			 else
			 tasta=10;
	  }
	  
	 if(verificare==4)
		{
			PORTD=(PORTD| 0x0F) & (0x0F & 0x7);
			colo = determinare_coloana();
			if(colo!=10)
			 tasta = (char)a[colo][0];
			 else
			 tasta=10;
			 verificare = 0;
		}


	  

	
	
	  verificare++;
	  
		return tasta;
	  
  }
  
  void aflare_distanta()
  {
	  int i = 0;
	  conversie_in_distanta();
	  /*distanta_1_total+=dist_1_partial;
	  distanta_2_total+=dist_2_partial;
	  //media aritmetica o data la 10 iterari
	  distanta_1_total = 0;
	  distanta_2_total = 0;
	  for(i=0;i<=9;i++)
	  {
		  distanta_1_total+=distante1[i];
		  distanta_2_total+=distante2[i];
	  }
	  if(iteratie==(numar_iterari-1))

		  iteratie = 0;
	  
	  distanta1 = distanta_1_total/numar_iterari;
	  distanta2 = distanta_2_total/numar_iterari;*/
	  
	  
  }
  
  void conversie_in_distanta()
  {
	   voltaj1 = ((double)senzor1*5)/1024;
	   voltaj2 = ((double)senzor2*5)/1024;
	   distanta1 = 0;
	   distanta2 = 0;
	  
	  
	  int i=1;
	  while(voltaj[i]>voltaj1 && i<sizeof(voltaj))
		i++;
	  //distante1[iteratie] = ((distanta[i-1]-distanta[i])/(voltaj[i-1]-voltaj[i]))*(voltaj1-voltaj[i])+distanta[i];  //ecutia dreptei
	  distanta1 =  ((distanta[i-1]-distanta[i])/(voltaj[i-1]-voltaj[i]))*(voltaj1-voltaj[i])+distanta[i];
	  
	 i=1;
	  while(voltaj[i]>voltaj2 && i<sizeof(voltaj))
		i++;
	 // distante2[iteratie] = ((distanta[i-1]-distanta[i])/(voltaj[i-1]-voltaj[i]))*(voltaj2-voltaj[i])+distanta[i];  //ecutia dreptei
	 distanta2 =  ((distanta[i-1]-distanta[i])/(voltaj[i-1]-voltaj[i]))*(voltaj2-voltaj[i])+distanta[i];;
	 
	iteratie++;
  }
  
    unsigned char Internal_Step = 0;
  
  #define WRITE_PORT_STEP1() {\
	  PORTB = STEP1_LCD[Internal_Step].Port_Data;\
	  PORTC = (PORTC & 0x3D) | ((0xC2) & STEP1_LCD[Internal_Step].Port_Control);\
  }

  #define WRITE_PORT_STEP2() {\ 
	  PORTB = STEP2_LCD[Internal_Step].Port_Data;\
	  PORTC = (PORTC & 0x3D) | ((0xC2) & STEP2_LCD[Internal_Step].Port_Control);\
  }

  #define WRITE_PORT_STEP3() {\ 
	  PORTB = STEP3_LCD[Internal_Step].Port_Data;\
	  PORTC = (PORTC & 0x3D) | ((0xC2) & STEP3_LCD[Internal_Step].Port_Control);\
  }

  
  
  void modificare_putere_motor(int x)
  {
	  OCR1B = x*12;
  }
  
  
  
  void send_a_command(unsigned char  command)
  {
	  ctrl_port = (1<<E) | (0<<RS) | (0<<RW);
	  _delay_us(10);

	  other_port = command;
	  _delay_ms(2);
	  ctrl_port = (0<<E) | (0<<RS) | (0<<RW);
	  _delay_us(10);
  }
  void send_a_character( unsigned char character)
  {
	  ctrl_port = (1<<RS) | (1<<E);
	  _delay_us(10);
	  other_port = character;
	  _delay_us(20);
	  ctrl_port = (0<<RS) | (0<<E);
	  _delay_us(10);
  }
  
  void init_display()
  {
	  send_a_command(0x01); //clear display
	  _delay_us(50);
	  send_a_command(0x38); //data length 8 bits 2 lines character font 5x8
	  _delay_us(10);
	  send_a_command(0x0C); //display on cursor on
	  _delay_us(10);
  }
  void afisare_distanta()
  {
	  int i;

		for (i = 0; i < DISPLAY_MEMORY_SIZE ; i++)
		{
			STEP3_LCD[2*i].Port_Data = Display_array[i];
			STEP3_LCD[2*i].Port_Control = 0x8F & (0x00 + PIN_RS + PIN_E);
			STEP3_LCD[2*i + 1].Port_Data = Display_array[i];
			STEP3_LCD[2*i + 1].Port_Control = 0x8F & (0x00 + PIN_RS);
	   }
	  
	  
	 /* Update the display array */
	  for (i = 0; i < DISPLAY_MEMORY_SIZE ; i++)
	  {
		  STEP3_LCD[2*i].Port_Data = Display_array[i];
		  STEP3_LCD[2*i].Port_Control =  (0x00 + RS + E);
		  STEP3_LCD[2*i + 1].Port_Data = Display_array[i];
		  STEP3_LCD[2*i + 1].Port_Control =  (0x00 + RS);
	  }

	  switch(HD44780_MainState)
	  {
		  case HD44780U_STEP1:
		  WRITE_PORT_STEP1();
		  if (Internal_Step >= (sizeof(STEP1_LCD) / 2))
		  {
			  HD44780_MainState = HD44780U_DELAY1;
			  delay_counter = 50;
			  Internal_Step = 0;
		  }
		  else
		  {
			  Internal_Step++;
		  }
		  break;
		  case HD44780U_DELAY1:
		  if (delay_counter == 0)
		  {
			  HD44780_MainState = HD44780U_STEP2;
		  }
		  break;
		  case HD44780U_STEP2:
		  WRITE_PORT_STEP2();
		  if (Internal_Step >= (sizeof(STEP2_LCD) / 2))
		  {
			  HD44780_MainState = HD44780U_DELAY2;
			  delay_counter = 50;
			  Internal_Step = 0;
		  }
		  else
		  {
			  Internal_Step++;
		  }
		  break;
		  case HD44780U_DELAY2:
		  if (delay_counter == 0)
		  {
			  HD44780_MainState = HD44780U_STEP3;
		  }
		  break;
		  case HD44780U_STEP3:
		  WRITE_PORT_STEP3();

		  if (Internal_Step >= (sizeof(STEP3_LCD) / 2))
		  {
			  HD44780_MainState = HD44780U_DELAY3;
			  delay_counter = 100;
			  Internal_Step = 0;
		  }
		  else
		  {
			  Internal_Step++;
		  }
		  break;
		  case HD44780U_DELAY3:
		  if (delay_counter == 0)
		  {
			  HD44780_MainState = HD44780U_STEP3;
		  }
		  break;
		  case HDD4478U_IDLE:
		  break;

	  }

	  if (delay_counter > 0)
	  {
		  delay_counter --;
	  }

  }