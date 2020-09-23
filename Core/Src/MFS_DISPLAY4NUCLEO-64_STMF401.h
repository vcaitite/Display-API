/*
 *  MFS_DISPLAY4NUCLEO-64_STMF401.h
 *  Copyright (C) 2020  Vítor Gabriel Reis Caitité <vitorgabriel1000@hotmail.com>
 *  Version 1.0 - API with the following implemented functions:
 *  void Alterna_LEDs(void);
 *	void Acende_LEDs(void);
 *	void Apaga_LEDs(void);
 *	void Envia_Codigo_Display(uint8_t carac, uint8_t num_display);
 *
 *  Based on MultiFuncShield-Library-1_3 implementation accessed at
 *  https://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Created on: 30 de setembro de 2020
 *  This API contain functions to provide use of some hardware resources
 *  from MFS (MultiFuncShield) available at:
 *  https://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/
 *  Push-button switches (SW1, SW2, SW3) attended by Rising Edge External Interrupt.
 *  Leds (D1, D2, D3 and D4).
 *  Four Seven-segments Display (HS410361) programmed by two 74HC595 chips using
 *  Bit Banging programming technique.
 */


#ifndef MFS_DISPLAY4NUCLEO_64_STMF401_H_
#define MFS_DISPLAY4NUCLEO_64_STMF401_H_
#include <stdint.h>

/*	MAPEAMENTO DE DÍGITOS:
 *  {D1,  D2,  D3,  D4};
 *  {0xF1,0xF2,0xF4,0xF8}; */
#define DIGITO_1 0xF1
#define DIGITO_2 0xF2
#define DIGITO_3 0xF4
#define DIGITO_4 0xF8

void Alterna_LEDs(void);
void Acende_LEDs(void);
void Apaga_LEDs(void);


/********************************************************************************
 * 								Function Description:							*		*
 * 	Função que recebe um caractere e a posição correspondente ao dígito do 		*
 * 	display de 7 segmentos e então mostra esse caractere no dígito escolhido.	*
 *																				*
 * 	@params:																	*
 * 	uint8_t carac - código do caractere que se deseja imprimir.					*
 * 	uint8_t num_display - valor correspondente ao dígito que se deseja imprimir	*
 *  					  o caractere (são válidos valores de 1 a 4, sendo o 	*
 *  					  valor 1 correspondente ao dígito mais a esquerda e o	*
 *  					  valor 4 associado ao dígito mais a direita)			*
 ********************************************************************************/
void Envia_Codigo_Display(uint8_t carac, uint8_t num_display);




#endif /* MFS_DISPLAY4NUCLEO_64_STMF401_H_ */
