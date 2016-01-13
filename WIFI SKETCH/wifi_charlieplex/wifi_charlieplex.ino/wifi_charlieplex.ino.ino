/*
 *  Simple HTTP get webclient test
 */
 
#include <EEPROM.h>
#include <pfodESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";
 
const char* host = "yourserver.com";
const int httpPort = 80;
String url = "/**folder**/index.php?read=simple";

unsigned long previousMillis = 0;
const long interval = 500; // milliseconds gap between sending a network request.

WiFiClient client;

// I skipped F because F isn't allowed
#define A 5
#define B 4
#define C 15
#define D 16
#define E 14
#define G 12
#define H 13

const int count = 42;

// visual array of how the pins are laid out
int lights[count][2] = {

      {A,B},  {B,C},  {C,D},  {D,E},  {E,G},  {G,H},  {H,A},
      
      {B,A},  {C,B},  {D,C},  {E,D},  {G,E},  {H,G},  {A,H},

      {A,C},  {B,D},  {C,E},  {D,G},  {E,H},  {G,A},  {H,B},
      
      {C,A},  {D,B},  {E,C},  {G,D},  {H,E},  {A,G},  {B,H},

      {A,D},  {B,E},  {C,G},  {D,H},  {E,A},  {G,B},  {H,C},
      
      {D,A},  {E,B},  {G,C},  {H,D},  {A,E},  {B,G},  {C,H}


};


// default is a smiley face
bool ledState[42] = {
  1,1,1,1,1,1,1,  
  0,0,0,0,0,0,1, 
  1,1,1,1,1,0,1,  
  1,0,0,0,1,0,1,  
  1,0,0,0,0,0,1,  
  1,1,1,1,1,1,1
};


void setup() {

Serial.begin(115200);

  pinMode(A, INPUT);
   pinMode(B, INPUT);
   pinMode(C, INPUT);
   pinMode(D, INPUT);
   pinMode(E, INPUT);
   pinMode(G, INPUT);
   pinMode(H, INPUT);
  
  delay(100);
 
  WiFi.begin(ssid, password);

  Serial.println("connecting to wifi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  delay(1000);

  client.connect(host, httpPort);

  Serial.println("waiting to connect to server");
  
  while (!client.connected()) {
    delay(500);
    Serial.print(".");
  }

  if(!client.connected()){
    client.connect(host, httpPort);
     while (!client.connected()) {
      delay(500);
      Serial.print(".");
    }
  }
  

}

void loop() {

  // try reconnecting
  if(!client.connected()){
    client.connect(host, httpPort);
     while (!client.connected()) {
    }
  }


  // check if theres a server reply to check
  bool reply = false;
  String response = "";

  while(client.available()){

    char in = client.read();
        
    if (in == '{') {
        reply = true;
    } else if (in == '}') {
        break;
    } else {
       if (reply) response += (in);
    }
   
  }
  
  if(reply){
    
    parse(response);
    
  } 

  // otherwise run the regular led sequence
  for(int i=0;i<42;i++){
    if(ledState[i]){
      light(lights[i]);
    }
  }

  // reset the pins (stops the last being slightly brighter);
  reset_pins();
     
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    flip();
  }

}

void parse(String response){
  for(int i=0;i<42;i++){
    if(response.charAt(i) == '1'){
      ledState[i] = 1;
    } else{
      ledState[i] = 0;
    }
  }
}


void flip(){

  client.flush();
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
}


void light( int pins[2] ){

  reset_pins();
    
  pinMode( pins[0], OUTPUT );
  digitalWrite( pins[0], HIGH );
  
  pinMode( pins[1], OUTPUT );
  digitalWrite( pins[1], LOW );
}

 
void reset_pins()
{
   pinMode(A, INPUT);
   pinMode(B, INPUT);
   pinMode(C, INPUT);
   pinMode(D, INPUT);
   pinMode(E, INPUT);
   pinMode(G, INPUT);
   pinMode(H, INPUT);
   digitalWrite(A, LOW);
   digitalWrite(B, LOW);
   digitalWrite(C, LOW);
   digitalWrite(D, LOW);
   digitalWrite(E, LOW);
   digitalWrite(G, LOW);
   digitalWrite(H, LOW);
   
}
