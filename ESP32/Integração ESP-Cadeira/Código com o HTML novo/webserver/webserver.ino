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

// Páginas HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
       <img src="logo.png" width="150">
        <title>Projeto Cadeira de Rodas</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
    </head>

    <style type="text/css">
        #input {
            display: inline-block;
            position: relative;
        }

        body {
            text-align: center;
            position: absolute;
            width:100%;

            font-family: Georgia;
            color: rgb(0, 0, 0);
            background: rgb(196, 223, 238); }

        #nomes {
            font-family: Helvetica;
            display: inline-block;
            margin: 0px auto;
            text-align: center;
        }
    </style>

    </head>
    <body>
        <div id="input"></div>
            <h1>Projeto Cadeira de Rodas</h1>
            <form action="/get">
                <input type="text" name="input1" autofocus>
                <input type="submit" value="Enviar">
            </form>
        </div>

        <div id = "nomes"></div> 
            <p>Projeto de Inicia&ccedil;&atilde;o cient&iacute;fica realizado no CEFET-MG pelos alunos:</p>
            <p>Marcelo Vieira</p>
            <p>Thamiris Souza</p>
        </div>
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

  // Variável que guarda HTTP request
  String inputMessage;
  
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Frente e trás
  dacWrite(CANAL_DAC0, 127);

  // Esquerda e direita
  dacWrite(CANAL_DAC1, 127);  // ambos com 2,5V na saída - cadeira começa parada

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    
    // GET valor do input1 em <ESP_IP>/get?input1=<inputMessage>
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
    if (num == "5") {
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

    Serial.println(inputMessage);
    request->send_P(200, "text/html", index_html);                             

   });

}
void loop() {

}