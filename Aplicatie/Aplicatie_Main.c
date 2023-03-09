/*
 * Aplicatie_Main.c
 *
 * Created: 05/08/2018 08:22:13
 *  Author: Andrei Cadar
 */ 

 #include <avr/io.h>
 #include "../Basic_SFWT/Basic_SFWT_lyb.h"
 #include "../HAL/HAL_lyb.h"
 #include "../configuration.h"
 #include "Aplicatie_lyb.h"
 
 #define dreapta_zeci 30
 #define dreapta_unitati 31
 #define dreapta_zecimi 33
 #define dreapta_sutimi 34
 
  #define stanga_zeci 49
  #define stanga_unitati 50
  #define stanga_zecimi 52
  #define stanga_sutimi 53
  
  #define procent_motor_sute 28
  #define procent_motor_zeci 29
  #define procent_motor_unitati 30
  
  #define putere_max 200;
  
  int logo_time = 600;
  int counter = 0;
  char tasta;
   int option = 1;
   int asteapta_tasta_10=0;
   int numar_asteptari_curente_tasta_10=0;
   int putere_motor=0;
 


  void init_aplicatie()
  {
	

  }

  void aplicatie_main()
  {
	schimbare_continut_display();

  }
  
  void display_informatii()
  {
	   int cp2distanta1 = (int)(distanta1);
	   
	   Display_array[dreapta_zeci]=(cp2distanta1/10+'0');
	   Display_array[dreapta_unitati]=(cp2distanta1%10+'0');
	   int cpdistanta1 = (int)(distanta1*100);
	   Display_array[dreapta_zecimi]=((cpdistanta1/10)%10+'0');
	   Display_array[dreapta_sutimi]=(cpdistanta1%10+'0');
	   
	   int cp2distanta2 = (int)(distanta2);
	   
	   Display_array[stanga_zeci]=(cp2distanta2/10+'0');
	   Display_array[stanga_unitati]=(cp2distanta2%10+'0');
	   int cpdistanta2 = (int)(distanta2*100);
	   Display_array[stanga_zecimi]=((cpdistanta2/10)%10+'0');
	   Display_array[stanga_sutimi]=(cpdistanta2%10+'0');
	  
  }
  void schimbare_string_de_la(char x[],int poz)
  {
	  int l = strlen(x);
	  for(int i=0;i<l;i++)
	  {
		  Display_array[poz+i]=x[i];
	  }
	  
  }
  void umplere_patratele(int x)
  {
	  int  i;
	  for(i=0;i<x/10;i++)
	  {
		  Display_array[40+i]=(char)(219);
	  }
	  for(int j=i;j<=60;j++)
		  Display_array[40+j]=' ';
  }
  
  void schimbare_continut_display()
  {
	 
	 
	  switch (MMI_State_Machine)
	  {
			case MMI_SCREEN1:
				Display_array=Display_array_0;
				if(counter>(2*logo_time)/3)
					{
						Display_array=Display_array_empty;
						if(counter>logo_time)
							MMI_State_Machine=MMI_SCREEN2;
					}
					
				counter++;	
				break;
			
			
			case MMI_SCREEN2:
				Display_array = Display_array_1;

					tasta = verificare_tasta();
				if(asteapta_tasta_10==1)
				{
					if(numar_asteptari_curente_tasta_10<5 )
					if(tasta==10)
						numar_asteptari_curente_tasta_10++;
						else
						numar_asteptari_curente_tasta_10=0;
					else
					{
						numar_asteptari_curente_tasta_10=0;
						asteapta_tasta_10=0;
					}
				}
				else
				{
					if(tasta=='>')
					{
						asteapta_tasta_10=1;
						if(option==1)
						{
							option=2;
							schimbare_string_de_la("    < Motor >     ",61);
						}
						else
						{
							if(option==2)
							{
								option=3;
								schimbare_string_de_la("< Testare Lumini > ",61);	
							}
							else
							{	option=1;
								schimbare_string_de_la("  < Informatii >   ",61);	
							}
						}
					}
					else if(tasta=='<')
					{
						asteapta_tasta_10=1;
						if(option==1)
						{	
							option=3;	
							schimbare_string_de_la("< Testare Lumini > ",61);
						
						}
						else
						{
							if(option==2)
							{
								option=1;
								schimbare_string_de_la("  < Informatii >   ",61);		
							}
							else
							{	
								option=2;
								schimbare_string_de_la("    < Motor >        ",61);	
							}
						}
					}
					else if(tasta=='E')
					{
						asteapta_tasta_10=1;
						if(option==1)
							MMI_State_Machine=MMI_SCREEN3;
						else if(option==2)
						{
							MMI_State_Machine=MMI_SCREEN4;
						}
					}
					else if(tasta=='x')
					{
						asteapta_tasta_10=1;
						MMI_State_Machine=MMI_SCREEN2;
					}
				}
				
				
				break;
			
			
			case MMI_SCREEN3:
			tasta = verificare_tasta();
				Display_array=Display_array_2;
				display_informatii();
			 if(tasta=='x')
				{
					asteapta_tasta_10=1;
					MMI_State_Machine=MMI_SCREEN2;
				}
				break;
				
				
				
				
				
			case MMI_SCREEN4:
				Display_array=Display_array_3;
				int cp_putere_motor=putere_motor/2;
				if(cp_putere_motor==100)
					{
						Display_array[procent_motor_sute] = '1';
						Display_array[procent_motor_zeci] = '0';
						Display_array[procent_motor_unitati]='0';
					}
				else
					{
						Display_array[procent_motor_sute] = ' ';
						Display_array[procent_motor_zeci] = cp_putere_motor/10+'0';
						Display_array[procent_motor_unitati]=cp_putere_motor%10+'0';
					}
				
				umplere_patratele(putere_motor);
				
				tasta = verificare_tasta();
				if(asteapta_tasta_10==1)
				{
					if(numar_asteptari_curente_tasta_10<5 )
					if(tasta==10)
					numar_asteptari_curente_tasta_10++;
					else
					numar_asteptari_curente_tasta_10=0;
					else
					{
						numar_asteptari_curente_tasta_10=0;
						asteapta_tasta_10=0;
					}
				}
				else
				{
					if(tasta=='^')
						{
							asteapta_tasta_10=1;
							if(putere_motor<200)
								putere_motor+=10;
						}
						else if(tasta=='?')
						{
							asteapta_tasta_10=1;
							if(putere_motor>0)
								putere_motor-=10;
						}
						else if(tasta=='x')
						{
							asteapta_tasta_10=1;
							MMI_State_Machine=MMI_SCREEN2;
						}
						
						modificare_putere_motor(putere_motor);
				}
				break;
				
				
		  
	  }
	  
	
	  
  }