Introduction:
This API was developed as a work in the discipline of Embedded Systems Programming at UFMG - Prof. Ricardo de Oliveira Duarte - Department of Electronic Engineering. Library is developed and tested with Stm32F401RE (Nucleo 64 board) and arduino shield MFS (MultiFuncShield). You can check the examples given. Veja modelo em: https://github.com/vcaitite/Display_API.git

A API em si corresponde aos arquivos Core/Src/MFS_DISPLAY4NUCLEO64-STMF401.h e Core/Src/MFS_DISPLAY4NUCLEO64-STMF401.c. Os outros arquivos são para configuração do sistema, feita através do STMCubeMx e exemplo de utilização (Core/Src/main.c).

Para mais informações entre em contato com os desenvolvedores:

Amanda Alkmim Rezende Teixeira: amandaarteixeira@hotmail.com e Vitor Gabrie Reis Caitite: vitorgabriel1000@hotmail.com.

Abaixo um resumo das funções desenvolvidas:

1 - void Envia_Codigo_Display(uint8_t carac, uint8_t num_display)

    Essa função recebe um caractere e qual dos quatro displays de 7 segmentos deseja-se exibir o caracter e mostra esse caractere no display escolhido.

    Parâmetros:
  	uint8_t carac - código do caractere que se deseja imprimir.	
  	uint8_t num_display - valor correspondente ao display no qual se deseja mostrar o caractere (são válidos valores de 1 a 4, sendo o valor 1 correspondente ao dísplay mais a esquerda e o valor 4 associado ao display mais a direita)

2 - void Exibir_Unsigned_Int(uint16_t value)

    Essa função exibe um valor inteiro de 0 a 9999 no display de 7 segmentos.	
 																			
    Parâmetros:
    uint16_t value - valor de 0 a 9999 que deseja-se mostrar no display de 7 segmentos	

3 - void Exibir_Char(char carac, uint8_t num_display)
    
    Essa função exibe um caractere no display de 7 segmentos escolhido.

    Parâmetros:
  	const char caractere - caractere a ser exibido no dispay 
  	uint8_t num_display - valor correspondente ao display no qual se deseja mostrar o caractere (são válidos valores de 1 a 4, sendo o valor 1 correspondente ao dísplay mais a esquerda e o valor 4 associado ao display mais a direita).
	
  																				
  	OBS1: Não é possível representar as letras k, m, v, w, x e z no display, portanto elas são colocadas com 3 traços. 

    OBS2: Essa função não apresenta caractéres especiais, como '_', '-', ',', ' ', '*', etc...


4 - void Exibir_String(const char *string)

    Essa função exibe uma string no do display de 7 segmentos.	
 
    Parâmetros:
  	const char *string  - string a ser exibida no display.
  																				
  	OBS1: Não é possível representar as letras k, m, v, w, x e z no display, portanto elas são colocadas com 3 traços. 
  																				
  	OBS2: Ao tentar colocar uma palavra de mais de 4 digitos, o display exibirá apenas os 4 primeiros.

    OBS3: Essa função não apresenta caractéres especiais, como '_', '-', ',', ' ', '*', etc...
	
5 - bool Contagem_Regressiva(uint16_t start_number, uint16_t end_number)

    Essa função realiza uma contagem regressiva do número start_number ao número end_number. Sendo que start_number deve ser sempre maior que end_number.

    Parâmetros:
																	
  	uint16_t start_number - valor de 1 a 9999 que deseja que se inicie a contagem regressiva.
 	uint16_t end_number - valor de 0 a 9998 que deseja que se encerre a contagem regressiva.

    Essa função retorna:
														
 	COUNT_OK (0), caso a contagem termine como esperado.						
 	COUNT_NOT_OK (1), caso a contagem não tenha terminado no valor especificado.
 	PARAMS_NOT_VALID (2), a função recebeu algum parâmetro inválido.			
		

