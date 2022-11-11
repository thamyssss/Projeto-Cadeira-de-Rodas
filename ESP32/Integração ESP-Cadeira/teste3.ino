/* Definição do canal DAC0 (GPIO 25) */
#define CANAL_DAC0 25

/* Definição do canal DAC1 (GPIO 26) */
#define CANAL_DAC1 26

void setup() {
  // Frente e trás
  dacWrite(CANAL_DAC0, 127); // REAL - 1,64V

  // Esquerda e direita
  dacWrite(CANAL_DAC1, 127);  // ambos com 2,5V na saída - cadeira começa parada

  printf("Digite o numero: ");
}

void loop() {

  int num;
  scanf("%d", &num);

  //for (int i = 1; i <= 4; i++) {
    
    // CADEIRA VAI PRA FRENTE
    if (num == 1) {
      dacWrite(CANAL_DAC0, 200);  // DAC0 ideal = 3,86V ------- REAL - 2,58V
                                  // Ligar nos pinos 4 e 5 do conector - frente e trás
    }

    // CADEIRA VAI PRA TRÁS
    else if (num == 2) {
      dacWrite(CANAL_DAC0, 60);  // DAC0 ideal = 1,14V ------- REAL - 0,78V
    }

    // CADEIRA VAI PRA DIREITA
    else if (num == 3) {
      dacWrite(CANAL_DAC0, 127);  // DAC0 volta para posição original = 2,5V ------- REAL - 1,64V
      dacWrite(CANAL_DAC1, 200);  // DAC1 ideal = 3,86V ------- REAL - 2,58V
    }

    // CADEIRA VAI PRA ESQUERDA
    else if (num == 4) {
      dacWrite(CANAL_DAC1, 60);  // DAC1 ideal = 1,14V ------- REAL - 0,78V
    }
  //}
}