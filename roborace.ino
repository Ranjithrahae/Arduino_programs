#define IN_1  D2      
#define IN_2  D3         
#define IN_3  D4          
    
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

Servo servo1; // Create a Servo object for servo 1
Servo servo2; // Create a Servo object for servo 2
Servo servo3;
String command;             //String to store app command state.


const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() {
 
  servo1.attach(IN_1); // Attach servo 1 to pin 9
  servo2.attach(IN_2); // Attach servo 2 to pin 10
  servo3.attach(IN_3); // Attach servo 3 to pin 11

  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void Joint1CW(){ 
        servo1.write(180);
  }

void Joint1CCW(){ 

    servo1.write(-10);
  }

void Joint2CW(){ 
  servo2.write(10);
  }

void Joint2CCW(){
        servo2.write(-10);
  }

void Joint3CW(){
      
       servo3.write(10);
   }

void Joint3CCW(){
      servo3.write(-10);
  }

void VaccumON(){ 

      /*digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);*/
     
  }


void HomePosition(){  

        servo1.write(0);
        servo2.write(0);
        servo3.write(0);
 }

void loop() {
      server.handleClient();
      servo1.write(0);
      servo2.write(0);
      servo3.write(0);
      delay(1000);
      command = server.arg("State");
      if (command == "F") Joint1CW();
      else if (command == "B") Joint1CCW();
      else if (command == "L") Joint2CW();
      else if (command == "R") Joint2CCW();
      else if (command == "I") Joint3CW();
      else if (command == "G") Joint3CCW();
      //else if (command == "H") VaccumON();
     // else if (command == "S") HomePosition();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}


