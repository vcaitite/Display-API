/*
 *  MFS_DISPLAY4NUCLEO-64_STMF401.h
 *  Copyright (C) 2020  Vítor Gabriel Reis Caitité <vitorgabriel1000@hotmail.com>
 *  and Amanda Alkmim Rezende Teixeira: amandaarteixeira@hotmail.com.
 *  Version 1.0 - API with the following implemented functions:
 *
 *  void Envia_Codigo_Display(uint8_t carac, uint8_t num_display);
 *	void Exibir_Unsigned_Int(uint16_t value);
 *	void Exibir_Char(char carac, uint8_t num_display);
 *	void Exibir_String(const char *string);
 *	bool Contagem_Regressiva(uint16_t start_number, uint16_t end_number);
 *	bool Contagem_Progressiva(uint16_t start_number, uint16_t end_number);
 *	void Apaga_Display();
 *	void Exibir_Palavra_Comum(PALAVRA_COMUM palavra);
 *	void Piscar_Int(uint16_t value, uint8_t tempo);
 *	void Piscar_Palavra_Comum(PALAVRA_COMUM palavra, uint8_t tempo);
 *	void Piscar_String(const char *string, uint8_t tempo);
 *	void PassarString(const char *string);
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
 *  This API contain functions to provide use for Four Seven-segments Display (HS410361)
 *  programmed by two 74HC595 chips using  Bit Banging programming technique. This API 
 *  provide resourses just for the Seven-segments Display from MFS (MultiFuncShield) 
 *  available at:
 *  https://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/
 */



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

const uint8_t SEGMENT_MAP_CHAR[26];

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
 * 	Função que exibe um caractere no digito escolhido do display de 7 segmentos.*
 *																				*
 * 	@params:																	*
 * 	const char caractere - caractere a ser exibido no dispay                    *
 * 	uint8_t num_display - valor correspondente ao dígito que se deseja imprimir	*
 *  					  o caractere (são válidos valores de 1 a 4, sendo o 	*
 *  					  valor 1 correspondente ao dígito mais a esquerda e o	*
 *  					  valor 4 associado ao dígito mais a direita)			*
 * 																				*
 * 	OBS1: Não é possível representar as letras k, m, v, w, x e z no display,    *
 * 	portanto elas são colocadas com 3 traços.  									*
 * 																				*
 *  OBS2: Essa função não apresenta caracteres especiais, como '_', '-', ',',   *
 *  ' ', '*', etc...															*
 ********************************************************************************/
void Exibir_Char(char carac, uint8_t num_display);

/********************************************************************************
 * 								Function Description:							*
 * 	Função que exibe uma string no do display de 7 segmentos.	                *
 *																				*
 * 	@params:																	*
 * 	const char *string  - string a ser exibida no display                       *
 * 																				*
 * 	OBS1: Não é possível representar as letras k, m, v, w, x e z no display,    *
 * 	portanto elas são colocadas com 3 traços.       							*
 * 																				*
 * 	OBS2: Ao tentar colocar uma palavra de mais de 4 digitos, o display exibirá *
 * 	apenas os 4 primeiros 														*
 * 																				*
 *  OBS3: Essa função não apresenta caracteres especiais, como '_', '-', ',',   *
 *  ' ', '*', etc...															*
 ********************************************************************************/
void Exibir_String(const char *string);


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
 * Função que recebe uma string e pisca ela	por um tempo determinado.           *
 * 	                                                                            *
 *  @params:																	*
 * 	const char *string  - string a ser exibida no display                       *
 * 	uint8_t tempo - tempo no qual o display ficará piscando. 					*
 * 																				*
 * 	OBS1: Não é possível representar as letras k, m, v, w, x e z no display,    *
 * 	portanto elas são colocadas com 3 traços.       							*
 * 																				*
 * 	OBS2: Ao tentar colocar uma palavra de mais de 4 digitos, o display exibirá *
 * 	apenas os 4 primeiros   								                    *
 * 																				*
 *  OBS3: Essa função não apresenta caracteres especiais, como '_', '-', ',',   *
 *  ' ', '*', etc...															*
 ********************************************************************************/
void Piscar_String(const char *string, uint8_t tempo);


/********************************************************************************
 * 								Function Description:							*
 * Função que faz com que uma string "passe" pelo display de 7 segmentos. Dessa *
 * forma, o primeiro caracter começa aparecendo no display 4, depois vai para o *
 * 3, e o segundo aparece no 4 e assim em diante até que o ultimo caracter passe*
 * pelo display 1 e a string acabe.									            *
 * 	                                                                            *
 *  @params:																	*
 * 	const char *string  - string a ser "passada" pelo display                   *
 * 																				*
 * 	OBS1: Não é possível representar as letras k, m, v, w, x e z no display,    *
 * 	portanto elas são colocadas com 3 traços.       							*
 * 																				*
 *  OBS3: Essa função não apresenta caracteres especiais, como '_', '-', ',',   *
 *  ' ', '*', etc...															*
 ********************************************************************************/
void PassarString(const char *string);


#endif /* MFS_DISPLAY4NUCLEO_64_STMF401_H_ */
