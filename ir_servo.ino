#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>

Servo servo;


const int I = 3;

const long LAUTER = 0x10EF01FE;
const long LEISER = 0x10EF718E;
const long HALTEN = 0xFFFFFFFF;

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000; 


int RECV_PIN = 7;          //  The digital pin that the signal pin of the sensor is connected to
IRrecv receiver(RECV_PIN);  //  Create a new receiver object that would decode signals to key codes
decode_results results;     //  A varuable that would be used by receiver to put the key code into



void setup() {

  receiver.enableIRIn();    //  Enable receiver so that it would start processing infrared signals
  servo.attach(13);
  servo.write(0);
  startMillis = millis();
  
}

int volume = 0;
int lauter = 0;

void loop() {

  currentMillis = millis();
  
  if (currentMillis - startMillis >= period)
  {
    //setzt lauter auf 3, sobald seit der letzten Regelung mehr als 10 Sekunden vergangen sind
    lauter == 3;
  }
  
  if (receiver.decode(&results))
  {            //  Decode the button code and put it in "results" variable
    
    if (results.value == LAUTER || ((results.value == HALTEN) && (lauter == 1)))
    {
      lauter = 1;
      if(volume <= (180-I))
      {
        volume+=I;
      }
      else volume = 180;
      
      servo.write(volume);
      delay(50);
      startMillis = currentMillis;
            
    }
    if (results.value == LEISER || ((results.value == HALTEN) && (lauter == 0)))
    {
      lauter = 0;
      if(volume >= I)
      {
        volume-=I;
      }
      else volume = 0;

      servo.write(volume);     
      delay(50);
      startMillis = currentMillis;
    }
    if (results.value != LEISER && results.value != LAUTER && results.value != HALTEN)
    {
      //es wurde eine andere Taste gedrückt als Lauter oder Leiser oder Halten
      lauter = 3;
    }
    
    receiver.resume();                      //  Continue listening for new signals
  }
}
