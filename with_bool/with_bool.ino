#include <SoftwareSerial.h>
#include "DHT.h"

//#define RELAY_FAN_PIN A5 // Arduino pin connected to relay which connected to fan
#define DHTPIN 12           // Arduino pin connected to relay which connected to DHT sensor
#define DHTTYPE DHT11

//below is for light sensor
#define LIGHT 7 // define pint  for sensor
#define RELAY 2 // define pin 9 as for relay

const int TEMP_THRESHOLD_UPPER = 30; // upper threshold of temperature, change to your desire value
const int TEMP_THRESHOLD_LOWER = 29; // lower threshold of temperature, change to your desire value

const int RELAY_FAN_PIN = 3;  // Arduino pin connected to relay which connected to fan
bool state = false;

SoftwareSerial BT(10, 11); //TX, RX  pins of arduino respetively

DHT dht(DHTPIN, DHTTYPE);

float temperature;    // temperature in Celsius

String command;
void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  dht.begin();

  //light
  pinMode(LIGHT, INPUT_PULLUP);// define pin as Input  sensor
  pinMode(RELAY, OUTPUT);// define pin as OUTPUT for relay
}

void loop() 
{
  while (BT.available())
  {  
    //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    command += c; //build the string.
  } 
  if (command.length() > 0) 
  {
    Serial.println(command);
    if(command == "light on") //this command will be given as an input to switch on light1
    {
      digitalWrite(2, HIGH);
    }
    else if(command == "light off") //this command will be given as an input to switch off light1 simillarly other commands work
    {
      digitalWrite(2, LOW);
    }
    if (command == "lamp on")
    {
      bool state = true;
    }
    else if (command == "lamp off")
    {
      bool state = false;
    }
    else if (command == "fan on")
    {
      digitalWrite (3, HIGH);
    }
    else if (command == "fan of")
    {
      digitalWrite (3, LOW);
    }
    else if (command == "all on") //using this command you can switch on all devices
    {
      digitalWrite (2, HIGH);
      digitalWrite (3, HIGH);
    }
    else if (command == "off")//using this command you can switch off all devices
    {
      digitalWrite (2, LOW);
      digitalWrite (3, LOW);
    }
    command="";
  }
    // wait a few seconds between measurements.
    delay(60);
  
    temperature = dht.readTemperature();;  // read temperature in Celsius
    
    if (isnan(temperature))
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else 
    {
      if(temperature > TEMP_THRESHOLD_UPPER)
      {
        Serial.println("The fan is turned on");
        digitalWrite(3, HIGH); // turn on
      } 
      else if(temperature < TEMP_THRESHOLD_LOWER)
      {
        Serial.println("The fan is turned off");
        digitalWrite(3, LOW); // turn on
      }
    }
  
    // Light LDR Sensor Code by Robojax.com 20180210
    int L =digitalRead(LIGHT);// read the sensor 
    
    if(L == 1)
    {
      Serial.println(" light is ON");
      digitalWrite(RELAY,HIGH);// turn the relay ON
    }
    else
    {
      Serial.println("  === light is OFF");
      digitalWrite(RELAY,LOW);// turn the relay OFF
    }
    delay(500);
  }
} 
//Reset the variable
//you can add other command to control addition devices by adding an elseif 
//and the additions commands you add in sketch can be given through voice regonisation as i have created the app buttons only to control three devices

//thankyou-karthik
