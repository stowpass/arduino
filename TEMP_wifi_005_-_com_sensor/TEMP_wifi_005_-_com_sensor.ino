//include libraries
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h> 
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <dht.h>
//===================DADOS A SEREM MODIFICADOS=====================
String urlservidor = "3.19.60.179";
String pgrecebe = "teste.php";
String idequipamento = "PCG001";
//=================================================================
dht DHT;

#define DHT11_PIN D2
//Define o pino de entrada de sinal ensor temperadura
void setup() 
{
  Serial.begin(115200); //velocidade de baute
  delay(10);
        
  //connecting to wifi
  Serial.println();
  Serial.println();
  Serial.print("Conectando ao wifi ");
  

    WiFiManager wifiManager;
    
    wifiManager.autoConnect("ConfigSCG");
  
    Serial.println("");

    Serial.println("Wifi Conectado");

    //Mostra o ip que pegou na rede Atual.
    Serial.print("Seu IP na rede é: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");  
}

void loop()
{
   int chk = DHT.read11(DHT11_PIN);
    if(chk == DHTLIB_OK)
     {
        Serial.print("Temperatura: ");
       Serial.println(DHT.temperature);
      }
 //================GET NA PAGINA, FORMAÇÃO DA URL ===================================
        HTTPClient http;
        String url = "http://"+ urlservidor +"/"+pgrecebe+"?idequipamento="+idequipamento+"&data="+String(DHT.temperature);
        Serial.println(url);     
        http.begin(url);
       
        //GET method
        int httpCode = http.GET();
        if(httpCode > 0)
        {
          Serial.printf("[HTTP] GET...code: %d\n", httpCode);
          if(httpCode == HTTP_CODE_OK)
          {
              String payload = http.getString();
              Serial.println(payload);
          }
       }
       else
       {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
       }
          http.end();
          delay(3000);//TEMPO DO CICLO DE ENVIO DE TEMPERATURA PARA SISTEMA
}
    
   
