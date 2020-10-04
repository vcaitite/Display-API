Esta é uma API para o display de 7 segmentos da placa de expansão do arduino.

Essa API foi feita para a plataforma de desenvolvimento ST32F401RE. Tentar utilizá-la em outras plataformas pode resultar em erro.

A API em si corresponde aos arquivos MFS_DISPLAY4NUCLEO64-STMF401.h e MFS_DISPLAY4NUCLEO64-STMF401.c. Os outros arquivos são para configuração do sistema, feita através do STMCubeMx e exemplo de utilização.

Para mais informações entre em contato com os desenvolvedores:

Amanda Alkmim Rezende Teixeira: amandaarteixeira@hotmail.com e Vitor Gabrie Reis Caitite: vitorgabriel1000@hotmail.com.

Abaixo um resumo das funções desenvolvidas:

1 - void Envia_Codigo_Display(uint8_t carac, uint8_t num_display)

    Essa função recebe um caractere e a posição correspondente ao dígito do	display de 7 segmentos e mostra esse caractere no dígito escolhido.

    Parâmetros:
  	uint8_t carac - código do caractere que se deseja imprimir.	
  	uint8_t num_display - valor correspondente ao dígito que se deseja imprimir	o caractere (são válidos valores de 1 a 4, sendo o valor 1 correspondente ao dígito mais a esquerda e o	valor 4 associado ao dígito mais a direita)

2 - void Exibir_Unsigned_Int(uint16_t value)

    Essa função exibe um valor inteiro de 0 a 9999 no display de 7 segmentos.	
 																			
    Parâmetros:
    uint16_t value - valor de 0 a 9999 que deseja-se mostrar no display de 7 segmentos	

3 - void Exibir_Char(char carac, uint8_t num_display)
    
    Essa função exibe um caractere no digito escolhido do display de 7 segmentos.

    Parâmetros:
  	const char caractere - caractere a ser exibido no dispay 
  	uint8_t num_display - valor correspondente ao dígito que se deseja imprimir o caractere (são válidos valores de 1 a 4, sendo o valor 1 correspondente ao dígito mais a esquerda e o valor 4 associado ao dígito mais a direita).	
  																				
  	OBS1: Não é possível representar as letras k, m, v, w, x e z no display, portanto elas são colocadas com 3 traços. 

4 - void Exibir_String(const char *string)

    Essa função exibe uma string no do display de 7 segmentos.	
 
    Parâmetros:
  	const char *string  - string a ser exibida no display.
  																				
  	OBS1: Não é possível representar as letras k, m, v, w, x e z no display, portanto elas são colocadas com 3 traços. 
  																				
  	OBS2: Ao tentar colocar uma palavra de mais de 4 digitos, o display exibirá apenas os 4 primeiros.
	
5 - bool Contagem_Regressiva(uint16_t start_number, uint16_t end_number)

    Essa função realiza uma contagem pregressiva do número start_number ao número end_number. Sendo que start_number deve ser sempre maior que end_number.

    Parâmetros:
																	
  	uint16_t start_number - valor de 1 a 9999 que deseja que se inicie a contagem regressiva.
 	uint16_t end_number - valor de 0 a 9998 que deseja que se encerre a contagem regressiva.

    Essa função retorna:
														
 	true - se a contagem ocorreu como planejado e chegou ao final.
 	false - valores inválidos recebidos como parâmetro.
		

6 - bool Contagem_Progressiva(uint16_t start_number, uint16_t end_number)

    Essa função realiza uma contagem progressiva do número start_number ao número end_number. Sendo que start_number deve ser sempre menor que end_number.

    Parâmetros:
																	
  	uint16_t start_number - valor de 0 a 9998 que deseja que se inicie a contagem progressiva.
 	uint16_t end_number - valor de 1 a 9999 que deseja que se encerre a contagem progressiva.

    Essa função retorna:
														
 	true - se a contagem ocorreu como planejado e chegou ao final.
 	false - valores inválidos recebidos como parâmetro.
		

7 - void Apaga_Display()
    
    Essa função apaga todo o display de 7 segmentos.


8 - void Exibir_Palavra_Comum(PALAVRA_COMUM palavra)
    
Essa função recebe uma palavra comum e exibe ela. As palavras que ela podem receber estão enumeradas no enum PALAVRA_COMUM

    Parãmetros:
 	PALAVRA_COMUM palavra - Palavra a ser exibida (listada no enum PALAVRA_COMUM).

9 - void Piscar_Int(uint16_t value, uint8_t tempo)

    Essa função recebe um inteiro de 0 a 9999 e faz com que esse inteiro pisque por um tempo determinado (em segundos).

    Parâmetros:
 	uint16_t inteiro - inteiro de 0 a 9999 que piscará.
    uint8_t tempo - tempo no qual o display ficará piscando.

10 - void Piscar_Palavra_Comum(PALAVRA_COMUM palavra, uint8_t tempo)

    Essa função recebe uma palavra comum e faz com que essa palavra pisque por um tempo determinado (em segundos).

    Parâmetros:
 	PALAVRA_COMUM palavra - Palavra a ser exibida (listada no enum PALAVRA_COMUM).
    uint8_t tempo - tempo no qual o display ficará piscando. 

11 - void Piscar_String(const char *string, uint8_t tempo)
    
     Essa função que recebe uma string e pisca ela	por um tempo determinado.

    Parâmetros:
  	const char *string  - string a ser exibida no display.
  	uint8_t tempo - tempo no qual o display ficará piscando. 
  																			
  	OBS1: Não é possível representar as letras k, m, v, w, x e z no display, portanto elas são colocadas com 3 traços.
  																				
  	OBS2: Ao tentar colocar uma palavra de mais de 4 digitos, o display exibirá 
  	apenas os 4 primeiros 

   
