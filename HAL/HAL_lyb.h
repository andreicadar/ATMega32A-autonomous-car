/*
 * HAL_lyb.h
 *
 * Created: 05/08/2018 08:21:55
 *  Author: Andrei Cadar
 */ 

#include "../configuration.h"
#ifndef HAL_LYB_H_
#define HAL_LYB_H_

  void init_hal();
  void hal_main();
  char verificare_tasta();
  void aflare_distanta();
  void modificare_putere_motor(int x);

extern unsigned char *Display_array; 
extern unsigned char Display_array_empty[DISPLAY_MEMORY_SIZE];
extern unsigned char Display_array_0[DISPLAY_MEMORY_SIZE];
extern unsigned char Display_array_1[DISPLAY_MEMORY_SIZE];
extern unsigned char Display_array_2[DISPLAY_MEMORY_SIZE];
extern unsigned  char Display_array_3[DISPLAY_MEMORY_SIZE];
extern double distanta1;
extern double distanta2;



#endif /* HAL_LYB_H_ */