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



// IDEIAS:
// Display specific variables for future new display functions implementations
// void Envia_String_Display(uint8_t carac[4], uint8_t num_display)
// void Envia_Signed_Display(int8_t, uint8_t num_display)
// void Envia_Float_Display(float, uint8_t num_display)


#ifndef MFS_DISPLAY4NUCLEO_64_STMF401_H_
#define MFS_DISPLAY4NUCLEO_64_STMF401_H_
#include <stdint.h>

/*	MAPEAMENTO DE DÍGITOS:
 *  {D1,  D2,  D3,  D4};
 *  {0xF1,0xF2,0xF4,0xF8}; */
#define DIGIT_1 0xF1
#define DIGIT_2 0xF2
#define DIGIT_3 0xF4
#define DIGIT_4 0xF8

const uint8_t SEGMENT_MAP_DIGIT[10];


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



/********************************************************************************
 * 								Function Description:							*		*
 * 	Função que exibe um valor inteiro de 0 a 9990 no display de 7 segmentos.	*				*
 *																				*
 * 	@params:																	*
 * 	uint16_t value - valor de 0 a 9999 que deseja-se mostrar no display de 		*
 * 					 de 7 segmentos												*
 ********************************************************************************/
void Exibir_Unsigned_Int(uint16_t value);



/********************************************************************************
 * 								Function Description:							*		*
 * 	Função que mostra no display de 7 segmentos uma contagem regressiva 		*
 * 	partindo do "start_number" e decrementando de 1 em 1 segundo até atingir o	*
 * 	"end_number". OBS: é necessário que o "start_number" seja maior que o		*
 * 	"end_number".																*
 *																				*
 * 	@params:																	*
 * 	uint16_t start_number - valor de 1 a 9999 que deseja que se inicie a  		*
 * 					 		regressiva.											*
 *	uint16_t end_number - valor de 0 a 9998 que deseja que se encerre a  		*
 * 					 	  regressiva.											*
 ********************************************************************************/
void Contagem_Regressiva(uint16_t start_number, uint16_t end_number);



/********************************************************************************
 * 								Function Description:							*		*
 * 	Função que mostra no display de 7 segmentos uma contagem progressiva 		*
 * 	partindo do "start_number" e incrementando de 1 em 1 segundo até atingir o	*
 * 	"end_number". OBS: é necessário que o "start_number" seja menor que o		*
 * 	"end_number".																*
 *																				*
 * 	@params:																	*
 * 	uint16_t start_number - valor de 0 a 9998 que deseja que se inicie a  		*
 * 					 		progressiva.										*
 *	uint16_t end_number - valor de 1 a 9999 que deseja que se encerre a  		*
 * 					 	  progressiva.											*
 ********************************************************************************/
void Contagem_Progressiva(uint16_t start_number, uint16_t end_number);


#endif /* MFS_DISPLAY4NUCLEO_64_STMF401_H_ */