6 - bool Contagem_Progressiva(uint16_t start_number, uint16_t end_number)

    Essa função realiza uma contagem progressiva do número start_number ao número end_number. Sendo que start_number deve ser sempre menor que end_number.

    Parâmetros:
																	
  	uint16_t start_number - valor de 0 a 9998 que deseja que se inicie a contagem progressiva.
 	uint16_t end_number - valor de 1 a 9999 que deseja que se encerre a contagem progressiva.

    Essa função retorna:
														
 	COUNT_OK (0), caso a contagem termine como esperado.						
 	COUNT_NOT_OK (1), caso a contagem não tenha terminado no valor especificado.
 	PARAMS_NOT_VALID (2), a função recebeu algum parâmetro inválido.			
		

7 - void Apaga_Display()
    
    Essa função apaga todo o display de 7 segmentos.


8 - void Exibir_Palavra_Comum(PALAVRA_COMUM palavra)
    
Essa função recebe uma palavra comum e exibe ela. As palavras que ela podem receber estão enumeradas no enum PALAVRA_COMUM. Esse enum de PALAVRA_COMUM é uma forma de listar para o usuário palavras que se pode utilizar com somente os 4 displays de 7 segmentos e a limitação de letras que não são possíveis de mostrar no display.

    Parãmetros:
 	PALAVRA_COMUM palavra - Palavra a ser exibida (listada no enum PALAVRA_COMUM).

9 - void Piscar_Int(uint16_t value, uint8_t tempo)

    Essa função recebe um inteiro de 0 a 9999 e faz com que esse inteiro pisque por um tempo determinado (em segundos).

    Parâmetros:
 	uint16_t inteiro - inteiro de 0 a 9999 que piscará.
    uint8_t tempo - tempo (em segundos) no qual o display ficará piscando. 

10 - void Piscar_Palavra_Comum(PALAVRA_COMUM palavra, uint8_t tempo)

    Essa função recebe uma palavra comum e faz com que essa palavra pisque por um tempo determinado (em segundos).

    Parâmetros:
 	PALAVRA_COMUM palavra - Palavra a ser exibida (listada no enum PALAVRA_COMUM).
    uint8_t tempo - tempo (em segundos) no qual o display ficará piscando. 

11 - void Piscar_String(const char *string, uint8_t tempo)
    
     Essa função que recebe uma string e pisca ela por um tempo determinado (em segundos).

    Parâmetros:
  	const char *string  - string a ser exibida no display.
  	uint8_t tempo - tempo (em segundos) no qual o display ficará piscando. 
  																			
  	OBS1: Não é possível representar as letras k, m, v, w, x e z no display, portanto elas são colocadas com 3 traços.
  																				
  	OBS2: Ao tentar colocar uma palavra de mais de 4 digitos, o display exibirá apenas os 4 primeiros.

    OBS3: Essa função não apresenta caractéres especiais, como '_', '-', ',', ' ', '*', etc...

12 - void PassarString(const char *string) 

    Essa função que faz com que uma string "passe" pelo display de 7 segmentos. Dessa forma, o primeiro caracter começa aparecendo no display 4, depois vai para o 3, e o segundo aparece no 4 e assim em diante até que o ultimo caracter passe pelo display 1 e a string acabe.

    Parâmetros:
  	const char *string  - string a ser "passada" pelo display.
 																				
 	OBS1: Não é possível representar as letras k, m, v, w, x e z no display, portanto elas são colocadas com 3 traços. 
 																				
    OBS3: Essa função não apresenta caracteres especiais, como '_', '-', ',', ' ', '*', etc...

   


No programa de main.c podemos ver a utilização de algumas dessas funções acima. O programa inicia-se piscando a palavra on durante alguns segundos e depois exibe a
frase "press buttons", encorajando o usuário a pressionar os botões do shield. Ao pressionar o botão 1 é feita uma contagem de 0 a 10. Ao pressionar o botão 2 é feita
uma contagem regressiiva de 9999 a 9990. Ao pressionar o botão 3, o nome da placa é exibido.  
