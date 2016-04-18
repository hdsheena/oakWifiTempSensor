#include <DHT.h>

int function_name(String argu);
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
float t;
float h;

  char tStr[8];
// the setup routine runs once when you press reset:
void setup() {     
  
  dht.begin();           
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT); //LED on Model B
  pinMode(1, OUTPUT); //LED on Model A   

Particle.disconnect();  
Particle.function("name", function_name);
Particle.connect();
Particle.disconnect();  
Particle.function("temp", temp);
Particle.connect();
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(1, HIGH);
  //function_name("string");
  delay(400);               // wait for a second
  digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(1, LOW); 
  //Particle.publish("low");
  delay(400);               // wait for a second

  
// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //float h = dht.readHumidity();
  float h = 33.342;
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //float t = digitalRead(2);
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Particle.publish("Failed to read from DHT sensor!");
    return;
  }
delay(200);
//because Particle likes character strings, convert floats to char strings
  char buffer[8];

  //variables for conversions
  char hStr[8];
  char tStr[8];
  
  //do the conversions
  dtostrf(h, 6, 2, hStr);
  dtostrf(t, 6, 2, tStr);
  //send to Particle
  Particle.publish("Humidity", hStr, 60, PRIVATE);
  Particle.publish("Temperature (C)", tStr, 60, PRIVATE);

}


int function_name(String argu)
{

  // code goes here
  Serial.print(argu);
//  return tStr;
}

int temp(String argu)
{

  // code goes here
  Serial.print(argu);
  return t;
}
