
#include <WiFi.h>
#include <HTTPClient.h> 

// constants won't change. They're used here to set pin numbers:
char* ssid = "guest";
char* password = "sebastian01";
const int buttonPin = 12;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

WiFiClient client;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  
 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting..");
 }
  
Serial.println("Connected!!!");
Serial.println(WiFi.localIP());
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
}



void loop() {

  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    http.begin("http://10.200.36.11:8080/echo");
    http.addHeader("Content-Type", "text/plain");

    

   
         //   read the state of the pushbutton value:
      buttonState = digitalRead(buttonPin);
      // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
        if (buttonState == HIGH) {
          // turn LED on:
          digitalWrite(ledPin, HIGH);
          int httpResponseCode = http.POST("From Jesper jaooo");
          if  (httpResponseCode>0) {
          String response = http.getString();
          Serial.println(httpResponseCode);
          Serial.println(response);
          delay(1000);
          } else {
            Serial.print("Error on Post");
            Serial.println(httpResponseCode);
          }
    } else {
        // turn LED off:
        digitalWrite(ledPin, LOW);
    }
     
  http.end();

  } else {
    Serial.println("error in wifi");
  }
}
