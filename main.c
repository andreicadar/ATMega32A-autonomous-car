/*
 * Masinuta_Autonoma.c
 *
 * Created: 05/08/2018 08:13:01
 * Author : Andrei Cadar
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Basic_SFWT/Basic_SFWT_lyb.h"
#include "HAL/HAL_lyb.h"
#include "Aplicatie/Aplicatie_lyb.h"

int main(void)
{
    init_basic_sfwt();
	init_hal();
	init_aplicatie();

    while (1) 
    {
		
    }
}

