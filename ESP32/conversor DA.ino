// Exemplo prático: controle da luminosidade de dois LEDs de forma independente

/* Definição do canal DAC0 (GPIO 25) */
#define CANAL_DAC0 25

/* Definição do canal DAC1 (GPIO 26) */
#define CANAL_DAC1 26

int i;

void setup() {
}

void loop() {
  for (i = 0; i <= 255; i++) {
    dacWrite(CANAL_DAC0, i);
    dacWrite(CANAL_DAC1, 255 - i);
    delay(100);
  }

  // Frente e trás
  dacWrite(CANAL_DAC0, 127);

  // Esquerda e direita
  dacWrite(CANAL_DAC1, 127);  // ambos com 2,5V na saída - cadeira começa parada

  // CADEIRA VAI PRA FRENTE
  if (num == "1") {
    dacWrite(CANAL_DAC0, 200);  // DAC0 = 3,86V
                                // Ligar nos pinos 4 e 5 do conector - frente e trás
  }

  // CADEIRA VAI PRA TRÁS
  else if (num == "2") {
    dacWrite(CANAL_DAC0, 60); // DAC0 = 1,14V
  }

  // CADEIRA VAI PRA DIREITA
  else if (num == "3") {
    dacWrite(CANAL_DAC0, 127); // DAC0 volta para posição original = 2,5V
    dacWrite(CANAL_DAC1, 200); // DAC1 = 3,86V
  }

  // CADEIRA VAI PRA ESQUERDA
  else if (num == "4") {
    dacWrite(CANAL_DAC1, 60); // DAC1 = 1,14V
  }
}