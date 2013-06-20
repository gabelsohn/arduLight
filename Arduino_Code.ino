#include <SPI.h>
#include <WiFi.h>
#include <Stepper.h>
#include <Servo.h>
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 2,3,8,9);
Servo tiltServo;

char thisChar[4];

int pan=0;
double currentPan=0;
int tilt=90;
int on=0;

//for steppify function use
int panTemp=0;

int currentTilt=0;

String data = "";
int i =0;
char inChar;
char fixer[3];

int led = A0;
  
char ssid[] = "Pilotcorkynet";     //  your network SSID (name) 
char pass[] = "Corkythedog";    // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiServer server(4000);
boolean alreadyConnected = false;
WiFiClient client;


void setup() {
  //Set up LED
  tiltServo.attach(5);
  tiltServo.write(90);
  delay (50);
  pinMode (led, OUTPUT);
  //initialize stepper
  myStepper.setSpeed(90);
  // initialize serial:
  Serial.begin(9600);
  // attempt to connect using WPA2 encryption:
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);
  // if you're not connected, stop here:
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } 
  // if you are connected, print out info about the connection:
  else {
    Serial.println("Connected to network");
    server.begin();
    printWifiStatus();
  }
}


void loop()
{
  // do nothing// wait for a new client:
  client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();    
      alreadyConnected = true;
    } 
      
  if (client.available()){
    //BEWARE, MAGIC NUMBER!!!!!! 3 '!"s sent from phone app
    while (i<3){
    //record next incoming character
    inChar = client.read();
    //add that onto the temporary data string
    data += inChar;
    if (data.endsWith("!"))
    {
     data.toCharArray(fixer,4);
     switch (i){
      case 0: 
      pan = atoi(fixer);
      Serial.println(pan);
      data="";
      break;
      case 1:
      tilt = atoi(fixer);
      Serial.println(tilt);
      data="";
      break;
      case 2:
      on = atoi(fixer);
      data="";
       }
      i++;
    }
  }
   data="";
   client.flush();
   //client.stop();
   i=0;
   }    
  }
  
  //control the LED
  if (on==1) digitalWrite (led, HIGH);
  else digitalWrite (led, LOW);
  
  //move stepper to new target
  steppify(pan);
  
  //tilt the tilt servo if its target position has changed
  if(tilt-currentTilt!=0){
  tiltServo.attach(5);
  tiltServo.write(tilt);
  currentTilt=tilt;
  //tiltServo.detach();
  }
}
  
 
  

  
  
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
 void steppify(int target){
   panTemp=target-currentPan;
   currentPan+=panTemp;
   myStepper.step(panTemp*2);
   
   
 }
 
 

