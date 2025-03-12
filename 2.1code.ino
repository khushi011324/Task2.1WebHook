#include <SPI.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>

char ssid[] = "Galaxy A15 5G 040B";  
char pass[] = "12345671";  

WiFiClient client;

unsigned long myChannelNumber = 2798837;
const char * myWriteAPIKey = "XZ9Y2A5B1C3D4E6F";  

int lightSensorPin = A0;  
int lightValue = 0;       

void setup() {
    Serial.begin(115200);

    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);
}

void loop() {
   
    lightValue = analogRead(lightSensorPin);
    Serial.print("Light Intensity: ");
    Serial.println(lightValue);

    ThingSpeak.setField(1, lightValue);
    int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (response == 200) {
        Serial.println("Data sent to ThingSpeak successfully.");
    } else {
        Serial.print("Error sending data. HTTP Response Code: ");
        Serial.println(response);
    }

   
    delay(60000);
}
