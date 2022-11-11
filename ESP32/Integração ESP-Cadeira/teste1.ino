/*********
  THAMIRIS, MARCELO e ALEXANDRE
  Projeto de Iniciação Científica de uma Cadeira de Rodas Motorizada Controlada por Sinais Cerebrais
  Dispositivos
  EMOTIV EPOC
  ESP32
  Cadeira de Rodas Motorizada
  
  Script de ESP32 contruído bom base no projeto descrito em: https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
  
*********/
#include <DNSServer.h> //Inclui as bibliotecas
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Seta webserver para a porta 80
AsyncWebServer server(80);

// Define o nome e senha do ponto de acesso
const char* ssid = "CadeiradeRodas";
const char* password = "12345678";

const char* PARAM_INPUT_1 = "input1";

String num = "0";

/* Definição do canal DAC0 (GPIO 25) */
#define CANAL_DAC0 25

/* Definição do canal DAC1 (GPIO 26) */
#define CANAL_DAC1 26

// Variáveis auxiliares para guardar o estado das saídas
//String output26State = "off";
//String output25State = "off";

// Define os pinos de saída
//const int output25 = 25;
//const int output26 = 26;

// Páginas HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="input1" autofocus>
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);

    // Conecta ao wi-fi com nome e senha
  Serial.print("Conectando ao wi-fi...");
  
  // Remover o parâmetro 'password' se quiser que o ponto de acesso seja aberto;
  WiFi.softAP(ssid, password);

  // Imprime o endereço IP da página HTML na tela
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");https://lastminuteengineers.b-cdn.net/wp-content/uploads/iot/ESP8266-Pinout-NodeMCU.png
  Serial.println(IP);
  
  server.begin();
  
  // Inicializa as variáveis de saída como saídas
  //pinMode(output25, OUTPUT);
  //pinMode(output26, OUTPUT);

   // Seta saídas no LOW
  //digitalWrite(output26, LOW);

  // Frente e trás
  dacWrite(CANAL_DAC0, 127);

  // Esquerda e direita
  dacWrite(CANAL_DAC1, 127);  // ambos com 2,5V na saída - cadeira começa parada

  // Variável que guarda HTTP request
  String inputMessage;
  
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      num = inputMessage.toInt();
    }
    else {
      inputMessage = "Nenhuma mensagem foi enviada";
      inputParam = "none";
    }

  // CADEIRA VAI PRA FRENTE
    if (num == "1") {
      dacWrite(CANAL_DAC0, 200);  // DAC0 = 3,86V
                                // Ligar nos pinos 4 e 5 do conector - frente e trás
      dacWrite(CANAL_DAC1, 127);
    }

  // CADEIRA VAI PRA TRÁS
    else if (num == "2") {
      dacWrite(CANAL_DAC0, 60); // DAC0 = 1,14V
      dacWrite(CANAL_DAC1, 127);
    }

  // CADEIRA VAI PRA DIREITA
    else if (num == "3") {
      dacWrite(CANAL_DAC0, 127); // DAC0 volta para posição original = 2,5V
      dacWrite(CANAL_DAC1, 200); // DAC1 = 3,86V
    }

  // CADEIRA VAI PRA ESQUERDA
    else if (num == "4") {
      dacWrite(CANAL_DAC0, 127);
      dacWrite(CANAL_DAC1, 60); // DAC1 = 1,14V
    }

    //Serial.println(inputMessage);
    request->send(200, "text/html", "HTTP GET enviou o seguinte valor para o ESP32: " + inputMessage +
                                     "<br><a href=\"/\">Retornar para Página Principal</a>");

   });

}
void loop() {

}