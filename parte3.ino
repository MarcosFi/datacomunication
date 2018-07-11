#include <ESP8266WiFi.h> // biblioteca para usar as funções de Wifi do módulo ESP8266
#include "UbidotsESPMQTT.h"
#define TOKEN "BBFF-tCRqvFa519QyRd1m3mdtDSopwwrZ3l"
#define MQTTCLIENTNAME "CLIENTEDADOS"
 

bool led_state = false;
 
// Definições da rede Wifi
const char* SSID = "LifeBox";
const char* PASSWORD = "lifebox123";

Ubidots cliente (TOKEN, MQTTCLIENTNAME);

void callback(char *topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  if ((char)payload[0]=='1'){
    digitalWrite(16, HIGH);
  }
  else{
    digitalWrite(16, LOW);
  }
Serial.println();
}


 
/*
 * função que conecta o NodeMCU na rede Wifi
 * SSID e PASSWORD devem ser indicados nas variáveis
 */
void reconnectWiFi() 
{
  if(WiFi.status() == WL_CONNECTED)
    return;
 
  WiFi.begin(SSID, PASSWORD);
 
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
 
  Serial.println();
  Serial.print("Conectado com sucesso na rede: ");
  Serial.println(SSID);
  Serial.print("IP obtido: ");
  Serial.println(WiFi.localIP());  
}
 
void initWiFi()
{
  delay(10);
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");
 
  reconnectWiFi();
}
 
 
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  cliente.setDebug(true);
  
  Serial.println("nIniciando configuração WiFin");
  initWiFi();
 
  Serial.println("nConfiguração finalizada, iniciando loopn"); 

  cliente.wifiConnection("LifeBox", "lifebox123");
  cliente.begin(callback);
  cliente.ubidotsSubscribe("esp8266", "atuador");
  }
 
void loop() {
 
  if(!cliente.connected()){
      cliente.reconnect();
      cliente.ubidotsSubscribe("Dados_do_node", "atuador");
      }
cliente.loop();

for(int j=0; j<5; j++){
       
    Serial.print("VAR = "); Serial.println(j);
   
    cliente.add("VAR", j);
  
    delay(1000);
    cliente.ubidotsPublish("Dados_do_node");
    //cliente.setDebug(true);

    //cliente.ubidotsSubscribe("Dados_do_node", "setpoint"));
    
    //cliente.ubidotsSubscribe("Dados_do_node", "atuador");

    cliente.loop();
    
    
    delay(100); 
  } 
}
