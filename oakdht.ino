#include <DHT.h>

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
float prevtemp = 0;
float deltatemp;
char data[8];
char type[8];
char* temp;
  char* hStr;
  char tStr[8];
  char deltaStr[8];
  char prevStr[8];
  char topush[30];

// the setup routine runs once when you press reset:
void setup() {     
  
  dht.begin();           
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT); //LED on Model B
  pinMode(1, OUTPUT); //LED on Model A   
  delay(60000);
float t = dht.readTemperature();
 temp = float_to_str(t);

Particle.publish("pushbullet", temp, 60, PRIVATE);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(1, HIGH);
  delay(100);               // wait for a second
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(1, LOW); 
  delay(8000);               // wait for a second

  
// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float prevtemp = t;
  //float h = 33.342;
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //float t = digitalRead(2);
  

  if (isnan(h) || isnan(t)) {
    pushbullet_publish("Failed to read from DHT sensor!");
    float prevtemp = 0;
    return;
  }
  
  float deltatemp = prevtemp-t;
delay(200);
if (deltatemp > 0 || t > 25) {
  temp = float_to_str(t);
  //String& data = String(temp);
  //prevStr[8] = float_to_str(prevtemp);
//pushbullet_publish(temp);
Particle.publish("pushbullet", temp, 60, PRIVATE);
delay(30000);
//particle_publish(temp, "temp");
}

}


void pushbullet_publish(const char *data)
{
  Particle.publish("pushbullet", data, 60, PRIVATE);
}

void particle_publish(char data[8], char type[8])
{
  Particle.publish(type, data, 60, PRIVATE);
}

char* float_to_str(float fl)
{
  char buffer[8];

  //variables for conversions
  char hStr[8];
  
  //do the conversions
  return dtostrf(fl, 6, 2, hStr);
  //return *hStr;
}
