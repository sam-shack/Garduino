// Included Libraries
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
// LCD For Mega Pins SCL: 21  SDA: 20
// LCD For Uno Pins SCL: 5   SDA: 4
  LiquidCrystal_I2C lcd(0x27,16,2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

// Variables
  float tempK, tempC, tempF, lightReading, waterLevel;
  float soilMoisture1, soilMoisture2, soilMoisture3, soilMoisture4;
  float capSoilValue1, capSoilValue2, capSoilValue3, capSoilValue4;
  long int seconds = 0;
  const int airValue = 620; // Calibrate these two values
  const int waterValue = 310;
    
// Setting Pins
  #define thermistor A0
  #define photoRes A1
  #define capSoilSensor1 A2
  #define capSoilSensor2 A3
  #define capSoilSensor3 A6 //A4
  #define capSoilSensor4 A7 //A5
  #define floatSwitch25 5
  #define floatSwitch50 6
  #define floatSwitch75 7
  #define floatSwitch100 8

// Sets Up LCD & Pins
  void setup() {
    lcd.init(); //Initlaize LCD
    lcd.backlight(); //Glow
    pinMode(floatSwitch25, INPUT_PULLUP);
    pinMode(floatSwitch50, INPUT_PULLUP);
    pinMode(floatSwitch75, INPUT_PULLUP);
    pinMode(floatSwitch100, INPUT_PULLUP);
    Serial.begin(9600);
    
  }

// Calls Functions Every 10 Seconds
  void loop()
  {
    setClock();
    if(seconds == 10){
      collectedData();
      printData();
      displayLCD();
    }
  }

// 10 Second Timer
  void setClock(){
    seconds++;
    delay(1000);
    if(seconds > 10)
    {seconds = 0;}
  }
  
// Print To LCD
  void displayLCD()
  {
    lcd.setCursor(0,0); //(col,row)
    lcd.print("Temp:       F");
    lcd.setCursor(6,0);
    lcd.print(tempF);   
  }
    
// Collects Data From Sensors
  void collectedData()
  {
  //Water Level [%] (Float Switches)
    int floatState25 = 1;//digitalRead(floatSwitch25);
    int floatState50 = 1;//digitalRead(floatSwitch50);
    int floatState75 = random(0,2);//digitalRead(floatSwitch75);
    int floatState100 = random(0,2);//digitalRead(floatSwitch100);
  
  // Depending On Which Switches Are Active Will Change Value Of Water Level  
    if(floatState25 && !floatState50 && !floatState75 && !floatState100){
      waterLevel = 25;
    }
    else if(floatState50 && !floatState75 && !floatState100){
      waterLevel = 50;
    }
    else if(floatState75 && !floatState100){
      waterLevel = 75;
    }
    else if(floatState100){
      waterLevel = 100;
    }
    else{
      waterLevel = 0;    
    }

  // Lux [Lx] (Photo-Resistor)
    lightReading = random(500.00,800.00);//analogRead(photoRes);

  // Temperature [K, F, C] (Thermistor)
    /*int tempAir  = analogRead(thermistor);
    tempK = log(10000.0 * ((1024.0 / tempAir - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
    */
    tempK = random(294.00,311.00);
    tempC = tempK - 273.15;
    tempF = (tempC * 9.0)/ 5.0 + 32.0;
    
  
  // Soil Moisutre [%] (Capacitive Soil Moisture Sensors)
    capSoilValue1 = 400; //analogRead(A2);
    capSoilValue2 = random(310,621); //analogRead(A3);
    capSoilValue3 = random(310,621); //analogRead(A4);
    capSoilValue4 = random(310,621); //analogRead(A5);
    soilMoisture1 = map(capSoilValue1, airValue, waterValue, 0, 100);
    soilMoisture2 = map(capSoilValue2, airValue, waterValue, 0, 100);    
    soilMoisture3 = map(capSoilValue3, airValue, waterValue, 0, 100);    
    soilMoisture4 = map(capSoilValue4, airValue, waterValue, 0, 100);    
  }

// Prints Out Data To Send to ESP (Ex: <10.2, 11.89, 59.00>)
  void printData(){
    Serial.print("<");
      Serial.print(lightReading);
      Serial.print(", ");
      Serial.print(tempK);
      Serial.print(", ");
      Serial.print(tempC);
      Serial.print(", ");
      Serial.print(tempF);
      Serial.print(", ");
      Serial.print(waterLevel);
      Serial.print(", ");
      Serial.print(soilMoisture1);
      Serial.print(", ");
      Serial.print(soilMoisture2);
      Serial.print(", ");
      Serial.print(soilMoisture3);
      Serial.print(", ");
      Serial.print(soilMoisture4);
    Serial.println(">");
  }