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

#include "MFS_DISPLAY4NUCLEO-64_STMF401.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Segment byte maps for numbers 0 to 9
// {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9};
// {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const uint8_t SEGMENT_MAP_DIGIT[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};


// Segment byte maps for alpha a-z */
// {  A,   b,   c,   d,   E,   F,   G,   H,   I,   j,   k,   l,  m, ...};
// {136, 131, 167, 161, 134, 142, 144, 139, 207, 241, 182, 199, 182, 171, 163, 140, 152, 175, 146, 135, 227, 182, 182, 182, 145, 182};
const uint8_t SEGMENT_MAP_CHAR[26] = {136, 131, 167, 161, 134, 142, 144, 139, 207, 241, 182, 199, 182, 171, 163, 140, 152, 175, 146, 135, 227, 182, 182, 182, 145, 182};



/********************************************************************************
 * 								Function Description:							*		*
 * 	Função apaga todo o display.												*
 ********************************************************************************/
void Apaga_Display(){
	static uint8_t i = 0;
	static uint8_t cod_display = 0xFF;
	static uint16_t serie = 0;
	serie = 0xFF;
	serie <<= 8;
	serie |= cod_display;
	// Envia os 16 bits na seguinte ordem serie[15:0]
	for(i=0; i<16; i++) {
		// considera o bit mais a esquerda (mais significativo)
		// coloca a linha SER em "1" se o bit em consideração for igual 1, "0" caso contrário
		if(serie & 0x8000)
			HAL_GPIO_WritePin (GPIOA, SER_Pin, 1);
		else
			HAL_GPIO_WritePin (GPIOA, SER_Pin, 0);
		// Dê um pulso de clock em SRCLK para indicar ao Shift Register que o valor do bit deverá ser lido
		HAL_GPIO_WritePin (GPIOA, SRCLK_Pin, 1);
		HAL_GPIO_WritePin (GPIOA, SRCLK_Pin, 0);
		// desloque a half word para a esquerda 1 posição de forma que o próximo bit seja o mais significativo
		serie <<= 1;
	}
	// Dê um pulso de clock em RCLK_Pin para indicar ao Latch D que o valor do bit deverá ser lido
	HAL_GPIO_WritePin (GPIOB, RCLK_Pin, 1);
	HAL_GPIO_WritePin (GPIOB, RCLK_Pin, 0);
}

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
void Envia_Codigo_Display(uint8_t carac, uint8_t num_display) {
	static uint8_t i = 0;
	static uint8_t cod_display = 0;
	static uint16_t serie = 0;
	serie = carac;
	serie <<= 8;
	switch(num_display){
	case 1:
		cod_display = DIGIT_1;
		break;
	case 2:
		cod_display = DIGIT_2;
		break;
	case 3:
		cod_display = DIGIT_3;
		break;
	case 4:
		cod_display = DIGIT_4;
		break;
	default:
		return;
		break;
	}
	serie |= cod_display;
	// Envia os 16 bits na seguinte ordem serie[15:0]
	for(i=0; i<16; i++) {
		// considera o bit mais a esquerda (mais significativo)
		// coloca a linha SER em "1" se o bit em consideração for igual 1, "0" caso contrário
		if(serie & 0x8000)
			HAL_GPIO_WritePin (GPIOA, SER_Pin, 1);
		else
			HAL_GPIO_WritePin (GPIOA, SER_Pin, 0);
		// Dê um pulso de clock em SRCLK para indicar ao Shift Register que o valor do bit deverá ser lido
		HAL_GPIO_WritePin (GPIOA, SRCLK_Pin, 1);
		HAL_GPIO_WritePin (GPIOA, SRCLK_Pin, 0);
		// desloque a half word para a esquerda 1 posição de forma que o próximo bit seja o mais significativo
		serie <<= 1;
	}
	// Dê um pulso de clock em RCLK_Pin para indicar ao Latch D que o valor do bit deverá ser lido
	HAL_GPIO_WritePin (GPIOB, RCLK_Pin, 1);
	HAL_GPIO_WritePin (GPIOB, RCLK_Pin, 0);
}

/********************************************************************************
 * 								Function Description:							*		*
 * 	Função que exibe um valor inteiro de 0 a 9990 no display de 7 segmentos.	*				*
 *																				*
 * 	@params:																	*
 * 	uint16_t value - valor de 0 a 9999 que deseja-se mostrar no display de 		*
 * 					 de 7 segmentos												*
 ********************************************************************************/
