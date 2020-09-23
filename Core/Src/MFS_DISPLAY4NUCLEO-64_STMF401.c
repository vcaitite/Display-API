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

// Display specific variables for future new diaplay functions implementations
// void Envia_Caractere_Display(uint8_t carac, uint8_t num_display)
// void Envia_String_Display(uint8_t carac[4], uint8_t num_display)
// void Envia_Unsigned_Display(uint8_t, uint8_t num_display)
// void Envia_Signed_Display(int8_t, uint8_t num_display)
// void Envia_Float_Display(float, uint8_t num_display)
// Segment byte maps for numbers 0 to 9
// {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9};
// {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
// const uint8_t SEGMENT_MAP_DIGIT[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90}

// Segment byte maps for alpha a-z */
// {  A,   b,   c,   d,   E,   F,   G,   H,   I,   j,   k,   l,  m, ...};
// {136, 131, 167, 161, 134, 142, 144, 139, 207, 241, 182, 199, 182, 171, 163, 140, 152, 175, 146, 135, 227, 182, 182, 182, 145, 182};

// Byte maps to select digit 1 to 4
// {  D1,  D2,  D3,  D4};
// {0xF1,0xF2,0xF4,0xF8};
// const

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

void Envia_Codigo_Display(uint8_t carac, uint8_t num_display) {
	static uint8_t i = 0;
	static uint8_t cod_display = 0;
	static uint16_t serie = 0;
	serie = carac;
	serie <<= 8;
	switch(num_display){
		case 1:
			cod_display = DIGITO_1;
			break;
		case 2:
			cod_display = DIGITO_2;
			break;
		case 3:
			cod_display = DIGITO_3;
			break;
		case 4:
			cod_display = DIGITO_4;
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

