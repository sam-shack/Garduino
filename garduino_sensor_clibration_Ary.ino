//calibration method usding push button and serial output
//I haven't tested it :( but hopefully it works.
//push button required


//change these to the analog pins used for the sensors
#define soil1 A1
#define soil2 A3
#define soil3 A4
#define soil4 A5

#define pushButton 7  //set this to the digital pin connected to the push button



void setup() {

  pinMode (pushButton, INPUT);  //button is an input
  Serial.begin(9600);           //start serial monitor

}

void loop() {

  bool buttonState = LOW;            //hold current state of push button, was it pressed or not

  //airValueN is the dry sensor value for sensor N
  //waterValueN is the submerged sensor value for sensor N
  int airValue1 = 0;
  int waterValue1 = 0;

  int airValue2 = 0;
  int waterValue2 = 0;

  int airValue3 = 0;
  int waterValue3 = 0;

  int airValue4 = 0;
  int waterValue4 = 0;

  bool flag = HIGH; //flag to control while loops

  buttonState = digitalRead(pushButton);    //read push button
  //Serial.println(buttonState);            //print state for debugging 


  if(buttonState == HIGH){                  //if button is pressed, start calibration
    Serial.println("Waiting for input");    //signal to user

    while(flag){
      if(buttonState == HIGH){
        
        Serial.println("Prepare sensor one for dry value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading dry value for sensor one");
            airValue1 = analogRead(soil1);                        //read and store dry value for this sensor
            delay(500);
            Serial.println("Sensor one dry value read");

            Serial.println("Proceeding to wet value");
            flag = LOW;                                           //set flag to escape while loop
          }
          
        }
      }
    }

    flag = HIGH;                                                  //reset flag to remain in next loop


    while(flag){
      buttonState = digitalRead(pushButton);

      if(buttonState == HIGH){
        Serial.println("Prepare sensor one for wet value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading wet value for sensor one");
            waterValue1 = analogRead(soil1);                      //read and store wet value for this sensor
            delay(500);
            Serial.println("Sensor one wet value read");

            Serial.println("Proceeding to next sensor");
            flag = LOW;
          } 
        }
      }
    }

            //repeat for remaining sensors


    flag = HIGH;

    while(flag){
      if(buttonState == HIGH){
        
        Serial.println("Prepare sensor two for dry value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading dry value for sensor two");
            airValue2 = analogRead(soil2);
            delay(500);
            Serial.println("Sensor two dry value read");

            Serial.println("Proceeding to wet value");
            flag = LOW;
          }
        }
      }
    }

    flag = HIGH;


    while(flag){
      buttonState = digitalRead(pushButton);

      if(buttonState == HIGH){
        Serial.println("Prepare sensor two for wet value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading wet value for sensor two");
            waterValue2 = analogRead(soil2);
            delay(500);
            Serial.println("Sensor two wet value read");

            Serial.println("Proceeding to next sensor");
            flag = LOW;
          } 
        }
      }
    }

    flag = HIGH;

    while(flag){
      if(buttonState == HIGH){
        
        Serial.println("Prepare sensor three for dry value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading dry value for sensor three");
            airValue3 = analogRead(soil3);
            delay(500);
            Serial.println("Sensor three dry value read");

            Serial.println("Proceeding to wet value");
            flag = LOW;
          }
        }
      }
    }

    flag = HIGH;


    while(flag){
      buttonState = digitalRead(pushButton);

      if(buttonState == HIGH){
        Serial.println("Prepare sensor three for wet value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading wet value for sensor three");
            waterValue3 = analogRead(soil3);
            delay(500);
            Serial.println("Sensor three wet value read");

            Serial.println("Proceeding to next sensor");
            flag = LOW;
          }
        }
      }
    }

    flag = HIGH;

    while(flag){
      if(buttonState == HIGH){
        
        Serial.println("Prepare sensor four for dry value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading dry value for sensor four");
            airValue4 = analogRead(soil4);
            delay(500);
            Serial.println("Sensor four dry value read");

            Serial.println("Proceeding to wet value");
            flag = LOW;
          }
        }
      }
    }

    flag = HIGH;


    while(flag){
      buttonState = digitalRead(pushButton);

      if(buttonState == HIGH){
        Serial.println("Prepare sensor four for wet value");
        delay(500);
        buttonState = LOW;
        Serial.println("Press button when ready to calibrate");
        while(buttonState == LOW){
          buttonState = digitalRead(pushButton);
          if(buttonState == HIGH){
            Serial.println("Reading wet value for sensor four");
            waterValue4 = analogRead(soil4);
            delay(500);
            Serial.println("Sensor four wet value read");

            Serial.println("Calibration complete for all four sensors!!");
            flag = LOW;
          } 
        }
      }
    }

    flag = HIGH;

    //display calibration values to user

    Serial.println("Displaying calibrated values:");
    Serial.print("Sensor one dry value is ");
    Serial.print(airValue1);
    Serial.print("  Sensor one wet value is ");
    Serial.println(waterValue1);
    Serial.print("Sensor two dry value is ");
    Serial.print(airValue2);
    Serial.print("  Sensor two wet value is ");
    Serial.println(waterValue2);
    Serial.print("Sensor three dry value is ");
    Serial.print(airValue3);
    Serial.print("  Sensor three wet value is ");
    Serial.println(waterValue3);
    Serial.print("Sensor four dry value is ");
    Serial.print(airValue4);
    Serial.print("  Sensor four wet value is ");
    Serial.println(waterValue4);

    Serial.println(":)");
  }
}
