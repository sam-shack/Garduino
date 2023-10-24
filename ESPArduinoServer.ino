// Import required libraries
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
  #define RXp2 16
  #define TXp2 17


// Amount Of Characters That Can Be Parsed Into The Arrays
  const byte numChars = 96;
  char receivedChars[numChars];
  char tempChars[numChars];

// Variables
  double waterLevel, soilMoisture1, soilMoisture2, soilMoisture3, soilMoisture4, lightReading, tempF, tempC, tempK = 0.0;
  boolean newData = false;





// Replace with your network credentials
  const char* ssid = "RCCF";
  const char* password = "auvsiauvsi";

// Create AsyncWebServer object on port 80
  AsyncWebServer server(80);

String readTemperatureF() {
  // Read temperature as Fahrenheit
    tempF;
    if (isnan(tempF)) {    
      Serial.println("Failed to read TempF!");
      return "";
    }
    else {
      //Serial.println(tempF);
      return String(tempF);
    }
}

String readSoilMoisture1() {
  // Read 
  if (isnan(soilMoisture1)) {
    Serial.println("Failed to read from soil moisture sensor 1!");
    return "";
  }
  else {
    //Serial.println(lightReading);
    return String(soilMoisture1);
  }
}

String readSoilMoisture2() {
  
  if (isnan(soilMoisture2)) {
    Serial.println("Failed to read from soil moisture sensor 2!");
    return "";
  }
  else {
    //Serial.println(soilMoisture2);
    return String(soilMoisture2);
  }
}

String readSoilMoisture3() {
  
  if (isnan(soilMoisture3)) {
    Serial.println("Failed to read from soil moisture sensor 3!");
    return "";
  }
  else {
    //Serial.println(soilMoisture3);
    return String(soilMoisture3);
  }
}

String readSoilMoisture4() {
  
  if (isnan(soilMoisture4)) {
    Serial.println("Failed to read from soil moisture sensor 3!");
    return "";
  }
  else {
    //Serial.println(soilMoisture4);
    return String(soilMoisture4);
  }
}

String readLight() {
  
  if (isnan(lightReading)) {
    Serial.println("Failed to read from light sensor!");
    return "";
  }
  else {
    //Serial.println(lightReading);
    return String(lightReading);
  }
}

String readWaterLevel() {
  
  if (isnan(waterLevel)) {
    Serial.println("Failed to read from water level sensor!");
    return "";
  }
  else {
    //Serial.println(waterLevel);
    return String(waterLevel);
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  
  bool status; 
  // default settings
  

  // Initialize SPIFFS
  SPIFFS.begin(false);
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/getTemperatureF", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemperatureF().c_str());
  });
  server.on("/getSoilMoisture1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSoilMoisture1().c_str());
  });
  server.on("/getSoilMoisture2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSoilMoisture2().c_str());
  });
   server.on("/getSoilMoisture3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSoilMoisture3().c_str());
  });
  server.on("/getSoilMoisture4", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSoilMoisture4().c_str());
  });
  server.on("/getLight", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readLight().c_str());
  });
  server.on("/getWaterLevel", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readWaterLevel().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  recvWithStartEndMarkers();
      if (newData == true) {
          strcpy(tempChars, receivedChars);
              // this temporary copy is necessary to protect the original data
              // because strtok() used in parseData() replaces the commas with \0
          parseData();
          showParsedData();
          newData = false;
      }
}

// Reads The Data Recieved From Arduino
  void recvWithStartEndMarkers(){
      static boolean recvInProgress = false;
      static byte ndx = 0;
      char startMarker = '<';
      char endMarker = '>';
      char rc;

      while (Serial2.available() > 0 && newData == false) {
          rc = Serial2.read();

          if (recvInProgress == true) {
              if (rc != endMarker) {
                  receivedChars[ndx] = rc;
                  ndx++;
                  if (ndx >= numChars) {
                      ndx = numChars - 1;
                  }
              }
              else {
                  receivedChars[ndx] = '\0'; // terminate the string
                  recvInProgress = false;
                  ndx = 0;
                  newData = true;
              }
          }

          else if (rc == startMarker) {
              recvInProgress = true;
          }
      }
}

void parseData(){      
      char * strtokIndx; // This is used by strtok() as an index

      strtokIndx = strtok(tempChars,",");  // Get the first part - the string
      lightReading = atof(strtokIndx);

      strtokIndx = strtok(NULL, ",");
      tempK = atof(strtokIndx);            // Convert this part to a float

      strtokIndx = strtok(NULL, ",");
      tempC = atof(strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      tempF = atof(strtokIndx);

      strtokIndx = strtok(NULL, ",");
      waterLevel = atof(strtokIndx);

      strtokIndx = strtok(NULL, ",");
      soilMoisture1 = atof(strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      soilMoisture2 = atof(strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      soilMoisture3 = atof(strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      soilMoisture4 = atof(strtokIndx);
}

void showParsedData(){
      Serial.print("Lux ");
      Serial.println(lightReading);
      Serial.print("TempK: ");
      Serial.println(tempK);
      Serial.print("TempC: ");
      Serial.println(tempC);
      Serial.print("TempF: ");
      Serial.println(tempF);
      Serial.print("Water Level: ");
      Serial.println(waterLevel);
      Serial.print("Soil Moisture 1: ");
      Serial.println(soilMoisture1);
      Serial.print("Soil Moisture 2: ");
      Serial.println(soilMoisture2);
      Serial.print("Soil Moisture 3: ");
      Serial.println(soilMoisture3);
      Serial.print("Soil Moisture 4: ");
      Serial.println(soilMoisture4);
      Serial.println("");

 }
