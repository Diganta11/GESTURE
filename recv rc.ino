#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10); // CE, CSN
const byte address[6] = "00069";
float recv[6];
#define enA 5  
#define in1 A0
#define in2 A1
#define enB 6   
#define in3 A2
#define in4 A3

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
 if (radio.available()) {   // If the NRF240L01 module received data
     
  radio.read( recv, sizeof(recv) );
  float x = recv[0];
  float y = recv[1];
  float s = recv[2];
  // Serial.println("hello");
  // Serial.print(x);
  // Serial.print("\t");
  // Serial.println(y);

  analogWrite(enA, 150);
  analogWrite(enB, 150);
  if(x < -6){
    Serial.println("F");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(x > 6){
    Serial.println("B");
    digitalWrite(in2, LOW);
    digitalWrite(in1, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in3, HIGH);
  }
  else if(y > 6){
    Serial.println("R");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(y < -6){
    Serial.println("L");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else{
    Serial.println("s");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
 }

}