void Exibir_Unsigned_Int(uint16_t value){
	//	Testando se o valor é válido:
	if(value > 9999 || value < 0){
		return;
	}
	uint8_t digit_1 = value/1000;
	value -= digit_1 * 1000;
	uint8_t digit_2 = value/100;
	value -= digit_2 * 100;
	uint8_t digit_3 = value/10;
	value -= digit_3 * 10;
	uint8_t digit_4 = value;
	Envia_Codigo_Display(SEGMENT_MAP_DIGIT[digit_1], 1);
	Envia_Codigo_Display(SEGMENT_MAP_DIGIT[digit_2], 2);
	Envia_Codigo_Display(SEGMENT_MAP_DIGIT[digit_3], 3);
	Envia_Codigo_Display(SEGMENT_MAP_DIGIT[digit_4], 4);
}

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
 * 	portanto elas são colocadas com 3 traços.									*
 * 																				*
 *  OBS2: Essa função não apresenta caracteres especiais, como '_', '-', ',',   *
 *  ' ', '*', etc...															*
 ********************************************************************************/
void Exibir_Char(char carac, uint8_t num_display){
	uint8_t aux = tolower(carac) - '0';

	if(aux >= 0 && aux < 10)
		Envia_Codigo_Display(SEGMENT_MAP_DIGIT[aux], num_display);
	else{
		uint8_t valor_a = 'a' - '0';

		aux = aux - valor_a;

		if(aux >= 0 && aux < 26)
			Envia_Codigo_Display(SEGMENT_MAP_CHAR[aux], num_display);
	}
}

/********************************************************************************
 * 								Function Description:							*
 * 	Função que exibe uma string no do display de 7 segmentos.	                *
 *																				*
 * 	@params:																	*
 * 	const char *string  - string a ser exibida no disply                        *
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
void Exibir_String(const char *string){
	Apaga_Display();

	if(strlen(string) > 0){
		Exibir_Char(string[0], 1);
		if(strlen(string) > 1){
			Exibir_Char(string[1], 2);
			if(strlen(string) > 2){
				Exibir_Char(string[2], 3);
				if(strlen(string) > 3)
					Exibir_Char(string[3], 4);
			}
		}
	}
}



/********************************************************************************
 * 								Function Description:							*		*
 * 	Função que mostra no display de 7 segmentos uma contagem regressiva 		*
 * 	partindo do "start_number" e decrementando de 1 em 1 segundo até atingir o	*
 * 	"end_number". OBS: é necessário que o "start_number" seja maior que o		*
 * 	"end_number". OBS 2: HAL_Init já deve ter sido chamada previamente.			*
 *																				*
 * 	@params:																	*
 * 	uint16_t start_number - valor de 1 a 9999 que deseja que se inicie a  		*
 * 					 		regressiva.											*
 *	uint16_t end_number - valor de 0 a 9998 que deseja que se encerre a  		*
 * 					 	  regressiva.											*
 *																				*
 *	@return: (bool)																*
 *	true - se a contagem ocorreu como planejado e chegou ao final.				*
 *	false - valores inválidos recebidos como parâmetro.							*
 ********************************************************************************/
bool Contagem_Regressiva(uint16_t start_number, uint16_t end_number){
	if(start_number > 9999 || start_number < 1 || end_number > 9998 ||
			end_number < 0 || start_number < end_number){
		return false;
	}
	int millis;
	for(uint16_t value = start_number; value >= end_number; value--){
		millis = HAL_GetTick();
		while(HAL_GetTick() - millis < 1000){
			Exibir_Unsigned_Int(value);
		}
	}
	return true;
}


/********************************************************************************
 * 								Function Description:							*		*
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
 *	false - valores inválidos recebidos como parâmetro.							*										*
 ********************************************************************************/
bool Contagem_Progressiva(uint16_t start_number, uint16_t end_number){
	if(start_number > 9998 || start_number < 0 || end_number > 9999 ||
			end_number < 1 || start_number > end_number){
		return false;
	}
	int millis;
	for(uint16_t value = start_number; value <= end_number; value++){
		millis = HAL_GetTick();
		while(HAL_GetTick() - millis < 1000){
			Exibir_Unsigned_Int(value);
		}
	}
	return true;
}

