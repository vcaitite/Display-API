Esta é uma API para o display de 7 segmentos da placa de expansão do arduino.

Essa API foi feita para a plataforma de desenvolvimento ST32F401RE. Tentar utilizá-la em outras plataformas pode resultar em erro.

A API em si corresponde aos arquivos MFS_DISPLAY4NUCLEO64-STMF401.h e MFS_DISPLAY4NUCLEO64-STMF401.c. Os outros arquivos são para configuração do sistema, feita através do STMCubeMx e exemplo de utilização.

Para mais informações entre em contato com os desenvolvedores:

Amanda Alkmim Rezende Teixeira: amandalkmim@gmail.com e Vitor Gabrie Reis Caitite: 

Abaixo um resumo das funções desenvolvidas:

1 - void Envia_Codigo_Display(uint8_t carac, uint8_t num_display);

2 - void Exibir_Unsigned_Int(uint16_t value);

3 - void Exibe_Letras(LETRA letra, uint8_t num_display);

    Essa função exibe uma letra em um digito do display de 7 segmentos escolhido.

    Parametros:
    LETRA letra - Escolha da letra que irá aparecer a partir do enum LETRAS. Observe que é impossível representar as letra k, m, v, w, x e z no display de 7 segmentos e, portanto, elas não existem.
    uint8_t num_display - O número do display no qual aparecerá a letra, variando de 1 a 4.
	
4 - bool Contagem_Regressiva(uint16_t start_number, uint16_t end_number);

5 - bool Contagem_Progressiva(uint16_t start_number, uint16_t end_number);

6 - void Apaga_Display();   
