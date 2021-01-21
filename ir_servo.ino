#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>

Servo servo;


const int I = 3;

//Decoded buttons from the remote
const long VOLUP = 0x10EF01FE;
const long VOLDWN = 0x10EF718E;
//Any button is pressed
const long HOLD = 0xFFFFFFFF;

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000; 


int RECV_PIN = 7;          //  IR sensor pin
IRrecv receiver(RECV_PIN); 
decode_results results;     //  decoded key



void setup() {

  receiver.enableIRIn();    //  Enable receiver so that it would start processing infrared signals
  servo.attach(13);
  servo.write(0);
  startMillis = millis();
  
}

int volume = 0;
int up = 0;

void loop() {

  currentMillis = millis();
  
  if (currentMillis - startMillis >= period)
  {
    //set up to 3 if the last button press was longer than 10s ago
    up == 3;
  }
  
  if (receiver.decode(&results))
  {            //  Decode the button code and put it in "results" variable
    
    if (results.value == VOLUP || ((results.value == HOLD) && (up == 1)))
    {
      up = 1;
      if(volume <= (180-I))
      {
        volume+=I;
      }
      else volume = 180;
      
      servo.write(volume);
      delay(50);
      startMillis = currentMillis;
            
    }
    if (results.value == VOLDWN || ((results.value == HOLD) && (up == 0)))
    {
      up = 0;
      if(volume >= I)
      {
        volume-=I;
      }
      else volume = 0;

      servo.write(volume);     
      delay(50);
      startMillis = currentMillis;
    }
    if (results.value != VOLDOWN && results.value != VOLUP && results.value != HOLD)
    {
      //a Button besides vol up or down has been pressed
      up = 3;
    }
    
    receiver.resume();                      //  Continue listening for new signals
  }
}
