#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

const char *ssid =  "CR7";  
const char *pass =  "shuv1234";


DHT dht(0, DHT11);

WiFiClient client;

long myChannelNumber = 2232239;
const char myWriteAPIKey[] = "IKNAZRUQL91NNVMD";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.println("Tempareture: " + (String) temp);
  Serial.println("Humidity: " + (String) hum);
  ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, hum, myWriteAPIKey);
  delay(2000);
}
