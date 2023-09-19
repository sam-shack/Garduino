//Libraries
#include <DS18B20.h>
#include <OneWire.h>


//Pins
#define photoRes A1
#define soil1 A2
#define soil2 A3
#define soil3 A4
#define soil4 A5


#define floatSwitch1 22
#define floatSwitch2 24
#define floatSwitch3 26
#define floatSwitch4 28

// relay pins 38, 40, 42, 44

#define relay1 44
#define relay2 42
#define relay3 40
#define relay4 38
//Variables
int floatPin1, floatPin2, floatPin3, floatPin4 = 0;
float lightReading, tempC, tempK, tempF = 0;

int airValue[4];
int waterValue[4];


float soilMoistureValue1, soilMoistureValue2, soilMoistureValue3, soilMoistureValue4;
int soilMoisturePercent1, soilMoisturePercent2, soilMoisturePercent3, soilMoisturePercent4;

//DS18B20 ds(30);
//Setup Serial & Pins
void setup() {
    Serial.begin(9600);
    pinMode(floatSwitch1, INPUT_PULLUP);
    pinMode(floatSwitch2, INPUT_PULLUP);
    pinMode(floatSwitch3, INPUT_PULLUP);
    pinMode(floatSwitch4, INPUT_PULLUP);
    pinMode(relay1, OUTPUT);
    digitalWrite(relay1, LOW);
    pinMode(relay2, OUTPUT);
    digitalWrite(relay2, LOW);
    pinMode(relay3, OUTPUT);
    digitalWrite(relay3, LOW);
    pinMode(relay4, OUTPUT);
    digitalWrite(relay4, LOW);

    //basic calibration sequence
    Serial.print("Hold all sensors out of water");
    delay(10000);
    airValue[1] = analogRead(soil1);
    airValue[2] = analogRead(soil2);
    airValue[3] = analogRead(soil3);
    airValue[4] = analogRead(soil4);

    Serial.print("Put all sensors in water");
    delay(10000);
    waterValue[1] = analogRead(soil1);
    waterValue[2] = analogRead(soil2);
    waterValue[3] = analogRead(soil3);
    waterValue[4] = analogRead(soil4);
}

void loop() {
//Water Level
    floatPin1 = digitalRead(floatSwitch1);
    floatPin2 = digitalRead(floatSwitch2);
    floatPin3 = digitalRead(floatSwitch3);
    floatPin4 = digitalRead(floatSwitch4); 
//Light
    lightReading = analogRead(photoRes);
//Temp
    tempK = tempC + 273.15;
  //tempF = ds.getTempF();
  //tempC = ds.getTempC();
//Soil Moisture
        soilMoistureValue1 = analogRead(soil1);
        soilMoisturePercent1 = map(soilMoistureValue1, airValue[1], waterValue[1], 0, 100);
        soilMoistureValue2 = analogRead(soil2);
        soilMoisturePercent2 = map(soilMoistureValue2, airValue[2], waterValue[2], 0, 100);
        soilMoistureValue3 = analogRead(soil3);
        soilMoisturePercent3 = map(soilMoistureValue3, airValue[3], waterValue[3], 0, 100);
        soilMoistureValue4 = analogRead(soil4);
        soilMoisturePercent4 = map(soilMoistureValue4, airValue[4], waterValue[4], 0, 100);
    
    //Serial.println(soilMoisturePercent1);

if(soilMoisturePercent1 < 50)
{
  digitalWrite(relay1, LOW);
} else {
  digitalWrite(relay1, HIGH);  
}

if(soilMoisturePercent2 < 50)
{
  digitalWrite(relay2, LOW);
} else {
  digitalWrite(relay2, HIGH);  
}

if(soilMoisturePercent3 < 50)
{
  digitalWrite(relay3, LOW);
} else {
  digitalWrite(relay3, HIGH);  
}

if(soilMoisturePercent4 < 50)
{
  digitalWrite(relay4, LOW);
} else {
  digitalWrite(relay4, HIGH);  
}
    
    // Serial.print(tempF);
    // Serial.print("     ");    
    // Serial.print(lightReading);
    // Serial.print("     ");
    // Serial.print(floatPin1);
    // Serial.print("     ");
    // Serial.print(floatPin2);
    // Serial.print("     ");
    // Serial.print(floatPin3);
    // Serial.print("     ");
    // Serial.print(floatPin4);
    // Serial.print("     ");
    Serial.print(soilMoisturePercent1);
    Serial.print("     ");
    Serial.print(soilMoisturePercent2);
    Serial.print("     ");
    Serial.print(soilMoisturePercent3);
    Serial.print("     ");
    Serial.println(soilMoisturePercent4);
    
    delay(1000);
}