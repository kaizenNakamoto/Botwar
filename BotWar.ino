
#include <ESP8266WiFi.h>

const char* dummy_var = "dummy";
const char* ssid = "bot";
const char* password = "12345678";
String req="stop";
String profile="p1";
int atflag=1;
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
int m[9]={16,5,4,0,14,12,3,1,2};
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  for(int j=0;j<9;j++)
  pinMode(m[j],OUTPUT);

 digitalWrite(m[9],LOW); 
  
}

void loop() {
   while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    motion(profile,req);
    return;
  } 
  // Wait until the client sends some data
 // Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  req = client.readStringUntil('\r');
  req.remove(0,5);
  req.remove(req.length()-9,req.length());
  Serial.println(req);
  client.flush();
  
   // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.print("Led pin is now: ");
 
 // Serial.println("Client disonnected");
 if(req=="p1"){
 req="stop"; 
 profile="p1";}
 else if(req=="p2"){
 req="stop"; 
 profile="p2";}
 if(req=="attack")
 {req="stop";
  attack();
  }
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void motion(String prof,String request){
  if(prof=="p1"){
   if(request=="stop")
   halt();
   if(request=="forward")
   forward();
   if(request=="back")
   back();
   if(request=="left")
   left();
   if(request=="right")
   right();
  }
  else if(prof=="p2"){
   if(request=="stop")
   halt();
   if(request=="forward")
   back();
   if(request=="back")
   forward();
   if(request=="left")
   left2();
   if(request=="right")
   right2();
  }
  else
  halt();
  }
 void halt(){
Serial.println("stop");
  for(int j=0;j<8;j++)
  digitalWrite(m[j],LOW);
  }
 void forward(){
  Serial.println("forward");
  digitalWrite(m[0],0);//1st row right motor
  digitalWrite(m[1],1);
  digitalWrite(m[2],1);//1st row left motor
  digitalWrite(m[3],0);
  digitalWrite(m[4],0);//2nd row right motor
  digitalWrite(m[5],1);
  digitalWrite(m[6],1);//2nd row left motor
  digitalWrite(m[7],0);
  
  }
 void back(){
  Serial.println("back");
    digitalWrite(m[0],1);//1st row right motor
  digitalWrite(m[1],0);
  digitalWrite(m[2],0);//1st row left motor
  digitalWrite(m[3],1);
  digitalWrite(m[4],1);//2nd row right motor
  digitalWrite(m[5],0);
  digitalWrite(m[6],0);//2nd row left motor
  digitalWrite(m[7],1);
  }
 void left(){
  Serial.println("left");
    digitalWrite(m[0],0);//1st row right motor
  digitalWrite(m[1],1);
    digitalWrite(m[4],0);//2nd row right motor
  digitalWrite(m[5],1);
  
    digitalWrite(m[2],0);//1st row left moto
  digitalWrite(m[3],1);
  
  digitalWrite(m[6],0);//2nd row left motor
  digitalWrite(m[7],1);
  delay(30);
    
    digitalWrite(m[2],0);//1st row left moto
  digitalWrite(m[3],0);
  
  digitalWrite(m[6],0);//2nd row left motor
  digitalWrite(m[7],0);
  delay(70);
  
  }
 void right(){
  Serial.println("right");
  digitalWrite(m[2],1);//1st row left motor
  digitalWrite(m[3],0);
  digitalWrite(m[6],1);//2nd row left motor
  digitalWrite(m[7],0);
    digitalWrite(m[0],1);//1st row right motor
  digitalWrite(m[1],0);
    digitalWrite(m[4],1);//2nd row right motor
  digitalWrite(m[5],0);
  
  delay(30);
      digitalWrite(m[0],0);//1st row right motor
  digitalWrite(m[1],0);
      digitalWrite(m[4],0);//2nd row right motor
  digitalWrite(m[5],0);
  
  delay(70);
  }

 void right2(){
  
    digitalWrite(m[0],1);//1st row right motor
  digitalWrite(m[1],0);
  digitalWrite(m[4],1);//2nd row right motor
  digitalWrite(m[5],0);
    digitalWrite(m[2],1);//1st row left motor
  digitalWrite(m[3],0);
  digitalWrite(m[6],1);//2nd row left motor
  digitalWrite(m[7],0);
  delay(35);
    digitalWrite(m[2],0);//1st row left motor
  digitalWrite(m[3],0);
  digitalWrite(m[6],0);//2nd row left motor
  digitalWrite(m[7],0);
  delay(65);
  
  }
  void left2(){
      digitalWrite(m[0],0);//1st row right motor
  digitalWrite(m[1],1);
  digitalWrite(m[4],0);//2nd row right motor
  digitalWrite(m[5],1);
    digitalWrite(m[2],0);//1st row left motor
  digitalWrite(m[3],1);
  digitalWrite(m[6],0);//2nd row left motor
  digitalWrite(m[7],1);
  delay(35);
      digitalWrite(m[0],0);//1st row right motor
  digitalWrite(m[1],0);
  digitalWrite(m[4],0);//2nd row right motor
  digitalWrite(m[5],0);
  delay(65);
      
    }
 void attack(){
  if(atflag==1){
    digitalWrite(m[8],1);
    atflag=0;}
  else{
    digitalWrite(m[8],0);
    atflag=1;}
  Serial.println("attack");}
