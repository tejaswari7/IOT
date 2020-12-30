#include <ESP8266WiFi.h>
#include <DHT.h>

String apiKey = "api_key";            //change this api key to your thingspeak api key(search in channel write api key)
int gas_sensor = A0; 
float m = -0.3376; 
float b = 0.7165; 
float R0 = 2.82; 
String quality = "";
#define DHTPIN 0         
WiFiClient client;

const char *ssid = "Wifi_name";      //change this to your wifi name
const char *pass = "Wifi_password";  //change this to your wifi password
const char *server = "api.thingspeak.com";

DHT dht(DHTPIN, DHT11);
void setup() {
  Serial.begin(9600);      
  pinMode(gas_sensor, INPUT);
  dht.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
     }
   Serial.println("");
   Serial.println("WiFi connected");
 } 

void loop() { 
  float sensor_volt;
  float RS_gas; 
  float ratio;
  float sensorValue = analogRead(gas_sensor); 
  sensor_volt = sensorValue*(5.0/1023.0); 
  RS_gas = ((5.0*10.0)/sensor_volt)-10.0;
  ratio = RS_gas/R0;
  double ppm_log = (log10(ratio)-b)/m; 
  double ppm = pow(10, ppm_log);

  if(ppm <= 50){
    quality="Good";
    }
  else if(ppm > 50 && ppm <= 100 ){
      quality="Moderate";
  }
  else if(ppm > 100 && ppm < 300){
   quality="Unhealthy";
   }
  else if(ppm >= 300){
   quality="Hazardous";
   }
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
                 }
  if (client.connect(server,80)) 
             {  
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(ppm);
                             postStr +="&field2=";
                             postStr += String(t);
                             postStr +="&field3=";
                             postStr += String(h);
                             postStr +="&field4=";
                             postStr += String(quality);
                             postStr += "\r\n\r\n";
                             
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);

                             Serial.print("Air Quality in ppm: ");
                             Serial.print(ppm);
                             Serial.print("\nTemperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.print("\nAir Quality: ");
                             Serial.print(quality);
                             Serial.println("\nSend to Thingspeak.");
                        }
          client.stop();
          Serial.println("Waiting...");
  delay(1000);
}
