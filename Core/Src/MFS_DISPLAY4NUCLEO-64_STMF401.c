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

#include "MFS_DISPLAY4NUCLEO-64_STMF401.h"
#include "main.h"

// Segment byte maps for numbers 0 to 9
// {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9};
// {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const uint8_t SEGMENT_MAP_DIGIT[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};


// Segment byte maps for alpha a-z */
// {  A,   b,   c,   d,   E,   F,   G,   H,   I,   j,   k,   l,  m, ...};
// {136, 131, 167, 161, 134, 142, 144, 139, 207, 241, 182, 199, 182, 171, 163, 140, 152, 175, 146, 135, 227, 182, 182, 182, 145, 182};


void Alterna_LEDs(void) {
//	HAL_GPIO_TogglePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin)
	HAL_GPIO_TogglePin (GPIOA, LED_D1_Pin);
	HAL_Delay(100);
	HAL_GPIO_TogglePin (GPIOA, LED_D2_Pin);
	HAL_Delay(100);
	HAL_GPIO_TogglePin (GPIOA, LED_D3_Pin);
	HAL_Delay(100);
	HAL_GPIO_TogglePin (LED_D4_GPIO_Port, LED_D4_Pin);
	HAL_Delay(100);
}

void Acende_LEDs(void) {
//	void HAL_GPIO_WritePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
	HAL_GPIO_WritePin (GPIOA, LED_D1_Pin, 0);
	HAL_GPIO_WritePin (GPIOA, LED_D2_Pin, 0);
	HAL_GPIO_WritePin (GPIOA, LED_D3_Pin, 0);
	HAL_GPIO_WritePin (LED_D4_GPIO_Port, LED_D4_Pin, 0);
}

void Apaga_LEDs(void) {
//	void HAL_GPIO_WritePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
	HAL_GPIO_WritePin (GPIOA, LED_D1_Pin, 1);
	HAL_GPIO_WritePin (GPIOA, LED_D2_Pin, 1);
	HAL_GPIO_WritePin (GPIOA, LED_D3_Pin, 1);
	HAL_GPIO_WritePin (LED_D4_GPIO_Port, LED_D4_Pin, 1);
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

