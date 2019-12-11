//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[15] = "00001";

int HeatPad = 7;

void setup()
{
  while (!Serial);
  Serial.begin(9600);

  radio.begin();

  //set the address
  radio.openReadingPipe(0, address);

  //Set module as receiver
  radio.startListening();

  pinMode (HeatPad, OUTPUT);
}

void loop()
{
  int myBPM;
  //Read the data if available in buffer
  if (radio.available())
  {
    radio.read(&myBPM, sizeof(myBPM));
    Serial.println(myBPM);

    if (myBPM > 75) {
      digitalWrite (7, HIGH);
    } else {
      digitalWrite (7, LOW);
    }
  }
}
