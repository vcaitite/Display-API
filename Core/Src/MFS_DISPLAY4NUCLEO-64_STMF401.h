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
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/*	MAPEAMENTO DE DÍGITOS:
 *  {D1,  D2,  D3,  D4};
 *  {0xF1,0xF2,0xF4,0xF8}; */
#define DIGIT_1 0xF1
#define DIGIT_2 0xF2
#define DIGIT_3 0xF4
#define DIGIT_4 0xF8

const uint8_t SEGMENT_MAP_DIGIT[10];

typedef enum {
	NENHUMA_LETRA = 0xFF,
	LETRA_A = 136,
	LETRA_B = 131,
	LETRA_C = 167,
	LETRA_D = 161,
	LETRA_E = 134,
	LETRA_F = 142,
	LETRA_G = 144,
	LETRA_H = 139,
	LETRA_I = 207,
	LETRA_J = 241,
	LETRA_L = 199,
	LETRA_N = 171,
	LETRA_O = 163,
	LETRA_P = 140,
	LETRA_Q = 157,
	LETRA_R = 175,
	LETRA_S = 146,
	LETRA_T = 135,
	LETRA_U = 227,
	LETRA_Y = 145,
} LETRA;

typedef enum {
	ON,
	OFF,
	YES,
	NO,
	OPEN,
	LOOP
} PALAVRA_COMUM;

/********************************************************************************
 * 								Function Description:							*
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
 * 								Function Description:							*
 * 	Função que exibe um valor inteiro de 0 a 9999 no display de 7 segmentos.	*
 *																				*
 * 	@params:																	*
 * 	uint16_t value - valor de 0 a 9999 que deseja-se mostrar no display de 		*
 * 					 de 7 segmentos												*
 ********************************************************************************/
void Exibir_Unsigned_Int(uint16_t value);

/********************************************************************************
 * 								Function Description:							*
 * 	Função que exibe uma letra em um dado digito do display de 7 segmentos.	    *
 *																				*
 * 	@params:																	*
 * 	ALPHA letra - valor descrito pelo enum ALPHA representando a letra que irá  *
 * 	aparecer no display          												*
 * 	uint8_t num_display -valor correspondente ao dígito que se deseja imprimir	*
 *  					  o caractere (são válidos valores de 1 a 4, sendo o 	*
 *  					  valor 1 correspondente ao dígito mais a esquerda e o	*
 *  					  valor 4 associado ao dígito mais a direita)           *
 * 																				*
 * 	OBS: Quando não é possível representar as letras k, m, v, w, x e z no 		*
 * 	display, portanto elas não existem.											*
 ********************************************************************************/
void Exibir_Letra(LETRA letra, uint8_t num_display);


/********************************************************************************
 * 								Function Description:							*
 * 	Função que mostra no display de 7 segmentos uma contagem regressiva 		*
 * 	partindo do "start_number" e decrementando de 1 em 1 segundo até atingir o	*
 * 	"end_number". OBS: é necessário que o "start_number" seja maior que o		*
 * 	"end_number". OBS 2: HAL_Init já deve ter sido chamada previamente.	 		*
 *																				*
 * 	@params:																	*
 * 	uint16_t start_number - valor de 1 a 9999 que deseja que se inicie a  		*
 * 					 		regressiva.											*
 *	uint16_t end_number - valor de 0 a 9998 que deseja que se encerre a  		*
 * 					 	  regressiva.											*
 *  @return: (bool)																*
 *	true - se a contagem ocorreu como planejado e chegou ao final.				*
 *	false - valores inválidos recebidos como parâmetro.							*
 ********************************************************************************/
bool Contagem_Regressiva(uint16_t start_number, uint16_t end_number);



/********************************************************************************
 * 								Function Description:							*
 * 	Função que mostra no display de 7 segmentos uma contagem progressiva 		*
 * 	partindo do "start_number" e incrementando de 1 em 1 segundo até atingir o	*
 * 	"end_number". OBS: é necessário que o "start_number" seja menor que o		*
 * 	"end_number". OBS 2: HAL_Init já deve ter sido chamada previamente.			*
 *																				*
 * 	@params:																	*
 * 	uint16_t start_number - valor de 0 a 9998 que deseja que se inicie a  		*
 * 					 		progressiva.										*
 *	uint16_t end_number - valor de 1 a 9999 que deseja que se encerre a  		*
 * 					 	  progressiva.											*
 * 					 	  														*
 *  @return: (bool)																*
 *	true - se a contagem ocorreu como planejado e chegou ao final.				*
 *	false - valores inválidos recebidos como parâmetro.							*
 ********************************************************************************/
bool Contagem_Progressiva(uint16_t start_number, uint16_t end_number);



/********************************************************************************
 * 								Function Description:							*
 * 	Função apaga todo o display.												*
 ********************************************************************************/
void Apaga_Display();

/********************************************************************************
 * 								Function Description:							*
 * Função que recebe uma palavra comum e exibe ela.                             *
 * 	                                                                            *
 * 	@params:																	*
 * 	PALAVRA_COMUM palavra - Palavra a ser exibida (listada no enum              *
 * 	PALAVRA_COMUM).                                                             *
 ********************************************************************************/
void Exibir_Palavra_Comum(PALAVRA_COMUM palavra);

/********************************************************************************
 * 								Function Description:							*
 * Função que recebe um inteiro de 0 a 9999 e faz com que esse inteiro pisque   *
 * por um tempo determinado (em segundos).                       *
 * 	                                                                            *
 * 	@params:																	*
 * 	uint16_t inteiro - inteiro de 0 a 9999 que piscará.                         *
 *  uint8_t tempo - tempo no qual o display ficará piscando                     *
 ********************************************************************************/
void Piscar_Int(uint16_t value, uint8_t tempo);

/********************************************************************************
 * 								Function Description:							*
 * Função que recebe uma palavra comum e faz com que essa palavra pisque por um *
 * tempo determinado (em segundos).						                        *
 * 	                                                                            *
 * 	@params:																	*
 * 	PALAVRA_COMUM palavra - Palavra a ser exibida (listada no enum              *
 * 	PALAVRA_COMUM).       							                            *
 *  uint8_t tempo - tempo no qual o display ficará piscando.                     *
 ********************************************************************************/
void Piscar_Palavra_Comum(PALAVRA_COMUM palavra, uint8_t tempo);

/********************************************************************************
 * 								Function Description:							*
 * Função que recebe quatro letras e faz com que elas apareçam no display 		*
 * piscando por um tempo determinado						                    *
 * 	                                                                            *
 * 	@params:																	*
 * 	LETRA letra1 - Letra a ser exibida no display 1       						*
 * 	LETRA letra2 - Letra a ser exibida no display 2  	                        *
 * 	LETRA letra3 - Letra a ser exibida no display 3  							*
 * 	LETRA letra4 - Letra a ser exibida no display 4  							*
 *  uint8_t tempo - tempo no qual o display ficará piscando.                    *
 ********************************************************************************/
void Piscar_Conjunto_Letras(LETRA letra1, LETRA letra2, LETRA letra3, LETRA letra4, uint8_t tempo);


#endif /* MFS_DISPLAY4NUCLEO_64_STMF401_H_ */
