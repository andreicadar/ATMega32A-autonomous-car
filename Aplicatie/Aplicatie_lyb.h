/*
 * Aplicatie_lyb.h
 *
 * Created: 05/08/2018 08:22:29
 *  Author: Andrei Cadar
 */ 


#ifndef APLICATIE_LYB_H_
#define APLICATIE_LYB_H_

  void init_aplicatie();
  void aplicatie_main();
  
  typedef enum MMI_STATE
  {
	  MMI_SCREEN1,
	  MMI_SCREEN2,
	  MMI_SCREEN3,
	  MMI_SCREEN4,
	  MMI_SCREEN5,
	  MMI_SCREEN6,
	  MMI_SCREEN7
  } MMI_STATE_t ;

  MMI_STATE_t MMI_State_Machine;



#endif /* APLICATIE_LYB_H_ */