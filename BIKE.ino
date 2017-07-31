#include <SoftwareSerial.h>
#define Tx_Led 9
#define Aux_Led 10
#define Button 11
#define AUX 5

SoftwareSerial mySerial(2, 3); // (2-RX) <<-- Connect TX pin of LoRa  ......  (3-TX) <<-- Connect RX pin of LoRa
// gnd SET_A and SET_B for Normal Mode (Send and Receive)


//int num = 20;
char data[5] = {0,0,0,0,0};                   // Create an array to store incoming data
unsigned long wait_time = 3000;
unsigned long prev_wait_time = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(Tx_Led, OUTPUT);
  pinMode(Aux_Led, OUTPUT);
  pinMode(Button,INPUT);
  pinMode(AUX, INPUT);

}

void loop() 
{
  // Sending the dummy data
  if (digitalRead(Button) == HIGH) 
  {
    digitalWrite(Tx_Led, HIGH);
    mySerial.println("Bike 1 Lat/Long: 10.729546 / 106.69603299999994");    
    digitalWrite(Tx_Led, LOW);
  }

  //Receive the confirmation from the station and print it
  if (mySerial.available() > 1)
  {
    String input = mySerial.readString();       // Read input from buffer like normal                    
    input.toCharArray(data,5);                // Convert input type String to store into array data[]

  //If the bike does not receive confirmation resend data
    unsigned long currentTime = millis ();
    if ((unsigned long)(currentTime - prev_wait_time) >= wait_time ) 
    {
      switch (data [5]) 
      {
        case '0':
          Serial.println ("Transmission failed");
          mySerial.println ("Bike 1 Lat/Long: 10.729546 / 106.69603299999994");
        case '1':
          Serial.println ("Data sent");
      }
    }
  //////////////////////////////////////////////////////////
  }
  

  // LED for checking if the module is receiving or sending data
  if (digitalRead(AUX) == LOW) 
  {
    digitalWrite(Aux_Led, HIGH);
  }
  
  else if (digitalRead(AUX) == HIGH) 
  {
    digitalWrite(Aux_Led, LOW);   
  }
  delay(20);
} 