/********************************************************************************
 * 								Function Description:							*
 * Função que recebe uma palavra comum e exibe ela.                             *
 * 	                                                                            *
 * 	@params:																	*
 * 	PALAVRA_COMUM palavra - Palavra a ser exibida (listada no enum              *
 * 	PALAVRA_COMUM).                                                             *
 ********************************************************************************/
void Exibir_Palavra_Comum(PALAVRA_COMUM palavra){
	Apaga_Display();

	switch(palavra){
	case ON:
		Exibir_Char('O', 3);
		Exibir_Char('N', 4);
		break;

	case OFF:
		Exibir_Char('O', 2);
		Exibir_Char('F', 3);
		Exibir_Char('F', 4);
		break;

	case YES:
		Exibir_Char('Y', 2);
		Exibir_Char('E', 3);
		Exibir_Char('S', 4);
		break;

	case NO:
		Exibir_Char('N', 3);
		Exibir_Char('O', 4);
		break;

	case OPEN:
		Exibir_Char('O', 1);
		Exibir_Char('P', 2);
		Exibir_Char('E', 3);
		Exibir_Char('N', 4);
		break;

	case LOOP:
		Exibir_Char('L', 1);
		Exibir_Char('O', 2);
		Exibir_Char('O', 3);
		Exibir_Char('P', 4);
		break;

	default:
		break;
	}

}


/********************************************************************************
 * 								Function Description:							*
 * Função que recebe um inteiro de 0 a 9999 e faz com que esse inteiro pisque   *
 * por um tempo determinado (em segundos).                       				*
 * 	                                                                            *
 * 	@params:																	*
 * 	uint16_t inteiro - inteiro de 0 a 9999 que piscará.                         *
 *  uint8_t tempo - tempo no qual o display ficará piscando                     *
 ********************************************************************************/
void Piscar_Int(uint16_t value, uint8_t tempo){
	//	Testando se o valor é válido:
	if(value > 9999 || value < 0){
		return;
	}

	int millis;

	for(uint8_t i = 0; i < tempo/2; i++){
		millis = HAL_GetTick();

		while(HAL_GetTick() - millis < 500){
			Exibir_Unsigned_Int(value);
		}

		while(HAL_GetTick() - millis < 1000){
			Envia_Codigo_Display(0xFF, 1);
			Envia_Codigo_Display(0xFF, 2);
			Envia_Codigo_Display(0xFF, 3);
			Envia_Codigo_Display(0xFF, 4);
		}
	}
}

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
void Piscar_Palavra_Comum(PALAVRA_COMUM palavra, uint8_t tempo){
	int millis;

	for(uint8_t i = 0; i < tempo/2; i++){
		millis = HAL_GetTick();

		while(HAL_GetTick() - millis < 500){
			Exibir_Palavra_Comum(palavra);
		}

		while(HAL_GetTick() - millis < 1000){
			Envia_Codigo_Display(0xFF, 1);
			Envia_Codigo_Display(0xFF, 2);
			Envia_Codigo_Display(0xFF, 3);
			Envia_Codigo_Display(0xFF, 4);
		}
	}
}

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
void Piscar_String(const char *string, uint8_t tempo){
	int millis;

	for(uint8_t i = 0; i < tempo/2; i++){
		millis = HAL_GetTick();

		while(HAL_GetTick() - millis < 500){
			Exibir_String(string);
		}

		while(HAL_GetTick() - millis < 1000){
			Envia_Codigo_Display(0xFF, 1);
			Envia_Codigo_Display(0xFF, 2);
			Envia_Codigo_Display(0xFF, 3);
			Envia_Codigo_Display(0xFF, 4);
		}
	}
}

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
void PassarString(const char *string){

	// Se a string estiver vazia não exibe nada
	if(strlen(string) < 1)
		return;

	char *aux = "---";

	char *new_str = malloc(strlen(string) + 2*strlen(aux) + 1);

	strcpy(new_str, aux);
	strcat(new_str, string);
	strcat(new_str, aux);

	int millis;

	for (uint8_t i = 0; i < strlen(new_str); i++){
		millis = HAL_GetTick();

		while(HAL_GetTick() - millis < 500){
			Exibir_String(new_str + i);
		}
	}

	free(new_str);
}
