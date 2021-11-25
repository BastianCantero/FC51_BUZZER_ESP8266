//Importamos las librerias necesarias, para trabajr con el modulo ESP8266 y Firebase
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//Declaramos variable de acceso al proyecto en Firebase
#define FIREBASE_HOST "https://esp8266-34b56-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "PEcBJqNci7XGulmbRgUdk91wiPOGXcr1fRWKyvO0"

//Declaramos variable de acceso a la red WIFI
#define WIFI_SSID "BFCA"
#define WIFI_PASSWORD "79800849"

FirebaseData firebaseData;

const int pinBuzzer = 4;
int pinFC51 = 5;
int fc51On = HIGH;

void setup() {
  Serial.begin(9600);

  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);
  delay(1000);

}

void loop() {
  fc51On = digitalRead(pinFC51);

  if(fc51On == LOW){
    Serial.println("Obtaculo detectado");
    
    Firebase.setInt(firebaseData, "/FC51_", 1);
    
    buzzerr();
  }else{
    Serial.println("Despejado");

    Firebase.setInt(firebaseData, "/FC51_", 0);
  }
  delay(250);
}

void buzzerr(){
  tone(pinBuzzer, 440);
  delay(500);

  noTone(pinBuzzer);
  delay(500);
}
